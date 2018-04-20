// Copyright (c) 2003-2008, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file FieldView.cpp
// author Roman Gaikov 
//--------------------------------------------------------------------------------------------------
#include "FieldView.h"
#include "FigureView.h"
#include "GameField.h"

nsFieldView *g_fieldView = 0;

#define CELL_SIZE			16.0f
#define FIELD_LINE_COUNT	(FIELD_WIDTH * FIELD_HEIGHT + 2)

//---------------------------------------------------------
// nsFieldView::nsFieldView: 
//---------------------------------------------------------
nsFieldView::nsFieldView()
{
	m_width = CELL_SIZE * FIELD_WIDTH;
	m_height = CELL_SIZE * FIELD_HEIGHT;

	m_startPos.x = DIM_WIDTH / 2.0f - m_width / 2.0f;
	m_startPos.y = DIM_HEIGHT / 2.0f - m_height / 2.0f;

	m_gridVerts = g_renDev->VerticesCreate( FIELD_LINE_COUNT * 2, FIELD_LINE_COUNT * 2 );
	m_gridVerts->SetPrimitiveMode( PM_LINES );

	vbVertex_t	*v = m_gridVerts->GetWriteVertices();
	word		*idx = m_gridVerts->GetWriteIndices();

	for ( int i = 0; i < FIELD_LINE_COUNT << 1; ++i )
		idx[i] = (word)i;

	dword c = nsColor::ToARGB( nsColor( 0.2f, 0.2f, 0.2f, 1 ) );

	for ( i = 0; i < FIELD_WIDTH + 1; ++i )
	{
		int	line = i * 2;
		v[line].v = nsVec3( m_startPos.x + i * CELL_SIZE, m_startPos.y, 0 );
		v[line + 1].v = nsVec3( m_startPos.x + i * CELL_SIZE, m_startPos.y + m_height, 0 );
		v[line].c = v[line + 1].c = c;
	}

	for ( i = 0; i < FIELD_HEIGHT + 1; ++i )
	{
		int line = i * 2 +(FIELD_WIDTH + 1) * 2;
		v[line].v = nsVec3( m_startPos.x, m_startPos.y + i * CELL_SIZE, 0 );
		v[line + 1].v = nsVec3( m_startPos.x + m_width, m_startPos.y + i * CELL_SIZE, 0 );
		v[line].c = v[line + 1].c = c;
	}
}

//---------------------------------------------------------
// nsFieldView::~nsFieldView: 
//---------------------------------------------------------
nsFieldView::~nsFieldView()
{
	g_renDev->VerticesRelease( m_gridVerts );
}

//---------------------------------------------------------
// nsFieldView::Init: 
//---------------------------------------------------------
bool nsFieldView::Init()
{
	if ( !g_fieldView )
	{
		g_fieldView = new nsFieldView;
		return true;
	}

	return true;
}

//---------------------------------------------------------
// nsFieldView::Release: 
//---------------------------------------------------------
void nsFieldView::Release()
{
	if ( g_fieldView )
	{
		delete g_fieldView;
		g_fieldView = 0;
	}
}

//---------------------------------------------------------
// nsFieldView::Draw: 
//---------------------------------------------------------
void nsFieldView::Draw()
{
	/*DrawCell( 1, 1, nsColor::red );
	DrawCell( 18, 28, nsColor::red );

	nsFigureView	fv;
	fv.SetFigure( g_figBase->GetFigure( 0 ) );
	fv.SetRotation( 3 );

	DrawFigure( 10, 10, &fv );//*/
	int	pos[2];
	g_gameField->GetFigurePos( pos );
	DrawFigure( pos[0], pos[1], &g_gameField->GetCurrFigure(), g_gameField->GetFigureColor() );

	DrawGrid();
}

//---------------------------------------------------------
// nsFieldView::DrawFigure: 
//---------------------------------------------------------
void nsFieldView::DrawFigure( int posX, int posY, const nsFigureView *fv, const nsColor &c )
{
	if ( !fv ) return;

	for ( int y = 0; y < fv->GetHeight(); ++y )
	{
		for ( int x = 0; x < fv->GetWidth(); ++x )
		{
			if ( fv->GetCell( x, y ) == 'X' )
				DrawCell( posX + x, posY + y, c );
		}
	}

	const nsGameField::field_t	&field = g_gameField->GetFieldArray();

	for ( y = 0; y < FIELD_HEIGHT; ++y )
		for ( int x = 0; x < FIELD_WIDTH; ++x )
		{
			if ( field.cell[y][x].ch == 'X' )
				DrawCell( x, y, field.cell[y][x].color );
		}
}

//---------------------------------------------------------
// nsFieldView::DrawCell: 
//---------------------------------------------------------
void nsFieldView::DrawCell( int x, int y, const nsColor &c )
{
	if ( x < 0 || x >= FIELD_WIDTH ) return;
	if ( y < 0 || y >= FIELD_HEIGHT ) return;

	y = FIELD_HEIGHT - y - 1;

	drawSprite_t	spr;
	spr.size = nsVec2( CELL_SIZE - 1, CELL_SIZE - 1 );
	spr.color = c;
	spr.pos = nsVec2( m_startPos.x + x * CELL_SIZE + 1, m_startPos.y + y * CELL_SIZE );

	RX_DrawSprite( spr );
}

//---------------------------------------------------------
// nsFieldView::DrawGrid: 
//---------------------------------------------------------
void nsFieldView::DrawGrid()
{
	g_renDev->TextureBind( 0 );
	g_renDev->VerticesDraw( m_gridVerts );
}
