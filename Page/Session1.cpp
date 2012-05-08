/**
 *  @file Session1.cpp
 *
 *  @date 2012-3-22
 *  @author Bonly
 */
#include "../Tools/pre.h"
#include "../Tools/Page.h"
#include "../Tools/Image.h"
#include "../Tools/Paint.h"
#include "Session1.h"
//#include <stdio.h>

//extern Graphics gpDC;
static Session1* se = 0;
Session1::Session1()
{
    /// @TODO Auto-generated constructor stub

}

Session1::~Session1()
{
    //DELIMG(ID_se1);
}

Page* createSession1()
{
    if(se == 0)
    {
      se = SafeNew Session1;
    }
    se->_page.init = Session1::init;
    se->_page.onDestory = onDestory;
    se->_page.onPaint = Session1::onPaint;
    se->_page.running = Session1::running;

    return &se->_page;
}

void Session1::onPaint()
{
    Img* p =  GETIMG(ID_se1);
    //p =  GETIMG(ID_background);
    PAINT->drawImage(p, 0, 0, ACHOR_LT);
    //printf("0x%0x\n",p);
    return;
}

int Session1::init()
{
    return 0;
}
void onDestory() ///< 释放资源函数指针
{
    SafeDelete(se);
    se = 0;
}
void Session1::running() ///< 处理游戏逻辑的函数指针
{

}
