/**
 @file APageScreen.cpp
 */
#include "APageScreen.h"
#include "osport.h"
#include "../Tools/pre.h"
#include "../Tools/Image.h"
#include "../Tools/Container.h"
#include "../Tools/Paint.h"
//ȫ�ֵ�dc
Graphics     gpDC;
//ȫ�ֵ�shell
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

    //STEP 0: �ڹ��캯���м�¼ȫ��DC��SHELL�� �������ʹ��
    gpDC        = m_pGlobal->m_pGraphics;
    gpShell     = m_pGlobal->m_pMe->m_pIShell;

    gpDC->setClip();

    //STEP 1: ��Ϸ�ĳ�ʼ������
    // GameInit();

    return 0;
}
int CAPageScreen::OnDestroy(void)
{

    //STEP 8 �˳�Ӧ��ʱ���ͷ����е���Դ    
    CancelTimer();

    //GameRelease();
    DELTASK();
    DELIMGPOOL();
    DELCONTPOOL();
    DELCONF();
    DELPAINT();
    return 0;
}

//FALSE��ʾδ������Ϣ�� TRUE��ʾ��������Ϣ
BOOL CAPageScreen::OnWndProc(void* pi, AEEEvent eCode , uint16 wParam , uint32 dwParam)
{
    BOOL bRet = CBaseScreen::OnWndProc(pi, eCode, wParam, dwParam);

    return bRet;
}

//����������
void CAPageScreen::OnShow(BOOL bShow)
{
    //STEP 2   �������ɹ��� ϵͳ���Զ����õ�ǰ���ڵ�ONSHOW
    //����ֻ��һ��window��ͨ��״̬�����Ƶ���Ϸ���ԣ� �����
    //��Ϸ������ڣ� ������������ʱ��
    //���ֻ��һ����ʱ���� �򴰿ڵ�ȱʡ��ʱ���Ѿ�������
    //��ontimer�д�����Ϸ���߼�
        m_bVisible = TRUE;
        //��ǰ̨�ˣ� �򱳾���
        gpDC->SetBackLight(TRUE);
        //ͨ����ʱ����ʽ������Ϸ���߼�, 1�����������
        SetTimer(1);
}

AECHAR  test[]={'h', 'l', 0};

int CAPageScreen::OnPaint(void* pi)
{
    //STEP 4: ��Ϸ�����߼��ɷ�������
    //���ÿ֡�Ļ���
    //���Դ���ֻ��ˢ�ɺ�ɫ(����)

    if (!m_bVisible)    return 0;

    gpDC->setColor(0);
    gpDC->clearScreen();
    TASKS->onPaint(pi);
    
    return 0;
}

void CAPageScreen::OnTimer(void)
{
  TASKS->run(0);
        //STEP 3 ��Ϸ��ʱ���ص�, �����������Ϸ�����߼�
        //���߼�
        OnPaint(NULL);

        //STEP 6  ���DEMO��Ϸ����ɺ��Ȼˢ�����Ѹ��µ���Ϸ����ˢ�µ���Ļ)
        //����java��servicerepaints
        //������Ϸ���Ƿ�ˢ��Ҳ���Է������߼���״̬�����Լ�����
        //ˢ��
        gpDC->FlushScreen();

        //����һ���򵥵Ķ�ʱ���������ӣ�������һ�ζ�ʱ��
        //������JAVA��  thread:sleep����
        //������30FPS���£� �����ǰʱ��С��30MS�� ����SLEEPʱ��
        //�����Ϸ�Ƚϼ򵥣�����׷���ٶȣ� ֻҪSetTimer(5)�ͺ���
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
    //�����ʱӦ��ֹͣ��ʱ���� �ر�����
    // �������ͷ���Դ
    //���������ͷ�򵥵Ĺر��˶�ʱ��

    CBaseScreen::OnSuspend();

    CancelTimer();
    
    return TRUE;
}

BOOL CAPageScreen::OnResume()
{
    //STEP 7
    //�ָ�ʱӦ������������ʱ���� �ָ���Դ
    //���������ͷ�򵥵������˶�ʱ��
    //ͨ����ʱ�������߼�����

    CBaseScreen::OnResume();

    SetTimer(1);

    return TRUE;
}
BOOL CAPageScreen::OnKeyPressed(int keyCode)
{
    //STEP 5  ������Ϣ���� ���DEMO��Ϸ�Ǽ�¼��ֵ��ʽ��
    //������Ϸ�����������Ϸ�߼�/״̬��ֱ��Ӱ�죬 ���Ծ��ڴ˴�����
    //BREWKEY2JAVA�ɽ���Ϸ����JAVA��
    //int i = BrewKey2Java(keyCode);

    //������˳���
    if(AVK_SOFT1 == keyCode)
        destroyApp(false);

    KeyPressedListen(keyCode, CURPAGE->page);

    return TRUE;
}

BOOL CAPageScreen::OnKeyReleased(int keyCode)
{
    //STEP 5  ������Ϣ����-���� ���DEMO��Ϸ�Ǽ�¼��ֵ��ʽ��
    //������Ϸ�����������Ϸ�߼�/״̬��ֱ��Ӱ�죬 ���Ծ��ڴ˴�����

    int i = BrewKey2Java(keyCode);

    KeyReleasedListen(keyCode, CURPAGE->page);

    return TRUE; //�Ѵ���KEY�¼�
}

BOOL CAPageScreen::OnPointerPressed(int x, int y)
{
    //     m_pGlobal->m_pKey->forceClear();
    // 
    //     m_pGlobal->m_pKey->pointerDown(x, y);
    //     m_pGlobal->m_pKey->setSavePointerPos(x, y); //���ü�¼Pointer_Downλ��
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

