// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file SpriteList.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_SpriteList_H_
#define	_SpriteList_H_

#include "Core/Parser.h"
#include "Core/Name.h"
#include "Core/SmartPtr.h"

class nsSpriteObj;

class nsSpriteList
{
public:
	typedef nsSmartPtr<nsSpriteList>	sp_t;

public:
	virtual ~nsSpriteList();

	static nsSpriteList*	Load( script_state_t *ss );
	static nsSpriteList*	Load( const char *fileName );
	nsSpriteObj*			FindSprite( const nsName &name );

	int						GetCount();
	nsSpriteObj*			GetSprite( int idx );
	
	void					MoveAll();
	void					DrawAll();
	
private:
	struct sortEntry_t
	{
		nsSpriteObj	*s;
	};

private:
	nsSpriteObj				**m_list;
	int						m_count;

	sortEntry_t				*m_sortList;

private:
	nsSpriteList();
	bool					Parse( script_state_t *ss );
	void					FillRunStates( nsSpriteObj *sprite );

	static int				CmpDepth( const void *elem1, const void *elem2 );
};

#endif //_SpriteList_H_