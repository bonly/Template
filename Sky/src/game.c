#include "pre.h"
#if WIN32 
#pragma warning(disable:4244)
#endif
#include "mrc_base.h"
#include "i18n.h"
#include "res_str.h"
#include "game.h"

static int32 timerH;
static int32 isSoundOn;

void GamePaint(int32 data)
{
	int32  iCount = 0, iIndex = 0;
	int32  iY = 0;
	static  int32 planeX = 0, planeY = 0;
	int32 w = 0, h = 0;

  TASKS->run(0);
  TASKS->onPaint(0);

	mrc_refreshScreen(0, 0, PAINT->ScreenWidth, PAINT->ScreenHeight);		
}

void Game_Start()
{
	isSoundOn = FALSE;
	//������ʼ��
	if(MR_SUCCESS == mrc_soundSet(0, "bk.mid", MR_SOUND_MIDI))
	{
		mrc_soundPlay(0, 1);
		isSoundOn = TRUE;
	}

	timerH = mrc_timerCreate();
	if(timerH)
	{
		mrc_timerStart(timerH, 100, 0, (mrc_timerCB)GamePaint, 1);
	}
	else
	{
		mrc_exit();
	}
}
void Game_Pause(void)
{
	if(timerH)
		mrc_timerStop(timerH);
	if(isSoundOn)
		mrc_soundStop(0);
	
}
void Game_Resume(void)
{
	if(timerH)
		mrc_timerStart(timerH, 100, 0, (mrc_timerCB)GamePaint, 1);
	if(isSoundOn)
		mrc_soundPlay(0, 1);
}

void Game_ReleaseSource(void)
{
#ifndef SDK_MOD  //ģ������ע���/�ر�������������
	mrc_soundStop(0);
#endif

    DELTASK();
    DELIMGPOOL();
    DELCONTPOOL();
    DELPAINT();
    DELCONF();

	mrc_soundSet(0, "*", MR_SOUND_MIDI);

	if(timerH)
	{
		mrc_timerStop(timerH);
		mrc_timerDelete(timerH);
		timerH = 0;
	}
}
void Game_KeyCheck(int32 code, int32 param0, int32 param1)
{
    switch( code )
    {
      case MR_KEY_PRESS :     //����ѹ���¼�
        {
          break;
        }
      case MR_KEY_DOWN:
        {
          break;
        }
      case MR_KEY_SOFTRIGHT:  //�����
        {
          mr_screeninfo ms;
          mrc_memset(&ms, 0, sizeof(ms));
          mrc_clearScreen(0, 0, 0);
          mrc_drawText("�˳���", 0, 0, 255, 255, 255, FALSE, MR_FONT_MEDIUM);
          mrc_refreshScreen(0, 0, ms.width, ms.height);
          mrc_exit();
        }
      case MR_KEY_RELEASE :   //�����ͷ��¼�
        {
           if(param0 == MR_KEY_SOFTRIGHT); //���� �����
           break;
        }
      case MR_MOUSE_UP:       //�������ͷ�
        {
          break;
        }
      case MR_MOUSE_DOWN:     //�����¼�������
        {
          PointerPressedListen(param0, param1, CURPAGE->page);
          break;
        }
    }
}