#include "AEEModGen.h"          // Module interface definitions
#include "AEEAppGen.h"          // Applet interface definitions

#include "AppGlobal.h"

static boolean STD_HandleEvent(AEEApplet * pme, AEEEvent eCode,uint16 wParam, uint32 dwParam);

int AEEClsCreateInstance(AEECLSID ClsId,IShell * pIShell,IModule * pMod,void ** ppObj)
{
   *ppObj = NULL;

   if(AEEApplet_New(sizeof(AEEApplet) + sizeof(AppBasic), // Size of our private class
	   ClsId,                              // Our class ID
	   pIShell,                            // Shell interface
	   pMod,                               // Module instance
	   (IApplet**)ppObj,                   // Return object
	   (AEEHANDLER)STD_HandleEvent,        // Our event handler
	   NULL))                              // No special "cleanup" function
	   return(AEE_SUCCESS);
   
   return (EFAILED);
}

static boolean STD_HandleEvent(AEEApplet * pMe, AEEEvent eCode, uint16 wParam, uint32 dwParam)
{
	if (EVT_APP_START == eCode)
	{
		if (0 != AppGlobal::StartApp(pMe, wParam, dwParam)) 
		{
			ISHELL_CloseApplet(pMe->m_pIShell, 0);
		}
		return TRUE;
	}
	else if (EVT_APP_STOP == eCode)
	{
		AppGlobal::StopApp(pMe, wParam, dwParam);
		return TRUE;
	}
	else
	{	
		return AppGlobal::WndProc(pMe, eCode, wParam, dwParam);
	}
	return FALSE;
}
