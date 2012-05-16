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
	//声音初始化
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
#ifndef SDK_MOD  //模拟器上注册打开/关闭声音会死机的
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
      case MR_KEY_PRESS :     //按键压下事件
        {
          break;
        }
      case MR_KEY_DOWN:
        {
          break;
        }
      case MR_KEY_SOFTRIGHT:  //左软件
        {
          mr_screeninfo ms;
          mrc_memset(&ms, 0, sizeof(ms));
          mrc_clearScreen(0, 0, 0);
          mrc_drawText("退出中", 0, 0, 255, 255, 255, FALSE, MR_FONT_MEDIUM);
          mrc_refreshScreen(0, 0, ms.width, ms.height);
          mrc_exit();
        }
      case MR_KEY_RELEASE :   //按键释放事件
        {
           if(param0 == MR_KEY_SOFTRIGHT); //按键 右软键
           break;
        }
      case MR_MOUSE_UP:       //触摸屏释放
        {
          break;
        }
      case MR_MOUSE_DOWN:     //触屏事件处理按下
        {
          PointerPressedListen(param0, param1, CURPAGE->page);
          break;
        }
    }
}