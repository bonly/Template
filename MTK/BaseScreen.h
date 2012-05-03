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
	virtual int          OnCreate(void* pi); // 窗口被创建的时候收到的消息, 缺省不作任何处理
	virtual int          OnDestroy(void); // 窗口被销毁时收到的命令, 缺省不作任何处理
	
	virtual BOOL		 OnWndProc(void* pi, AEEEvent eCode , uint16 wParam , uint32 dwParam); // 窗口主消息处理函数
	
	virtual void         OnShow(BOOL bShow); // 窗口需要显示或者隐藏的时候收到的消息
	virtual int			 OnPaint(void* pi); // 窗口绘制接口
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
	// 设置窗口定时器
	int					SetTimer(int nMs);
	int					CancelTimer(void);
	void				SetParrent(CBaseScreen* pParrent);
public:
	// 父窗口指针
	CBaseScreen*		m_parent;
	BOOL				m_bTimerOn;
	BOOL				m_bVisible;
	BOOL				m_bNeedRedraw;
	AppGlobal*			m_pGlobal;
};

#endif