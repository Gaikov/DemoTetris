// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file UserInput.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_UserInput_H_
#define	_UserInput_H_

struct IUserInput
{
	virtual void OnKeyUp( int key ) = 0;
	virtual void OnKeyDown( int key, bool rept ) = 0;
	virtual void OnChar( char ch ) = 0;
	
	virtual void OnLButtonUp( float x, float y ) = 0;
	virtual void OnLButtonDown( float x, float y ) = 0;
	virtual void OnMouseMove( float x, float y ) = 0;
};

#endif //_UserInput_H_