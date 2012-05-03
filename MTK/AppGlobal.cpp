#include "AppGlobal.h"
#include "APageScreen.h"



AppGlobal::AppGlobal(void)
{

}
	
AppGlobal::~AppGlobal(void)
{
	
}

int AppGlobal::StartApp(AEEApplet* pMe, unsigned short wParam, unsigned int dwParam)
{	
	int iRet = JSystem::Create(); //初始化app_basic
	if (0 != iRet) return iRet;
	
	iRet = Create(pMe, wParam, dwParam);
	if (0 != iRet) return iRet;
	

	EnterNewScreen(GETAPPGLOBAL()->m_pAPageScreen);

	return 0;
}

void AppGlobal::StopApp(AEEApplet* pMe, unsigned short wParam, unsigned int dwParam)
{
	Destory(); //销毁app_global
	JSystem::Destroy(); //销毁app_basic
}

BOOL AppGlobal::WndProc(void* pi, AEEEvent eCode , uint16 wParam , uint32 dwParam) // 窗口主消息处理函数
{
#ifndef AEE_SIMULATOR	//真机上这里需要调用appman的亮灯接口了
	if (eCode == EVT_KEY )
	{
		GetHelperExt()->APP_mmi_idle_key_event_backlight_check();
	}
#endif
	AppGlobal* pAppGlobal = GETAPPGLOBAL();
	if (pAppGlobal && pAppGlobal->m_pCurrentScreen)
	{
		return pAppGlobal->m_pCurrentScreen->OnWndProc(pi, eCode, wParam, dwParam);
	}
	return FALSE;
}

void AppGlobal::DoEnterScreen(CBaseScreen* pWin)
{
	GETAPPGLOBAL()->m_pCurrentScreen = pWin;
	if(pWin) pWin->OnShow(TRUE); 
}
void AppGlobal::DoLeaveScreen(CBaseScreen* pWin)
{
	if(pWin) pWin->OnShow(FALSE);
}
void AppGlobal::EnterNewScreen(CBaseScreen* pWin)
{
	DoLeaveScreen(GETAPPGLOBAL()->m_pCurrentScreen);
	DoEnterScreen(pWin);
}

int AppGlobal::Create(AEEApplet* pMe, unsigned short wParam, unsigned int dwParam)
{
	int iRtn = 0;
	AppBasic* pBasic = GETAPPBASIC();
	if (!pBasic) return 301;
	
	pBasic->pAppGlobal = SafeNew AppGlobal(); //创建global
	if (!pBasic->pAppGlobal) return 302;

	AppGlobal* pGlobal = GETAPPGLOBAL();
	pGlobal->Init();
	pGlobal->m_pMe = pBasic->pAeeApplet;
	
	pGlobal->m_pGraphics = SafeNew JGraphics(pBasic->pAeeApplet->m_pIDisplay); //创建graphics
	if (!pGlobal->m_pGraphics) return 304;

	pGlobal->m_pFileout = SafeNew JFileOutputStream("./data.txt"); //创建fileout
	if (!pGlobal->m_pFileout) return 306;

	pGlobal->m_pFilein = SafeNew JFileInputStream("./data.txt"); //创建filein
	if (!pGlobal->m_pFilein) return 307;
	
	pGlobal->m_pKey = SafeNew JKey(); //创建key
	if (!pGlobal->m_pKey) return 305;
	pGlobal->m_pKey->setUseNumberDirect(FALSE);

	iRtn = pGlobal->CreateUtil();
	if (SUCCESS != iRtn) return iRtn;
	
	iRtn = pGlobal->CreateScreen();
	if (SUCCESS != iRtn) return iRtn;
	

	return SUCCESS;
}

void AppGlobal::Destory()
{
#ifdef DEBUG_VERSION
	DBGPRINTF("SafeDelete(----->AppGlobal::Destory()\r\n");
#endif
	AppBasic* pBasic = GETAPPBASIC();
	if (pBasic)
	{
		AppGlobal* pGlobal = GETAPPGLOBAL();
		
		if (pGlobal)
		{
			pGlobal->DestoryScreen();
			pGlobal->DestoryUtil();
		
			SafeDelete(pGlobal->m_pKey);
			SafeDelete(pGlobal->m_pGraphics);
			//
			SafeDelete(pGlobal->m_pFileout);
			SafeDelete(pGlobal->m_pFilein);
		}
		SafeDelete(pBasic->pAppGlobal);
	}
}

void AppGlobal::Init()
{
	m_pMe = NULL;
	m_pGraphics = NULL;
	m_pKey = NULL;


	m_pCurrentScreen = NULL;
	m_pAPageScreen = NULL;

	m_pWStringBuffer = NULL;

	ZeroMemory(&m_AppSetting, sizeof(AppSetting));
	m_AppSetting.uBacklight = EAppSetting_Backlight_Open;
	m_AppSetting.uInput = EAppSetting_Input_Program;
}

