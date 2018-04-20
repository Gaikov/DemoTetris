// Copyright (c) 2003-2008, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file GameField.cpp
// author Roman Gaikov 
//--------------------------------------------------------------------------------------------------
#include "GameField.h"
#include "FigureBase.h"

nsGameField *g_gameField = 0;

nsVar		*g_fig_time = 0;
nsVar		*g_fig_strafe = 0;
nsVar		*g_left = 0;
nsVar		*g_right = 0;
nsVar		*g_up = 0;
nsVar		*g_down = 0;

//---------------------------------------------------------
// nsGameField::nsGameField: 
//---------------------------------------------------------
nsGameField::nsGameField() :
	m_figCurr( 0 ),
	m_stepTime( 0 ),
	m_strafeTime( 0 )
{
	m_up = m_down = m_right = m_left = false;

	FieldClear();

	g_fig_time = g_cfg->RegVar( "g_fig_time", "1", GVF_SAVABLE );
	g_fig_strafe = g_cfg->RegVar( "g_fig_strafe", "0.1", GVF_SAVABLE );

	g_left = g_cfg->RegVar( "g_left", "0", GVF_INTERNAL );
	g_right = g_cfg->RegVar( "g_right", "0", GVF_INTERNAL );
	g_up = g_cfg->RegVar( "g_up", "0", GVF_INTERNAL );
	g_down = g_cfg->RegVar( "g_down", "0", GVF_INTERNAL );

	FigureAppear();
}

//---------------------------------------------------------
// nsGameField::~nsGameField: 
//---------------------------------------------------------
nsGameField::~nsGameField()
{

}

//---------------------------------------------------------
// nsGameField::Init: 
//---------------------------------------------------------
bool nsGameField::Init()
{
	if ( !g_gameField )
	{
		g_gameField = new nsGameField;
		return true;
	}

	return true;
}

//---------------------------------------------------------
// nsGameField::Release: 
//---------------------------------------------------------
void nsGameField::Release()
{
	if ( g_gameField )
	{
		delete g_gameField;
		g_gameField = 0;
	}
}

//---------------------------------------------------------
// nsGameField::GetFigurePos: 
//---------------------------------------------------------
void nsGameField::GetFigurePos( int pos[2] )
{
	pos[0] = m_figPosX;
	pos[1] = m_figPosY;
}

//---------------------------------------------------------
// nsGameField::Loop: 
//---------------------------------------------------------
void nsGameField::Loop()
{
	if ( g_up->Value() ) m_up = true;
	if ( g_right->Value() ) m_right = true;
	if ( g_left->Value() ) m_left = true;

	if ( g_down->Value() )
	{
		
		m_down = true;
	}

	m_strafeTime -= g_frameTime;
	if ( m_strafeTime <= 0 )
	{
		m_strafeTime += g_fig_strafe->Value();
		FigureStrafe();
	}

	m_stepTime -= g_frameTime;
	if ( m_stepTime <= 0 )
	{
		m_stepTime += g_fig_time->Value();
		FigureStep();
	}
}

//---------------------------------------------------------
// nsGameField::FigureStrafe: 
//---------------------------------------------------------
void nsGameField::FigureStrafe()
{
	if ( m_left )
	{
		m_figPosX --;
		if ( CheckCollision() )
			m_figPosX ++;
		else if ( m_figPosX < 0 )
			m_figPosX = 0;
		m_left = false;
	}
	else if ( m_right )
	{
		m_figPosX ++;
		if ( CheckCollision() )
			m_figPosX --;
		else if ( m_figPosX + m_figView.GetWidth() > FIELD_WIDTH )
			m_figPosX = FIELD_WIDTH - m_figView.GetWidth();

		m_right = false;
	}

	if ( m_up )
	{
		int	oldRot = m_figRot;
		m_figRot = (m_figRot + 1) % 4;
		m_figView.SetRotation( m_figRot );
		m_up = false;

		int	oldX = m_figPosX;
		if ( m_figPosX + m_figView.GetWidth() > FIELD_WIDTH )
			m_figPosX = FIELD_WIDTH - m_figView.GetWidth();

		if ( CheckCollision() )
		{
			m_figRot = oldRot;
			m_figView.SetRotation( m_figRot );
			m_figPosX = oldX;
		}
	}
}

//---------------------------------------------------------
// nsGameField::FigureStep: 
//---------------------------------------------------------
void nsGameField::FigureStep()
{
	m_figPosY ++;
	if ( m_figPosY + m_figView.GetHeight() > FIELD_HEIGHT ||
		CheckCollision() )
	{
		m_figPosY --;
		FigurePlace();
		FigureAppear();
	}
}

//---------------------------------------------------------
// nsGameField::AppearFigure: 
//---------------------------------------------------------
void nsGameField::FigureAppear()
{
	m_figPosY = 0;
	m_figCurr = g_figBase->GetFigure( rand() % g_figBase->GetFigureCount() );
	m_figView.SetFigure( m_figCurr );
	m_figView.SetRotation( 0 );
	m_figColor.Rand();
	m_figRot = 0;

	m_figPosX = int( FIELD_WIDTH / 2.0f - m_figView.GetWidth() / 2.0f );

	if ( CheckCollision() )	FieldClear();
}

//---------------------------------------------------------
// nsGameField::FigurePlace: 
//---------------------------------------------------------
void nsGameField::FigurePlace()
{
	for ( int y = 0; y < m_figView.GetHeight(); ++y )
		for ( int x = 0; x < m_figView.GetWidth(); ++x )
		{
			if ( m_figView.GetCell( x, y ) == 'X' )
			{
				cell_t	&cell = m_field.cell[y + m_figPosY][x + m_figPosX];
				cell.ch = 'X';
				cell.color = m_figColor;
			}
		}

	for ( y = 0; y < FIELD_HEIGHT; ++y )
	{
		if ( RowCheck( y ) )
		{
			for ( int i = y; i > 0; --i )
				RowCopy( i - 1, i );
			RowClear( 0 );
		}
	}
}

//---------------------------------------------------------
// nsGameField::CheckCollision: 
//---------------------------------------------------------
bool nsGameField::CheckCollision()
{
	for ( int y = 0; y < m_figView.GetHeight(); ++y )
		for ( int x = 0; x < m_figView.GetWidth(); ++x )
		{
			cell_t	&cell = m_field.cell[y + m_figPosY][x + m_figPosX];
			if ( cell.ch == 'X' && m_figView.GetCell( x, y ) == 'X' )
				return true;
		}

	return false;
}

//---------------------------------------------------------
// nsGameField::RowCheck: 
//---------------------------------------------------------
bool nsGameField::RowCheck( int y )
{
	for ( int x = 0; x < FIELD_WIDTH; ++x )
		if ( m_field.cell[y][x].ch != 'X' ) return false;

	return true;
}

//---------------------------------------------------------
// nsGameField::RowCopy: 
//---------------------------------------------------------
void nsGameField::RowCopy( int srcY, int destY )
{
	memcpy( m_field.cell[destY], m_field.cell[srcY], sizeof(cell_t) * FIELD_WIDTH );
}

//---------------------------------------------------------
// nsGameField::RowClear: 
//---------------------------------------------------------
void nsGameField::RowClear( int y )
{
	for ( int x = 0; x < FIELD_WIDTH; ++x )
		m_field.cell[y][x].ch = ' ';
}

//---------------------------------------------------------
// nsGameField::FieldClear: 
//---------------------------------------------------------
void nsGameField::FieldClear()
{
	for ( int y = 0; y < FIELD_HEIGHT; ++y )
		RowClear( y );
}