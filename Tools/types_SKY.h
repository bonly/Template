/**
 *  @file types_SKY.h
 *
 *  @date 2012-5-3
 *  @author Bonly
 */
#ifndef __TYPES_SKY_H__
#define __TYPES_SKY_H__
#include "../Sky/src/types.h"
typedef struct t_img
{
	uint16	*pImg;
	int32    dataLen;
	int32    width;
	int32    height;
  int (*getWidth)();
  int (*getHeight)();
}T_IMG;

//javaµÄÃªµã
#define	ACHOR_HCENTER       1
#define	ACHOR_VCENTER       2
#define	ACHOR_LEFT          4
#define	ACHOR_RIGHT         8
#define	ACHOR_TOP           16
#define	ACHOR_BOTTOM        32
#define	ACHOR_BASELINE      64

#define ACHOR_LT   ACHOR_LEFT|ACHOR_TOP
#define ACHOR_RT   ACHOR_RIGHT|ACHOR_TOP
#define ACHOR_LB   ACHOR_LEFT|ACHOR_BOTTOM
#define ACHOR_RB   ACHOR_RIGHT|ACHOR_BOTTOM
#define ACHOR_HV   ACHOR_HCENTER | ACHOR_VCENTER
#define ACHOR_HT   ACHOR_HCENTER | ACHOR_TOP
#define ACHOR_LV   ACHOR_LEFT | ACHOR_VCENTER
#define ACHOR_RV   ACHOR_RIGHT | ACHOR_VCENTER
#define ACHOR_HB   ACHOR_HCENTER | ACHOR_BOTTOM

#endif

