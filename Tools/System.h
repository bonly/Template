/**
 *  @file system.h
 *
 *  @date 2012-5-3
 *  @author Bonly
 */

#ifndef __cplusplus
#define bool int
#endif

///MTK平台
#if __MTK__
#if WIN32 
#pragma comment(lib,"sxmFixFont.lib")
#pragma comment(lib,"sxmHttp.lib")
#pragma comment(lib,"sxmInput.lib")
#pragma comment(lib,"sxmjlib.lib")
#endif //WIN32

#include <jport.h>
#include <jdefine.h>

typedef JImage Img;
#define EXIT(X) destroyApp(X)

#endif //__MTK__


///斯凯平台
#if __SKY__

#ifdef __cplusplus
extern "C"{
#endif

#include <mrc_base.h>
#include "types_SKY.h"
typedef T_IMG Img;

#define SafeFree free
#define SafeMalloc malloc
#define SafeDelete delete
#define SafeNew new

#define EXIT(X) mrc_exit()
#ifdef __cplusplus
}
#endif
#endif //__SKY__