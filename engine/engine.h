// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file engine.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_engine_H_
#define	_engine_H_

struct nsEngine
{
	static bool Init();
	static void Release();
	static void MainLoop();
};

#endif //_engine_H_