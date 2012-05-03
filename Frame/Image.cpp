/**
 *  @file Image.cpp
 *
 *  @date 2012-4-25
 *  @author Bonly
 */
#include "Image.h"

//#include <stdlib.h>
#include <aeestdlib.h>
#include <jport.h>

extern Graphics gpDC;
ResPool *imgPool = 0;

#define IMGSEG

/**
 * @def �������
 */
#define RES(O,F) Obj V_##O;
#include "Resource.inc"
#undef RES

/**
 * @def ��������List
 */
#define RES(O,F) (Obj*)&V_##O,
Obj*  imgList[]={
#include "Resource.inc"
};
#undef RES

/**
 * @def �����ʼ������
 * 
 */
#define RES(X,F) \
static int load_##X(void* p) {\
    if(V_##X.obj == 0) \
       V_##X.obj = Image_createImage(gpDC, #F);\
       if(V_##X.obj == 0) return 1;else return 0; \
}
#include "Resource.inc"
#undef RES

/**
 * �������ṹ����
 */
static void fix_relation()
{
    int i = 0;
#define IMGSEG
#define RES(X,F) \
    imgList[i]->ID = i; \
    imgList[i]->create = load_##X; \
    ++i;
#include "Resource.inc"
#undef RES
#undef IMGSEG
}
#undef IMGSEG


static void delObj(int idx); ///< ɾ������

/** 
 * ��ʼ��
 */
static int init(ResPool *resp)
{
    resp->List = imgList;
    resp->res_max = RES_MAX;
    resp->delObj = delObj;
    resp->fix_relation = fix_relation;

    return 0;
}

/**
 * ɾ������
 */
static void delObj(int idx) 
{
    if(idx >= imgPool->res_max || idx < 0) return;
    if (imgPool->List[idx]->obj)
    {
      delete (JImage*)imgPool->List[idx]->obj;
      imgPool->List[idx]->obj = 0;
    } 
}

JImage* GETIMG(int x)
{
   return (JImage*)RESP(imgPool, init)->getObj(x)->obj;
}

void DELIMG(int x)
{
   RESP(imgPool, init)->delObj(x);
}
