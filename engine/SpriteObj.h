// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file SpriteObj.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_SpriteObj_H_
#define	_SpriteObj_H_

#include "nsLib/color.h"
#include "Core/Name.h"
#include "Core/Parser.h"
#include "RenDevice.h"
#include "RenAux.h"

//---------------------------------------------------------
// spriteProps_t: 
//---------------------------------------------------------
struct spriteProps_t
{
	nsVec2			pos;
	nsVec2			scale;
	float			angle;
	nsColor			color;
};

class nsSpriteObj;

//---------------------------------------------------------
// nsSpriteState: 
//---------------------------------------------------------
class nsSpriteState
{
public:
	enum interpMethod_t
	{
		INTERP_LINEAR = 0,
		INTERP_COSINE
	};

	struct runState_t
	{
		nsName			spriteID;
		nsName			stateID;

		//заполняются в списке (nsSpriteList)
		nsSpriteObj		*sprite;
		nsSpriteState	*state;
	};

public:
	bool			m_usePos;

	spriteProps_t	m_props;
	
	nsName			m_id;
	bool			m_visible;
	interpMethod_t	m_method;
	nsName			m_next;
	float			m_speed;

	runState_t		*m_runStates;
	int				m_runStatesCount;

public:
	nsSpriteState();
	nsSpriteState( script_state_t *ss );
	void	Free();
};

//---------------------------------------------------------
// nsSpriteObj: 
//---------------------------------------------------------
class nsSpriteObj
{
friend class nsSpriteList;

public:
	virtual ~nsSpriteObj();

	static nsSpriteObj*	Load( script_state_t *ss );

	const nsVec2&		GetPos();
	nsVec2				CalcPos();	//относительно родителя
	void				SetPos( const nsVec2 &pos );

	void				Move();
	void				Draw();

	bool				StateChange( const nsName &name );

	void				DepthSet( int depth );
	void				DepthReset();
	int					DepthGet() { return m_depth; }

	void				SetData( void *data ) { m_data = data; }
	void*				GetData() { return m_data; }

private:
	nsName				m_id;
	nsName				m_parentID;
	nsSpriteObj			*m_parent;
	nsVec2				m_size;
	nsVec2				m_center;
	bool				m_visible;
	
	bool				m_texCoords;
	nsVec2				m_tex1, m_tex2;

	drawSprite_t		m_drawDesc;

	nsSpriteState		*m_states;
	int					m_stateCount;

	spriteProps_t		m_prevState;
	spriteProps_t		m_currState;
	nsSpriteState		*m_nextState;
	float				m_lerp;

	int					m_defDepth;	//глубина по умолчанию
	int					m_depth;	//для сортировки

	void				*m_data;	//пользовательские данные

private:
	nsSpriteObj();

	bool				StateChange( nsSpriteState *next );
	
	void				LerpProps( nsSpriteState *next, float t );
	bool				Parse( script_state_t *ss );
	nsSpriteState*		FindState( const nsName &name );
};

#endif //_SpriteObj_H_