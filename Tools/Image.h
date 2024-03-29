/**
 *  @file Image.h
 *
 *  @date 2012-4-25
 *  @author Bonly
 */
#ifndef _IMAGE_H__
#define _IMAGE_H__

#include "pre.h"
#include "ResPool.h"

#ifdef __cplusplus
extern "C"{
#endif

/** @note Resource.inc格式
标识,文件名
@code
#ifdef IMGSEG
RES(background, res/backgroud/2_bg.png)
#endif
@endcode
 
 */

#define IMGSEG
/**
 * @enum 定义每个对象的ID号
 */
enum RES{
  #define RES(X,...) ID_##X,
  #include "Resource.inc"
  #undef RES
  RES_MAX//!< RES_MAX
};

/**
 * @def 预定义变量实例
 */

#define RES(X,...) extern Obj *V_##X;
#include "Resource.inc"
#undef RES

extern ResPool *imgPool; ///< 预定义图片池

/**
 * @def 预定义初始化变量的函数
 */
//*
#define RES(X,...) \
    int load_##X(void*);
#include "Resource.inc"
#undef RES
//*/

#undef IMGSEG

Img* GETIMG(int x); ///< 取图片
void DELIMG(int x);  ///< 删除图片

#define DELIMGPOOL() DELRESP(imgPool) ///< @def DELIMGPOOL


//#define GETIMG(X) (SDL_Surface*)RESP->getObj(X)->obj ///< @def 取图片

#ifdef __cplusplus
}
#endif

#endif  //_IMAGE_H__
