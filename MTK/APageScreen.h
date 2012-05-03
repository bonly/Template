
#ifndef _APAGE_SCREENEX_H_
#define _APAGE_SCREENEX_H_

#include "BaseScreen.h"
#include "SxhInput.h"



class CAPageScreen:public CBaseScreen
{ 
public:
	CAPageScreen();
	virtual ~CAPageScreen();
	
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
	
	
private:
};

#endif
