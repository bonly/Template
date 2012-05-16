/**
 *  @file types_MTK.h
 *
 *  @date 2012-5-9
 *  @author Bonly
 */
#ifndef __TYPES_MTK_H__
#define __TYPES_MTK_H__

enum{BM_TRANSPARENT,BM_COPY};
typedef struct t_img
{
	void   *pImg;
	int    width;
	int    height;
  int    type;
}T_IMG;

#endif