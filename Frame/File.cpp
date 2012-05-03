/**
 *  @file File.cpp
 *  @brief �ļ��ӿڶ���
 *  @date 2012-4-16
 *  @author Bonly
 */

#include "File.h"
#include "../MTK/AppGlobal.h"

static IFileMgr *FileMgr = 0; ///�ļ�����ָ��
static int count = 0; ///�ļ�����FileMgr �����ü�¼��

File Log; ///��־�ļ�
char gpcDebug[BUFSIZE];  ///��־��������С

/**
 * ����
 */
File::File() :
            _app(0), _FileMgr(0), _File(0)
{

}

/**
 * ����
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
 * ��ʼ����̬��ӿ�
 * @return 0:�ɹ�
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
 * ���״̬�Ƿ�ɹ�
 * @return true:�ɹ� false:ʧ��
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
 * ���ļ�
 * @param file ���ļ���
 * @param flag �򿪷�ʽ
 * @return 0:�ɹ� -1:ʧ��
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
 * �ر��ļ�
 * @return �ļ���������
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
 * ������ݵ��ļ�
 * @param buf���������
 * @param cnt������
 * @return��-1:ʧ��
 */
int File::write(void* buf, int cnt)
{
    if (!good())
        return -1;
    return IFILE_Write(_File, buf, cnt);
}

/**
 * ��������
 * @param buf ������ݵĻ���
 * @param cnt �������ݴ�С
 * @return
 */
int File::read(void* buf, int cnt)
{
    if (!good())
        return -1;

    return IFILE_Read(_File, buf, cnt);
}

/**
 * �����־
 * @param buf �ַ�������
 */
void OutputDebugData(char const* buf)
{
    if (!Log.good())
        Log.open("MyLog.txt");

    int rc = Log.write((void*) buf, STRLEN(buf));
}

/**
 * �����ʽת����־
 * @param fmt ��ʽ
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


