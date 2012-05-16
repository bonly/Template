/**
 *  @file Container.h
 *
 *  @date 2012-4-25
 *  @author Bonly
 */
#include "Container.h"
#include "Image.h"
//#include "File.h"
//#include <aeestdlib.h>
#include "Paint.h"
#include <stdarg.h>

ResPool *contPool = 0;

int init_obj(Cont *obj, const int, ...);

#define CONT
/**
 * @def 定义变量
 */
#define RES(O,...) Obj *V_##O = 0;
#include "cont.inc"
#undef RES

/**
 * @def 定义数组List
 */
#define RES(O,...) (Obj*) V_##O,
Obj*  contList[]={
#include "cont.inc"
};
#undef RES


/**
 * @def 定义初始化函数,创建数据物件
 * 
 */
#define RES(X, C, ...) \
static int init_##X(void* p) {\
  if(V_##X->obj == 0) {\
       Cont* obj = SafeNew Cont;\
       if(obj == 0) return 1; \
       obj->ID = ID_##X; \
       V_##X->obj = obj; \
       init_obj(obj, C, __VA_ARGS__);\
  }\
  return 0;\
}
#include "cont.inc"
#undef RES

/**
 * 补完整结构数据,创建控制物件
 */
static void fix_relation()
{
    int i = 0;
#define CONT
#define RES(X, ...) \
    V_##X = SafeNew Obj; \
    contList[i] = V_##X; \
    contList[i]->obj = 0; \
    contList[i]->ID = i; \
    contList[i]->create = init_##X; \
    ++i;
#include "cont.inc"
#undef RES
#undef CONT
}

#undef CONT

/**
 * 删除数据对象
 */
static void delObj(int idx) 
{
    if(idx >= contPool->res_max || idx < 0) return;
    if (contPool->List[idx]->obj)
    {
      delete (Cont*)contPool->List[idx]->obj;
      contPool->List[idx]->obj = 0;
    } 
}

/** 
 * 初始化
 */
static int init(ResPool *resp)
{
    resp->List = contList;
    resp->res_max = RESCONT_MAX;
    resp->delObj = delObj;
    resp->fix_relation = fix_relation;

    return 0;
}

/** 取容器
 *
 */
Cont* GetCont(int x)
{
    return (Cont*)RESP(&contPool, init)->getObj(x)->obj;
}

/** 显示容器,可供在onpaint中调用
 *
 */
int ShowCont(int x, Page *pg)
{
  Cont* btn = GetCont(x);
  btn->page = pg;
  if (btn == 0) return -1;
  if (btn->curPic >= 0)
      PAINT->drawImage(GETIMG(btn->curPic), btn->x, btn->y);
  return 0;
}

/** 对象初始化值
 *
         X,Y,W,H,UP图片ID,DOWN图片ID,OVER图片ID,
         OnPointerPressed函数,OnPointerDragged函数,OnPointerReleased函数,
         OnKeyPressed函数,OnKeyReleased函数
 */
#pragma managed(push, off)
int init_obj(Cont *obj, const int count, ...)
{
  if(obj == 0) return -1;

  va_list ap;
  va_start(ap, count);
  
  obj->curPic = -1;
  obj->picDown = -1;
  obj->picOver = -1;
  obj->picUp = -1;
  for (int cnt = 0; cnt < count; ++cnt)
  {
    switch (cnt)
    {
    case 0:
      obj->x = va_arg(ap, int);  ///x
      break;
    case 1:
      obj->y = va_arg(ap, int);  ///y
      break;
    case 2:
      obj->width = va_arg(ap, int);  ///w
      break;
    case 3:
      obj->height = va_arg(ap, int);  ///h
      break;
    case 4:
      obj->picUp = va_arg(ap, int); ///UP图片ID
      obj->curPic = obj->picUp;
      break;
    case 5:
      obj->picDown = va_arg(ap, int); ///DOWN图片ID
      break;
    case 6:
      obj->picOver = va_arg(ap, int); ///OVER图片ID
      break;
    case 7:
      obj->PointerPressed = va_arg(ap, pPointerEvn); ///OnPointerPressed函数
      break;
    case 8:
      obj->PointerDragged = va_arg(ap, pPointerEvn); ///OnPointerDragged函数
      break;
    case 9:
      obj->PointerReleased = va_arg(ap, pPointerEvn); ///OnPointerReleased函数
      break;
    case 10:
      obj->KeyPressed = va_arg(ap, pKeyEvn); ///OnKeyPressed函数
      break;
    case 11:
      obj->KeyReleased = va_arg(ap, pKeyEvn); ///OnKeyReleased函数
      break;
    }
  }
  va_end(ap);
  return 0;
}
#pragma managed(pop)

