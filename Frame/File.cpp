/**
 *  @file File.cpp
 *  @brief 文件接口定义
 *  @date 2012-4-16
 *  @author Bonly
 */

#include "File.h"
#include "../MTK/AppGlobal.h"

static IFileMgr *FileMgr = 0; ///文件管理指针
static int count = 0; ///文件管理FileMgr 的引用记录数

File Log; ///日志文件
char gpcDebug[BUFSIZE];  ///日志缓冲区大小

/**
 * 构造
 */
File::File() :
            _app(0), _FileMgr(0), _File(0)
{

}

/**
 * 析构
 */
File::~File()
{
    if (_File)
    {
        close();
    }
    --count;
    if (FileMgr && count == 0)
    {
        IFILEMGR_Release(FileMgr);
        FileMgr = 0;
        _FileMgr = 0;
    }
}

/**
 * 初始化动态库接口
 * @return 0:成功
 */
int File::init()
{
    _app = GETAPPGLOBAL()->m_pMe;
    if (_app && FileMgr == 0)
    {
      if (ISHELL_CreateInstance(_app->m_pIShell, AEECLSID_FILEMGR,(void**)&FileMgr)
                  != SUCCESS)
      {
          return ENOMEMORY;
      }
      _FileMgr = FileMgr;
      ++count;
    }
    return SUCCESS;
}

/**
 * 检查状态是否成功
 * @return true:成功 false:失败
 */
bool File::good()
{
    if ((_app == 0) && (init()!=0))
    {
      return false;
    }
    
    return (_FileMgr == 0 || _File == 0) ? false : true;
}

/**
 * 打开文件
 * @param file 打开文件名
 * @param flag 打开方式
 * @return 0:成功 -1:失败
 enum {
 _OFM_READ      = 0x0001,
 _OFM_READWRITE = 0x0002,
 _OFM_CREATE    = 0x0004,
 _OFM_APPEND    = 0x0008
 };
 */
int File::open(const char* file,
            int flag)
{
    if (_FileMgr == 0)
        return -1;

    _flag = flag;
	  if (SUCCESS != IFILEMGR_Test(_FileMgr, file))
	  {
      _flag |= _OFM_CREATE;
	  }
	  else
	  {
      _flag |= _OFM_APPEND;
	  }
    _File = IFILEMGR_OpenFile(_FileMgr, file, _flag);

    if (!_File)
    {
        _FileMgr = 0;
        return -1;
    }
    if (_flag|_OFM_APPEND)
    {
        IFILE_Seek(_File,_SEEK_END,0);
    }

    return 0;
}

int File::flush()
{
  if (!good())
    return -1;
  return IFILE_SetCacheSize(_File, 0);
}

/**
 * 关闭文件
 * @return 文件的引用数
 */
int File::close()
{
    if (!good())
        return -1;

    IFILE_SetCacheSize(_File, 0);
    int ref = IFILE_Release(_File);
    _File = 0;
    return ref;
}

/**
 * 输出数据到文件
 * @param buf　输出内容
 * @param cnt　长度
 * @return　-1:失败
 */
int File::write(void* buf, int cnt)
{
    if (!good())
        return -1;
    return IFILE_Write(_File, buf, cnt);
}

/**
 * 读入数据
 * @param buf 存放数据的缓冲
 * @param cnt 读放数据大小
 * @return
 */
int File::read(void* buf, int cnt)
{
    if (!good())
        return -1;

    return IFILE_Read(_File, buf, cnt);
}

/**
 * 输出日志
 * @param buf 字符串内容
 */
void OutputDebugData(char const* buf)
{
    if (!Log.good())
        Log.open("MyLog.txt");

    int rc = Log.write((void*) buf, STRLEN(buf));
}

/**
 * 定义格式转出日志
 * @param fmt 格式
 * @return
 */
int log(const char *fmt, ...)
{
    if (!Log.good())
        Log.open("MyLog.txt");

    if (!Log.good())
        return -1;

    ZeroMemory(gpcDebug, sizeof(gpcDebug));

    JulianType ttt;
    GETJULIANDATE(0, &ttt);
    
    //SPRINTF(gpcDebug, "%d:%d:%d:%d %s:%d", ttt.wHour, ttt.wMinute, ttt.wSecond,
    //            currentTimeMillis(),__FILE__, __LINE__);
    
    SPRINTF(gpcDebug, "[%s:%s]", __DATE__, __TIME__);
    char* ptc = &gpcDebug[STRLEN(gpcDebug)];
    va_list p;
    va_start(p, fmt);

    for (const char *s = fmt; *s; ++s)
    {
        if (*s != '%')
        {
            *(ptc++) = *s;
        }
        else
        {
            switch (*(++s))
            {
                case '%':
                {
                    *(ptc++) = '%';
                }
                    break;
                case 's':
                {
                    const char* pc = va_arg(p, const char*);
                    while (*pc)
                    {
                        *(ptc++) = *(pc++);
                    }
                }
                    break;
                case 'c':
                {
                    *(ptc++) = va_arg(p, char);
                }
                    break;
                case 'd':
                {
                    int nNum = va_arg(p, int);

                    char pc[32] = { 0 };

                    if (nNum < 0)
                    {
                        *(ptc++) = '-';
                        nNum = -nNum;
                    }
                    else if (nNum == 0)
                    {
                        *(ptc++) = '0';
                    }

                    int nIndex = 32;
                    while (nNum > 0)
                    {
                        nIndex--;
                        pc[nIndex] = (int) (nNum % 10) + '0';
                        nNum /= 10;
                    }

                    for (; nIndex < 32;)
                    {
                        *(ptc++) = pc[nIndex++];
                    }
                }
                    break;
                case 'u':
                {
                    unsigned int nNum = va_arg(p, unsigned int);

                    char pc[32] = { 0 };

                    if (nNum == 0)
                    {
                        *(ptc++) = '0';
                    }

                    int nIndex = 32;
                    while (nNum > 0)
                    {
                        nIndex--;
                        pc[nIndex] = (int) (nNum % 10) + '0';
                        nNum /= 10;
                    }

                    for (; nIndex < 32;)
                    {
                        *(ptc++) = pc[nIndex++];
                    }
                }
                    break;
                case 'p':
                {
                    *(ptc++) = '0';
                    *(ptc++) = 'x';

                    unsigned int unNum = va_arg(p, unsigned int);

                    char pc[32] = { 0 };

                    if (unNum == 0)
                    {
                        *(ptc++) = '0';
                    }

                    int nIndex = 32;
                    while (unNum > 0)
                    {
                        nIndex--;
                        int n = (int) (unNum % 16);
                        if (n < 10)
                            pc[nIndex] = n + '0';
                        else
                            pc[nIndex] = n - 10 + 'a';
                        unNum >>= 4;
                    }

                    for (; nIndex < 32;)
                    {
                        *(ptc++) = pc[nIndex++];
                    }
                }
                    break;
                default:
                    break;
            }
        }
    }
    va_end(p);
    *ptc = 0;

    return Log.write((void*) gpcDebug, STRLEN(gpcDebug));
}


