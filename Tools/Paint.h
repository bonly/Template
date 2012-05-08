/**
 *  @file Paint.h
 *
 *  @date 2012-5-7
 *  @author Bonly
 */
#ifndef __PAINT_H__
#define __PAINT_H__
#include "pre.h"

class Paint
{
public:
  bool drawImage(Img* pJImage, int iX, int iY, int iAchor);
};

void destory_paint(); //< สอนน

Paint* instance_paint();

#define PAINT instance_paint()
#define DELPAINT() destory_paint()

#endif
