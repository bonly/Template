#ifndef  _CBASE_SCREEN_H
#define  _CBASE_SCREEN_H

#include "AppGlobal.h"
#include "JDefine.h"

class AppGlobal;
class CBaseScreen
{
public:
	CBaseScreen(void);
	virtual ~CBaseScreen(void);

public:
	virtual int          OnCreate(void* pi); // ���ڱ�������ʱ���յ�����Ϣ, ȱʡ�����κδ���
	virtual int          OnDestroy(void); // ���ڱ�����ʱ�յ�������, ȱʡ�����κδ���
	
	virtual BOOL		 OnWndProc(void* pi, AEEEvent eCode , uint16 wParam , uint32 dwParam); // ��������Ϣ������
	
	virtual void         OnShow(BOOL bShow); // ������Ҫ��ʾ�������ص�ʱ���յ�����Ϣ
	virtual int			 OnPaint(void* pi); // ���ڻ��ƽӿ�
	virtual void		 OnTimer(void);

	virtual BOOL	     OnSuspend();
	virtual BOOL		 OnResume();
	
	virtual BOOL		 OnKeyPressed(int keyCode);
	virtual BOOL		 OnKeyReleased(int keyCode);
	
	virtual BOOL		 OnPointerPressed(int x, int y);
	virtual BOOL		 OnPointerDragged(int x, int y);
	virtual BOOL		 OnPointerReleased(int x, int y);	
	
	virtual void         CancelAllForDoEnter();

public:
	// ���ô��ڶ�ʱ��
	int					SetTimer(int nMs);
	int					CancelTimer(void);
	void				SetParrent(CBaseScreen* pParrent);
public:
	// ������ָ��
	CBaseScreen*		m_parent;
	BOOL				m_bTimerOn;
	BOOL				m_bVisible;
	BOOL				m_bNeedRedraw;
	AppGlobal*			m_pGlobal;
};

#endif