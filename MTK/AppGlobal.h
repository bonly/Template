#ifndef _STD_GLOBAL_H
#define _STD_GLOBAL_H

//java
#include "JDefine.h"
#include "JSystem.h"
#include "JKey.h"
#include "JGraphics.h"
#include "JVector.h"
#include "JRect.h"
#include "JImage.h"
#include "JWStringBuffer.h"
#include "JStringBuffer.h"
#include "JFileInputStream.h"
#include "JFileOutputstream.h"


//screen
#include "BaseScreen.h"

//util

#define GETAPPGLOBAL() ((AppGlobal*)(GETAPPBASIC()->pAppGlobal))
#define GETSTRING(x) GETAPPGLOBAL()->m_strings[x]

#define APP_GLOBAL_GetWorkBuf() GETAPPGLOBAL()->m_pBuf1

#define APP_GLOBAL_DefBufSize  1024
#define APP_GLOBAL_DefTimerValue 200

#define  APP_GLOBAL_DefUrlSize 512



enum ERes_ImageIndex
{
	ERes_ImageIndex_abc,
	ERes_ImageIndex_num,
	ERes_ImageIndex_chatarrow,
};

typedef struct UrlData 
{
	char szUrl[1024];
	unsigned int nId;
}UrlData, *PUrlData;


typedef struct AppSetting
{
	unsigned int uBacklight;	//打开背光
	unsigned int uInput;		//自带输入法
}AppSetting, *PAppSetting;

enum EAppSetting_Index
{	
	EAppSetting_Index_BackLight = 0,
	EAppSetting_Index_Input,
};	

enum EAppSetting_Backlight
{
	EAppSetting_Backlight_Open = 0,
	EAppSetting_Backlight_Close,
	EAppSetting_Backlight_MAX,
};

enum EAppSetting_Input
{
	EAppSetting_Input_Program = 0,
	EAppSetting_Input_System,
	EAppSetting_Input_MAX,
};

enum EAppUrl_Index
{
	EAppUrl_Index_Main = 0,
	EAppUrl_Index_PayCenter,
	EAppUrl_Index_BBS,
};

class CBaseScreen;

class AppGlobal
{
public:
	static int  StartApp(AEEApplet* pMe, unsigned short wParam, unsigned int dwParam);
	static void StopApp(AEEApplet* pMe, unsigned short wParam, unsigned int dwParam);
	
	static void DoEnterScreen(CBaseScreen* pWin);
	static void DoLeaveScreen(CBaseScreen* pWin);
	static void EnterNewScreen(CBaseScreen* pWin);
	
	static BOOL WndProc(void* pi, AEEEvent eCode , uint16 wParam , uint32 dwParam); // 窗口主消息处理函数

	int	 GetCmnetIap();
	int  GetCmwapIap();



	BOOL IsSupportSystemIME();
	static void SetSystemBacklight(BOOL bOpen);

private:
	AppGlobal(void);
	~AppGlobal(void);

	static int  Create(AEEApplet* pMe, unsigned short wParam, unsigned int dwParam);
	static void Destory();	
	
	void Init();
	int CreateUtil();
	void DestoryUtil();

	int CreateScreen();
	void DestoryScreen();

public:
	AEEApplet*		m_pMe;
	JGraphics*		m_pGraphics;
	JKey*			m_pKey;
	JFileOutputStream* m_pFileout;
	JFileInputStream* m_pFilein;

	char            m_pBuf1[APP_GLOBAL_DefBufSize];

	CBaseScreen*    m_pCurrentScreen;
	
	CBaseScreen*	m_pAPageScreen;

	JWStringBuffer* m_pWStringBuffer;

	AppSetting	    m_AppSetting;
}; 

extern void CheckAndFillFullVirtualScreen();

//#ifdef ROM_VERSION
//extern const unsigned char _abc_png[368];
//extern const unsigned char _chatarrow_png[1276];
//extern const unsigned char _cmtv_png[1232];
//extern const unsigned char _info_png[1560];
//extern const unsigned char _logo_hv_png[9672];
//extern const unsigned char _logo_lt_png[3308];
//extern const unsigned char _num_png[248];
//extern const unsigned char _panel_png[3436];
//extern const unsigned char _pause_png[476];
//extern const unsigned char _play_png[532];
//extern const unsigned char _playgray_png[396];
//extern const unsigned char _secicon_png[304];
//extern const unsigned char _silence_png[440];
//extern const unsigned char _volume_png[220];
//#endif

#endif