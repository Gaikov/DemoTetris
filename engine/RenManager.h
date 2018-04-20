// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file RenManager.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_RenManager_H_
#define	_RenManager_H_

#include "RenDevice.h"

struct nsFont;

class nsRenManager
{
public:
	enum { MAX_DEVICES = 8 };

	nsRenManager();
	~nsRenManager();

	bool		RegVars();
	bool		Init();
	void		Release();
	
	//bool		AddDevice( IRenDevice* dev );
	IRenDevice*	GetCurrDevice();
	IRenDevice*	GetDevice( int idx );
	int			GetDeviceCount() { return m_devCount; }

private:
	IRenDevice	*m_devList[MAX_DEVICES];
	int			m_devCount;
	int			m_currDevice;
};

extern nsRenManager	g_renMgr;
extern IRenDevice	*g_renDev;
extern nsFont		*g_sysFont;

#endif //_RenManager_H_
