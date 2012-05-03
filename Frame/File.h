/**
 *  @file File.h
 *  @brief �ļ��ӿ�����
 *  @date 2012-4-16
 *  @author Bonly
 */

#ifndef FILE_H_
#define FILE_H_
#include <aeeappgen.h>
#include <AEEFile.h>

class File
{
    public:
        File();
        virtual ~File();
        int open(const char* file, int flag = _OFM_READWRITE);
        bool good();
        int write(void* buf, int cnt);
        int read(void* buf, int cnt);
        int close();
        int flush();

    private:
        int init();

    private:
        AEEApplet *_app;
        IFileMgr  *_FileMgr;  ///< �ļ�����
        IFile     *_File;     ///< �ļ�
        int       _flag;       ///< �����ʶ
};

/**
 * ��־�ļ���װ
 */
extern File Log;
enum {BUFSIZE=2*1024};
extern char gpcDebug[BUFSIZE];  ///��־��������С
void OutputDebugData(char const* buf);  ///����ɵ���־�ӿ�
int log(const char *fmt, ...);          ///��������־�ӿ�

#define LOG(...) \
{\
    if (!Log.good())\
        Log.open("MyLog.txt");\
    if (!Log.good())\
        return -1;\
    ZeroMemory(gpcDebug, sizeof(gpcDebug));\
    SPRINTF(gpcDebug, "[%s:%s]", __DATE__, __TIME__);\
    char* ptc = &gpcDebug[STRLEN(gpcDebug)];\
    SPRINTF(ptc, __VA_ARGS__);  \
    Log.write((void*) gpcDebug, STRLEN(gpcDebug));\
}

#ifdef _DEBUG
#define _ {\
  SPRINTF(gpcDebug, "[%s:%s %s:%d]\r\n", __DATE__, __TIME__, __FILE__, __LINE__); \
  OutputDebugData(gpcDebug); \
  Log.close(); \
  }

#define plog(X) {\
  SPRINTF(gpcDebug, "[%s:%s %s:%d] %s\r\n", __DATE__, __TIME__, __FILE__, __LINE__,X); \
  OutputDebugData(gpcDebug); \
  Log.close(); \
  }
#else
#define _ 
#define plog(X) 
#endif

#endif /* FILE_H_ */

/**
 @addtogroup Usage
 @par 1.����ͷ�ļ�
 @code #include "File.h"  @endcode
 ���޸���־buffer�Ĵ�С
 @code enum {BUFSIZE=2*1024}; @endcode
 @par 2.����Ҫ��¼��־�ĵط�����
 @code log ("%s\r\n", "OnCreate"); @endcode
 ����
 @code OutputDebugData("onDestroy\r\n"); @endcode
 */
