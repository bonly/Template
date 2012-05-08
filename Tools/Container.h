/**
 *  @file Container.h
 *
 *  @date 2012-4-25
 *  @author Bonly
 */
#ifndef __CONTAINER_H__
#define __CONTAINER_H__
#include "ResPool.h"
#ifdef __cplusplus
extern "C"{
#endif

/** @note cont.inc 定义
按钮标识, 后面的参数个数,
         X,Y,W,H,UP图片ID,DOWN图片ID,OVER图片ID,
         OnPointerPressed函数,OnPointerDragged函数,OnPointerReleased函数,
         OnKeyPressed函数,OnKeyReleased函数
@code 
#define CONT

#endif
@endcode
 */

typedef bool (*pPointerEvn)(int, int); ///< 定义点压操作函数指针类型
typedef bool (*pKeyEvn)(int); ///< 定义按键操作函数指针类型

/**
 * 定义容器结构
 */
typedef struct _Cont
{
  int ID;
  int x;
  int y;
  int width;
  int height;
  int picUp;
  int picDown;
  int picOver;
  int curPic;
  pPointerEvn PointerPressed;
  pPointerEvn PointerDragged;
  pPointerEvn PointerReleased;
  pKeyEvn     KeyPressed;
  pKeyEvn     KeyReleased;
}Cont;

#define CONT

/**
 * 预定义各函数指针类型
按钮标识,参数个数,UP图片ID,DOWN图片ID,OVER图片ID,
  OnPointerPressed函数,OnPointerDragged函数,OnPointerReleased函数,
  OnKeyPressed函数,OnKeyReleased函数
 */
#define RES(ID, C, X, Y, W, H, U, D, O,PP,PD,PR,KP,KR) \
  extern bool PP(int, int);\
  extern bool PD(int, int);\
  extern bool PR(int, int);\
  extern bool KP(int); \
  extern bool KR(int);
#include "cont.inc"
#undef RES

/**
 * @enum 定义每个容器的ID号
 */
enum RESCONT{
  #define RES(X) ID_##X,
  #include "cont.inc"
  #undef RES
  RESCONT_MAX///< RESCONT_MAX
};

/**
 * @def 预定义变量实例
 */
#define RES(X) extern Obj V_##X;
#include "cont.inc"
#undef RES

extern ResPool *contPool; ///< 预定义容器池

/**
 * @def 预定义初始化变量的函数
 *//*
#define RES(ID,U,D,O,PP,PD,PR,KP,KR) \
    int init_##ID(void*);
#include "cont.inc"
#undef RES
*/

/**
 * 显示容器
*/
int ShowCont(int x);

Cont* GetCont(int x); ///< 取容器
#undef CONT

#define DELCONTPOOL() DELRESP(contPool) ///< @def DELCONTPOOL

#ifdef __cplusplus
extern "C++"{
/**
   @brief 判断屏幕触摸是否落入某个控件内
   x, y, 当前触摸点坐标, Xzero,Yzero 虚似坐标(偏移), deviation(偏差范围)
 */
template<typename KEY>
int InButtonPic(int x, int y, int Xzero, int Yzero, KEY btn, int deviation = 0)
{
	if ((x + Xzero) >= (btn.x - deviation) 
    && (x + Xzero) <= (btn.x + btn.width + deviation)  
		&& (y + Yzero) >= (btn.y - deviation) 
    && (y + Yzero) <= (btn.y + btn.height + deviation))
         return 1;
     else
         return 0;

}

template<typename KEY>
int InButtonPic(int x, int y, int Xzero, int Yzero, KEY* btn, int deviation = 0)
{
	if (   (x + Xzero) >= (btn->x - deviation) 
    && (x + Xzero) <= (btn->x + btn->width + deviation)  
		&& (y + Yzero) >= (btn->y - deviation) 
    && (y + Yzero) <= (btn->y + btn->height + deviation))
         return 1;
     else
         return 0;

}

}
#endif //cplusplus

bool PointerPressedListen(int x, int y);
bool PointerDraggedListen(int x, int y);
bool PointerReleasedListen(int x, int y);
bool KeyPressedListen(int keyCode);
bool KeyReleasedListen(int keyCode);

#ifdef __cplusplus
}
#endif


#endif //__CONTAINER_H__
