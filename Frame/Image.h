/**
 *  @file Image.h
 *
 *  @date 2012-4-25
 *  @author Bonly
 */
#ifndef _IMAGE_H__
#define _IMAGE_H__
#include "ResPool.h"
#include <jport.h>

/** @note Resource.inc��ʽ
��ʶ,�ļ���
@code
#ifdef IMGSEG
RES(background, res/backgroud/2_bg.png)
#endif
@endcode
 
 */

#define IMGSEG
/**
 * @enum ����ÿ�������ID��
 */
enum RES{
  #define RES(X,F) ID_##X,
  #include "Resource.inc"
  #undef RES
  RES_MAX//!< RES_MAX
};

/**
 * @def Ԥ�������ʵ��
 */
#define RES(X,F) extern Obj V_##X;
#include "Resource.inc"
#undef RES

extern ResPool *imgPool; ///< Ԥ����ͼƬ��

/**
 * @def Ԥ�����ʼ�������ĺ���
 */
/*
#define RES(X,F) \
    int load_##X(void*);
#include "Resource.inc"
#undef RES
*/

#undef IMGSEG


JImage* GETIMG(int x); ///< ȡͼƬ
void DELIMG(int x);  ///< ɾ��ͼƬ

#define DELIMGPOOL() DELRESP(imgPool) ///< @def DELIMGPOOL
#endif


//#define GETIMG(X) (SDL_Surface*)RESP->getObj(X)->obj ///< @def ȡͼƬ

