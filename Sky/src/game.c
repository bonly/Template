#pragma warning(disable:4244)
#include "mrc_base.h"
#include "i18n.h"
#include "res_str.h"
#include "game.h"
#include "pre.h"
#include "image.h"
#include "Container.h"

static T_IMG   *bk;
static T_IMG   plane;
static int32 timerH;
static int32 isSoundOn;

void GamePaint(int32 data)
{
	mr_screeninfo ms;
	int32  iCount = 0, iIndex = 0;
	int32  iY = 0;
	static  int32 planeX = 0, planeY = 0;
	int32 w = 0, h = 0;

	mrc_memset(&ms, 0, sizeof(mr_screeninfo));
	mrc_getScreenInfo(&ms);
	iCount = ms.height / bk->height;
	iY = (ms.height - bk->height * iCount) / 2;

	mrc_clearScreen(0, 0, 0);

	{
		//绘制飞机主体
		for(iIndex = 0; iIndex < iCount; iIndex++)
		{		
			mrc_bitmapShowEx(bk->pImg, 0, iY, bk->width, bk->width, bk->height, BM_COPY, 0, 0);
			iY += bk->height;
		}

		mrc_bitmapShowEx(plane.pImg, planeX, planeY, plane.width, plane.width, plane.height, BM_TRANSPARENT, 0, 0);

		mrc_drawText((char*)SGL_LoadString(STR_HELLO_STR), planeX, planeY + plane.height, 255, 255, 255, TRUE, MR_FONT_MEDIUM);

		planeX += 5;
		planeY += 5;
		if(planeX > ms.width)
		{
			planeX = 0;
		}
		if(planeY > ms.height)
		{
			planeY = 0;
		}
	}

	{
		//绘制Title
		w = h = 0;
		if( (MR_SUCCESS == mrc_unicodeTextWidthHeight((uint16*)SGL_LoadString(STR_GAME_TITLE), MR_FONT_MEDIUM, &w, &h)) && w > 0 && h > 0)
		{
			mrc_drawText((char*)SGL_LoadString(STR_GAME_TITLE), (ms.width - w) / 2, 0, 255, 255, 255, TRUE, MR_FONT_MEDIUM);
		}
	}

	{
		//绘制功能菜单
		w = h = 0;
		if( (MR_SUCCESS == mrc_unicodeTextWidthHeight((uint16*)SGL_LoadString(STR_GAME_RETURN), MR_FONT_MEDIUM, &w, &h)) && w > 0 && h > 0)
		{
			mrc_drawText((char*)SGL_LoadString(STR_GAME_RETURN), ms.width - w, ms.height - h, 255, 255, 255, TRUE, MR_FONT_MEDIUM);
		}
		
	}
	

	mrc_refreshScreen(0, 0, ms.width, ms.height);		
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
	//图片初始化
	//mrc_memset(&bk, 0, sizeof(T_IMG));
	mrc_memset(&plane, 0, sizeof(T_IMG));
	//bk.pImg = (uint16*)mrc_readFileFromMrp("bk.bmp", &bk.dataLen, 0);
  bk = GETIMG(ID_bk);
  load_bk(0);
	plane.pImg = (uint16*)mrc_readFileFromMrp("plane.bmp", &plane.dataLen, 0);
	if(bk->pImg)
	{
		bk->width = 240;
		bk->height = 44;		
	}

	if(plane.pImg)
	{
		plane.width = 41;
		plane.height = 26;
	}

	if(bk->pImg && plane.pImg)
	{
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
  /*
	if(bk.pImg)
	{
		mrc_freeFileData(bk.pImg, bk.dataLen);
		mrc_memset(&bk, 0, sizeof(bk));
	}
  */
  DELIMG(ID_bk);
	if(plane.pImg)
	{
		mrc_freeFileData(plane.pImg, plane.dataLen);
		mrc_memset(&plane, 0, sizeof(plane));
	}
#ifndef SDK_MOD  //模拟器上注册打开/关闭声音会死机的
	mrc_soundStop(0);
#endif

    DELTASK();
    DELIMGPOOL();
    DELCONTPOOL();
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
	if(code == MR_KEY_RELEASE)
	{
		if(param0 == MR_KEY_SOFTRIGHT)
		{
			mr_screeninfo ms;
			mrc_memset(&ms, 0, sizeof(ms));
			mrc_clearScreen(0, 0, 0);
			mrc_drawText("退出中", 0, 0, 255, 255, 255, FALSE, MR_FONT_MEDIUM);
			mrc_refreshScreen(0, 0, ms.width, ms.height);
			mrc_exit();
		}
	}
}