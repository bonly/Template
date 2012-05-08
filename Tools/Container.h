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

/** @note cont.inc ����
��ť��ʶ, ����Ĳ�������,
         X,Y,W,H,UPͼƬID,DOWNͼƬID,OVERͼƬID,
         OnPointerPressed����,OnPointerDragged����,OnPointerReleased����,
         OnKeyPressed����,OnKeyReleased����
@code 
#define CONT

#endif
@endcode
 */

typedef bool (*pPointerEvn)(int, int); ///< �����ѹ��������ָ������
typedef bool (*pKeyEvn)(int); ///< ���尴����������ָ������

/**
 * ���������ṹ
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
 * Ԥ���������ָ������
��ť��ʶ,��������,UPͼƬID,DOWNͼƬID,OVERͼƬID,
  OnPointerPressed����,OnPointerDragged����,OnPointerReleased����,
  OnKeyPressed����,OnKeyReleased����
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
 * @enum ����ÿ��������ID��
 */
enum RESCONT{
  #define RES(X) ID_##X,
  #include "cont.inc"
  #undef RES
  RESCONT_MAX///< RESCONT_MAX
};

/**
 * @def Ԥ�������ʵ��
 */
#define RES(X) extern Obj V_##X;
#include "cont.inc"
#undef RES

extern ResPool *contPool; ///< Ԥ����������

/**
 * @def Ԥ�����ʼ�������ĺ���
 *//*
#define RES(ID,U,D,O,PP,PD,PR,KP,KR) \
    int init_##ID(void*);
#include "cont.inc"
#undef RES
*/

/**
 * ��ʾ����
*/
int ShowCont(int x);

Cont* GetCont(int x); ///< ȡ����
#undef CONT

#define DELCONTPOOL() DELRESP(contPool) ///< @def DELCONTPOOL

#ifdef __cplusplus
extern "C++"{
/**
   @brief �ж���Ļ�����Ƿ�����ĳ���ؼ���
   x, y, ��ǰ����������, Xzero,Yzero ��������(ƫ��), deviation(ƫ�Χ)
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
