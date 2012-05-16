/**
 *  @file PreLoad.cpp
 *
 *  @date 2012-2-27
 *  @author Bonly
 */
#include "../Tools/Image.h"
#include "../Tools/pre.h"
#include "../Tools/Container.h"
#include "PreLoad.h"
#include "../Tools/Paint.h"
//#include <stdio.h>

//extern Graphics gpDC;
static Page page;

bool click(int x, int y);
/**
 *  初始化函数
 * @return 0: 成功
 */
static int  init()
{
    //V_background.obj = SDL_LoadBMP("c:/bg1.bmp");
    //GETIMG(ID_background);
    

    return 0;
}

/**
 * 处理游戏逻辑的函数
 */
static void running()
{
}

/**
 * 渲染函数
 */
static void onPaint()
{
    //gpDC->drawImage(GETIMG(ID_background), 0, 0, ACHOR_LT);
    PAINT->drawImage(GETIMG(ID_background), 0, 0);
    Cont* btn = GetCont(ID_test);
    btn->x = 30;
    btn->y = 30;
    btn->PointerPressed = click;
    ShowCont(ID_test, &page);
}

/**
 * 释放资源函数
 */
static void onDestory()
{
    //SDL_FreeSurface(V_background.obj);
    DELIMG(ID_background);
}


bool click(int x, int y)
{
  //printf("test ok\r\n");
  TASKS->next_page = 1;
  TASKS->operation = NEXT_PAGE;
  return true;
}

static bool OnPointerPressed(int x,int y)
{
  //printf("pointer press\r\n");
  return true;
}

static bool OnPointerDragged(int x, int y)
{
  //printf("pointer dragged\r\n");
  return false;
}

bool OnPointerReleased(int x, int y)
{
  //printf("pointer released\r\n");
  return false;
}

bool OnKeyReleased(int keyCode)
{
  //printf("key released\r\n");
  return false;
}

bool OnKeyPressed(int keyCode)
{
  //printf("key pressed\r\n");
  return false;
}

/**
 * 创建页面
 * @return Page* 页面结构的指针
 */
Page* createPreLoad()
{
   page.init = init;
   page.onDestory = onDestory;
   page.onPaint = onPaint;
   page.running = running;
   page.OnPointerPressed = OnPointerPressed;
   page.OnPointerDragged = OnPointerDragged;
   page.OnPointerReleased = OnPointerReleased;
   page.OnKeyPressed = OnKeyPressed;
   page.OnKeyReleased = OnKeyReleased;
   return &page;
}