int AppGlobal::CreateUtil()
{

	if (!m_pWStringBuffer) m_pWStringBuffer = SafeNew JWStringBuffer(128);
	if (!m_pWStringBuffer) return 308;

	return SUCCESS;
}

void AppGlobal::DestoryUtil()
{
	SafeDelete(m_pWStringBuffer);
}

int AppGlobal::CreateScreen()
{
 	if (!m_pAPageScreen) m_pAPageScreen = SafeNew CAPageScreen();
 	if (!m_pAPageScreen) return 404;



	return SUCCESS;
}

void AppGlobal::DestoryScreen()
{
	SafeDelete(m_pAPageScreen);
}


int	AppGlobal::GetCmnetIap()
{
	//设置接入点
	const WCHAR szCmnet[] = {'c','m','n','e','t', '\0'};
#ifndef AEE_SIMULATOR
	int profileCount = INETMGR_GetProfileSize(GETAPPBASIC()->pINetMgr);
	int nCmnet = -1;
	APP_GPRSDataAccountNode* profileNode = (APP_GPRSDataAccountNode*) SafeMalloc(sizeof(APP_GPRSDataAccountNode));
	for (int i = 0 ; i < profileCount; i ++)
	{	

		INETMGR_GetDataAccount(GETAPPBASIC()->pINetMgr, i, profileNode);
		WSTRLOWER((WCHAR*)profileNode->APN);

		if (0 == WSTRCMP((WCHAR*)profileNode->APN, szCmnet))// "cmnet"))
		{
			nCmnet = i;
			break;
		}
	}
	SafeFree(profileNode);

	if (nCmnet >= 0)
	{
#ifdef DEBUG_VERSION
		DBGPRINTF("set cmnet at %d\r\n", nCmnet);
#endif
		return nCmnet;
	}	
	else
	{
#ifdef DEBUG_VERSION
		DBGPRINTF("set default at %d\r\n", nCmnet);
#endif
		return 1;
	}
#else
	return 1;
#endif
}

int AppGlobal::GetCmwapIap()
{
	//设置接入点
	const WCHAR szCmwap[] = {'c','m','w','a','p', '\0'};
#ifndef AEE_SIMULATOR
	int profileCount = INETMGR_GetProfileSize(GETAPPBASIC()->pINetMgr);
	int nCmwap = -1;
	APP_GPRSDataAccountNode* profileNode = (APP_GPRSDataAccountNode*) SafeMalloc(sizeof(APP_GPRSDataAccountNode));
	for (int i = 0 ; i < profileCount; i ++)
	{	

		INETMGR_GetDataAccount(GETAPPBASIC()->pINetMgr, i, profileNode);
		WSTRLOWER((WCHAR*)profileNode->APN);

		if (0 == WSTRCMP((WCHAR*)profileNode->APN, szCmwap))// "cmwap"))
		{
			nCmwap = i;
			break;
		}
	}
	SafeFree(profileNode);

	if (nCmwap >= 0)
	{
#ifdef DEBUG_VERSION
		DBGPRINTF("set nCmwap at %d\r\n", nCmwap);
#endif
		return nCmwap;
	}	
	else
	{
#ifdef DEBUG_VERSION
		DBGPRINTF("set default at %d\r\n", nCmwap);
#endif
		return 0;
	}
#else
	return 0;
#endif
}




BOOL AppGlobal::IsSupportSystemIME()
{
	return FALSE;
}


void AppGlobal::SetSystemBacklight(BOOL bOpen)
{
	AEEApplet* pMe = (AEEApplet*)GETAPPINSTANCE();
	if (pMe)
	{
		if (bOpen)
		{
			IDISPLAY_Backlight(pMe->m_pIDisplay, TRUE);
		}
		else
		{
			IDISPLAY_Backlight(pMe->m_pIDisplay, FALSE);
		}
	}
}

void CheckAndFillFullVirtualScreen()
{
	/*
	#ifndef AEE_SIMULATOR
	uint32 iDeviceWidth = 0;
	int size = sizeof(iDeviceWidth);
	ISHELL_GetDeviceInfoEx(JSystem::s_pIShell, 0x7fff+10, (void *)&iDeviceWidth, &size);

	if (gpGraphics && iDeviceWidth != gpGraphics->getDBRc()->getWidth())
	{
	#ifndef KZhanXunPlat
	// 展讯平台不需要调用
	FillFullVirtualScreen();
	#endif
	}
	#endif
	*/
}
