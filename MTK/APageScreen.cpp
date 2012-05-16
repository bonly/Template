/**
 @file APageScreen.cpp
 */
#include "APageScreen.h"
#include "osport.h"
#include "../Tools/pre.h"
#include "../Tools/Image.h"
#include "../Tools/Container.h"
#include "../Tools/Paint.h"
//全局的dc
Graphics     gpDC;
//全局的shell
IShell*      gpShell;

int framecnt = 0;

CAPageScreen::CAPageScreen():CBaseScreen()
{
    OnCreate(NULL);
}

CAPageScreen::~CAPageScreen()
{
    OnDestroy();
}

int CAPageScreen::OnCreate(void* pi)
{

    //STEP 0: 在构造函数中记录全局DC和SHELL， 方便后续使用
    gpDC        = m_pGlobal->m_pGraphics;
    gpShell     = m_pGlobal->m_pMe->m_pIShell;

    gpDC->setClip();

    //STEP 1: 游戏的初始化工作
    // GameInit();

    return 0;
}
int CAPageScreen::OnDestroy(void)
{

    //STEP 8 退出应用时，释放所有的资源    
    CancelTimer();

    //GameRelease();
    DELTASK();
    DELIMGPOOL();
    DELCONTPOOL();
    DELCONF();
    DELPAINT();
    return 0;
}

//FALSE表示未处理消息， TRUE表示处理了消息
BOOL CAPageScreen::OnWndProc(void* pi, AEEEvent eCode , uint16 wParam , uint32 dwParam)
{
    BOOL bRet = CBaseScreen::OnWndProc(pi, eCode, wParam, dwParam);

    return bRet;
}

//代码的总入口
void CAPageScreen::OnShow(BOOL bShow)
{
    //STEP 2   当创建成功后， 系统会自动调用当前窗口的ONSHOW
    //对于只有一个window，通过状态机控制的游戏而言， 这个是
    //游戏的总入口， 在这里启动定时器
    //如果只有一个定时器， 则窗口的缺省定时器已经够用了
    //在ontimer中处理游戏主逻辑
        m_bVisible = TRUE;
        //到前台了， 打背景灯
        gpDC->SetBackLight(TRUE);
        //通过定时器正式启动游戏主逻辑, 1个毫秒后启动
        SetTimer(1);
}

AECHAR  test[]={'h', 'l', 0};

int CAPageScreen::OnPaint(void* pi)
{
    //STEP 4: 游戏的主逻辑可放在这里
    //完成每帧的绘制
    //测试代码只是刷成黑色(清屏)

    if (!m_bVisible)    return 0;

    gpDC->setColor(0);
    gpDC->clearScreen();
    TASKS->onPaint(pi);
    
    return 0;
}

void CAPageScreen::OnTimer(void)
{
  TASKS->run(0);
        //STEP 3 游戏定时器回调, 在这里调用游戏的主逻辑
        //主逻辑
        OnPaint(NULL);

        //STEP 6  这个DEMO游戏是完成后必然刷屏（把更新的游戏画面刷新到屏幕)
        //类似java的servicerepaints
        //其他游戏，是否刷屏也可以放在主逻辑的状态机中自己处理
        //刷屏
        gpDC->FlushScreen();

        //这是一个简单的定时器处理例子，启动下一次定时器
        //类似于JAVA的  thread:sleep操作
        //限制在30FPS以下， 如果当前时间小于30MS， 计算SLEEP时间
        //如果游戏比较简单，或者追求速度， 只要SetTimer(5)就好了
        SetTimer(200); 
    /*
    if(TASKS->current_page == 0)
    {
        TASKS->next_page = 1;
        TASKS->operation = NEXT_PAGE;
    }
    else
    {
        TASKS->next_page = 0;
        TASKS->operation = NEXT_PAGE;
    }
    */
}

BOOL CAPageScreen::OnSuspend()
{
    //STEP 6
    //被打断时应当停止定时器， 关闭网络
    // 尽可能释放资源
    //这个例子里头简单的关闭了定时器

    CBaseScreen::OnSuspend();

    CancelTimer();
    
    return TRUE;
}

BOOL CAPageScreen::OnResume()
{
    //STEP 7
    //恢复时应当重新启动定时器， 恢复资源
    //这个例子里头简单的重启了定时器
    //通过定时器驱动逻辑运行

    CBaseScreen::OnResume();

    SetTimer(1);

    return TRUE;
}
BOOL CAPageScreen::OnKeyPressed(int keyCode)
{
    //STEP 5  按键消息处理， 这个DEMO游戏是记录键值方式的
    //其他游戏如果按键对游戏逻辑/状态有直接影响， 可以均在此处处理
    //BREWKEY2JAVA可将游戏码变成JAVA的
    //int i = BrewKey2Java(keyCode);

    //左软件退出！
    if(AVK_SOFT1 == keyCode)
        destroyApp(false);

    KeyPressedListen(keyCode, CURPAGE->page);

    return TRUE;
}

BOOL CAPageScreen::OnKeyReleased(int keyCode)
{
    //STEP 5  按键消息处理-弹起， 这个DEMO游戏是记录键值方式的
    //其他游戏如果按键对游戏逻辑/状态有直接影响， 可以均在此处处理

    int i = BrewKey2Java(keyCode);

    KeyReleasedListen(keyCode, CURPAGE->page);

    return TRUE; //已处理KEY事件
}

BOOL CAPageScreen::OnPointerPressed(int x, int y)
{
    //     m_pGlobal->m_pKey->forceClear();
    // 
    //     m_pGlobal->m_pKey->pointerDown(x, y);
    //     m_pGlobal->m_pKey->setSavePointerPos(x, y); //设置记录Pointer_Down位置
    //     m_pGlobal->m_pKey->setPrePointerDnTime(currentTimeMillis());

    PointerPressedListen(x,y,CURPAGE->page);
    BOOL bRet = FALSE;

    return bRet;
}
BOOL CAPageScreen::OnPointerDragged(int x, int y)
{
    //     m_pGlobal->m_pKey->pointerMove(x, y);

    BOOL bRet = FALSE;
    PointerDraggedListen(x, y,CURPAGE->page);

    return bRet;
}
BOOL CAPageScreen::OnPointerReleased(int x, int y)
{
    //    m_pGlobal->m_pKey->pointerUp(x, y);

    BOOL bRet = FALSE;
    PointerReleasedListen(x,y,CURPAGE->page);

    return bRet;
}