bool NP(int, int)
{
  return true;
}

bool NK(int)
{
  return true;
}

bool PointerPressedListen(int x, int y, Page *pg)
{
  for (int i = 0; i < contPool->res_max; ++i)
  {
    Cont* cont = GetCont(i);
    if (cont == 0) continue; ///没取到按钮,继续

    if (pg != cont->page) ///不是按钮所在页,继续
      continue;

    if (cont->curPic != -1 && cont->picDown != -1) ///换图
    {
      cont->width =  GETIMG(cont->picDown)->width;
      cont->height =  GETIMG(cont->picDown)->height;
      cont->curPic = cont->picDown;
    }

    if (cont->PointerPressed == 0) continue;
    if (1 == InButtonPic(x, y, 0, 0, cont))
    {
      return cont->PointerPressed(x, y);
    }
  }
  return false;
}

bool PointerDraggedListen(int x, int y, Page *pg)
{
  for (int i = 0; i < contPool->res_max; ++i)
  {
    Cont* cont = GetCont(i);
    if (cont == 0 )continue;

    if (pg != cont->page)
      continue;

    if (cont->curPic != -1 && cont->picOver != -1)
    {
      cont->curPic = cont->picOver;
    }
    if (cont->PointerDragged == 0) continue;
    if (1 == InButtonPic(x, y, 0, 0, cont))
    {
      return cont->PointerDragged(x, y);
    }
  }
  return false;
}

bool PointerReleasedListen(int x, int y, Page *pg)
{
  for (int i = 0; i < contPool->res_max; ++i)
  {
    Cont* cont = GetCont(i);
    if (cont == 0) continue;

    if (pg != cont->page)
      continue;
    
    if (cont->curPic != -1 && cont->picUp != -1)///设置大小值
    {
      cont->width =  GETIMG(cont->picUp)->width;
      cont->height =  GETIMG(cont->picUp)->height;
      cont->curPic = cont->picUp;
    }

    if (cont->PointerReleased == 0) continue;
    if (1 == InButtonPic(x, y, 0, 0, cont))
    {
      return cont->PointerReleased(x, y);
    }
  }
  return false;
}

bool KeyReleasedListen(int keyCode, Page *pg)
{
  for (int i = 0; i < contPool->res_max; ++i)
  {
    Cont* cont = GetCont(i);
    if (cont ==0) continue;

    if (cont->page != pg)
      continue;

    if (cont->curPic != -1 && cont->picUp != -1)
    {
      cont->width =  GETIMG(cont->picUp)->width;
      cont->height =  GETIMG(cont->picUp)->height;
      cont->curPic = cont->picUp;
    }
    if (cont->KeyReleased == 0) continue;
    cont->KeyReleased(keyCode);
  }
  return true;
}

bool KeyPressedListen(int keyCode,Page *pg)
{
  for (int i = 0; i < contPool->res_max; ++i)
  {
    Cont* cont = GetCont(i);
    if (cont == 0) continue;

    if (pg != cont->page)
      continue;
    
    if (cont->curPic != -1 && cont->picDown != -1)
    {
      cont->width =  GETIMG(cont->picDown)->width;
      cont->height =  GETIMG(cont->picDown)->height;
      cont->curPic = cont->picDown;
    }
    if (cont->KeyPressed == 0) continue;
    cont->KeyPressed(keyCode);
  }
  return true;
}
