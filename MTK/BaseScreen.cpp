#include "BaseScreen.h"



static void UTL_CB_Timer(void * pData)
{
	if(pData)
	{
		((CBaseScreen*)pData)->OnTimer();
	}
}

CBaseScreen::CBaseScreen(void)
{
	OnCreate(NULL);
}

CBaseScreen::~CBaseScreen(void)
{
	OnDestroy();
}

// ���ڱ�������ʱ���յ�����Ϣ
int CBaseScreen::OnCreate(void* /*pi*/)
{
	m_bTimerOn = FALSE;
	m_bVisible = TRUE;
	m_bNeedRedraw = FALSE;
	
	m_pGlobal = GETAPPGLOBAL();
	
	SetParrent(NULL);
	
	return 0;
}

// ���ڱ�����ʱ�յ�������
int CBaseScreen::OnDestroy(void)
{
	if (m_bTimerOn) CancelTimer();
	return 0;
}

void CBaseScreen::OnShow(BOOL bShow) // ������Ҫ��ʾ�������ص�ʱ���յ�����Ϣ
{
	if (bShow)
	{
		m_pGlobal->m_pKey->forceClear();
		m_bVisible = TRUE;
	}
	else
	{
		m_parent = NULL;
		m_bNeedRedraw = FALSE;
		m_bVisible = FALSE;
		
		CancelTimer();
	}
}

BOOL CBaseScreen::OnWndProc(void* /*pi*/, AEEEvent eCode , uint16 wParam , uint32 dwParam) // ��������Ϣ������
{
	BOOL bRet = FALSE;
	switch (eCode)
	{
	case EVT_KEY_PRESS:
		{
			bRet = OnKeyPressed(wParam);
		}
		break;
	case EVT_KEY_RELEASE:
		{
			bRet = OnKeyReleased(wParam);
		}
		break;
	case EVT_KEY_HELD:
		{
			//ע��������Ϣû�д���
		}
		break;
	case EVT_APP_SUSPEND:
		{
			bRet = OnSuspend();
		}
		break;
	case EVT_APP_RESUME:
		{
			bRet = OnResume();
		}
		break;
	case EVT_EXT_PEN_PRESS:
		{
			
			bRet = OnPointerPressed((int)wParam, (int)dwParam);
		}
		break;
	case EVT_EXT_PEN:
		{
			bRet = OnPointerDragged((int)wParam, (int)dwParam);
		}
		break;
	case EVT_EXT_PEN_RELEASE:
		{
			bRet = OnPointerReleased((int)wParam, (int)dwParam);
		}
		break;
	default:
		break;
	}
	return bRet;
}

BOOL CBaseScreen::OnSuspend()
{
	m_bVisible = FALSE;
	if (m_bTimerOn) CancelTimer();
	return TRUE;
}
BOOL CBaseScreen::OnResume()
{
	m_bVisible = TRUE;
	m_pGlobal->m_pKey->forceClear();
	return TRUE;
}

BOOL CBaseScreen::OnKeyPressed(int /*keyCode*/)
{
	return FALSE;
}

BOOL CBaseScreen::OnKeyReleased(int /*keyCode*/)
{
	return FALSE;
}

BOOL CBaseScreen::OnPointerPressed(int /*x*/, int /*y*/)
{
	return FALSE;
}
BOOL CBaseScreen::OnPointerDragged(int /*x*/, int /*y*/)
{
	return FALSE;
}
BOOL CBaseScreen::OnPointerReleased(int /*x*/, int /*y*/)
{
	return FALSE;
}

// ���ڻ��ƽӿ�
int CBaseScreen::OnPaint(void* /*pi*/)
{
	return 0;
}

// ���ô��ڶ�ʱ��
int CBaseScreen::SetTimer(int nMs)
{
	int rtn = ISHELL_SetTimer(GETAPPBASIC()->pAeeApplet->m_pIShell, nMs, UTL_CB_Timer, this);
	if (SUCCESS == rtn)
	{
		m_bTimerOn = TRUE;
	}
	return rtn;
}

int CBaseScreen::CancelTimer(void)
{
	if(m_bTimerOn)
	{
		m_bTimerOn = FALSE;
		return ISHELL_CancelTimer(GETAPPBASIC()->pAeeApplet->m_pIShell, UTL_CB_Timer, this);
	}
	return SUCCESS;
}

void CBaseScreen::OnTimer(void)
{
	m_bTimerOn = FALSE;
}	
void CBaseScreen::SetParrent(CBaseScreen* pParrent)
{
	m_parent = pParrent;
}

void CBaseScreen::CancelAllForDoEnter()
{
	CancelTimer();
}


