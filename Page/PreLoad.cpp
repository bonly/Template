/**
 *  @file PreLoad.cpp
 *
 *  @date 2012-2-27
 *  @author Bonly
 */
#include "../Frame/Image.h"
#include "../Frame/pre.h"
#include "../Frame/Container.h"
#include "PreLoad.h"
#include <stdio.h>

extern Graphics gpDC;
static Page page;

/**
 *  ��ʼ������
 * @return 0: �ɹ�
 */
static int  init()
{
    //V_background.obj = SDL_LoadBMP("c:/bg1.bmp");
    //GETIMG(ID_background);
    

    return 0;
}

/**
 * ������Ϸ�߼��ĺ���
 */
static void running()
{
}

/**
 * ��Ⱦ����
 */
static void onPaint()
{
    gpDC->drawImage(GETIMG(ID_background), 0, 0, ACHOR_LT);
    ShowCont(ID_test);
}

/**
 * �ͷ���Դ����
 */
static void onDestory()
{
    //SDL_FreeSurface(V_background.obj);
    DELIMG(ID_background);
}

/**
 * ����ҳ��
 * @return Page* ҳ��ṹ��ָ��
 */
Page* createPreLoad()
{
   page.init = init;
   page.onDestory = onDestory;
   page.onPaint = onPaint;
   page.running = running;
   return &page;
}

bool click(int x, int y)
{
  printf("test ok\r\n");
  return true;
}
