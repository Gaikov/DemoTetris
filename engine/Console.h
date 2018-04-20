// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Console.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_Console_H_
#define	_Console_H_

#include "nsLib/StrTools.h"
#include "nsLib/CycleList.h"
#include "nsLib/color.h"
#include "nsLib/EditString.h"
#include "Core/log.h"
#include "UserInput.h"

class nsConsole : public IUserInput, public ILogListener
{
public:
	nsConsole();
	~nsConsole();

	void			Activate( bool active );
	void			Toggle();
	bool			IsActive();
	bool			IsEnabled();
	void			Clear();
	void			Print( const char *str );
	void			FreeRes();
	bool			LoadRes();
	void			Draw();

protected:
	enum { CON_TEXT_SIZE = 32768 };

protected:
	char			m_text[CON_TEXT_SIZE];
	nsEditString	m_line;
	int				m_nLineUp;
	char			*m_pPrint;

	void			*m_tex;
	float			tex_offs[2];

	bool						m_bActive;

	nsCycleList<nsString, 10>	m_hyst;

protected:
	void			DrawCursor( float y );
	
	char*			SkipLines( char *from, int count );
	void			ClearLine();

	char*			LineFromEnd( char *end );
	void			DrawLine( const char *line, float y, int len, const nsColor &c );

	virtual void	OnKeyUp( int key ) {}
	virtual void	OnKeyDown( int key, bool rept );
	virtual void	OnChar( char ch );
	
	virtual void	OnLButtonUp( float x, float y ) {}
	virtual void	OnLButtonDown( float x, float y ) {}
	virtual void	OnMouseMove( float x, float y ) {}
};

extern	nsConsole	g_con;

#endif //_Console_H_
