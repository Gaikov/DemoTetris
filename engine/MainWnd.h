#ifndef _WND_H_
#define _WND_H_

#include "Core/headers.h"

class nsMainWnd
{
public:
	bool			m_processMsg;

public:
	nsMainWnd();
	~nsMainWnd();
	
	bool			create( const char *title, const char *classname );
	bool			destroy();

	void			ClientToRender( int x, int y, float &rx, float &ry );
	void			MinimizeWindow();

	HWND			GetHWnd() { return m_hWnd; }

	bool			IsActive();
	
	void			SetCaption( const char *text );

protected:
	bool			m_bActive;
	bool			m_bUpdateView;

	HWND			m_hWnd;

protected:
	static LRESULT CALLBACK	StatinsMainWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	
	virtual LRESULT	WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	void			OnActivateApp( bool active );
};

extern nsMainWnd	g_mainWnd;

#endif 
