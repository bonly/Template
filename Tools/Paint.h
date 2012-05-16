/**
 *  @file Paint.h
 *
 *  @date 2012-5-7
 *  @author Bonly
 */
#ifndef __PAINT_H__
#define __PAINT_H__
#include "pre.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef struct _Paint
{
  int (*drawImage)(Img* pJImage, int iX, int iY);
  int ScreenWidth;
  int ScreenHeight;
}Paint;

void destory_paint(); //< สอนน

Paint* instance_paint();

#define PAINT instance_paint()
#define DELPAINT() destory_paint()

#ifdef __cplusplus
}
#endif

#endif
