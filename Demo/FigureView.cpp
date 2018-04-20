// Copyright (c) 2003-2008, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file FigureView.cpp
// author Roman Gaikov 
//--------------------------------------------------------------------------------------------------
#include "FigureView.h"
#include "common.h"
#include "FieldView.h"
#include "nsLib/Utils.h"

//---------------------------------------------------------
// nsFigureView::nsFigureView: 
//---------------------------------------------------------
nsFigureView::nsFigureView() :
	m_figure( 0 )
{

}

//---------------------------------------------------------
// nsFigureView::SetFigure: 
//---------------------------------------------------------
void nsFigureView::SetFigure( const figure_t *f )
{
	m_figure = f;
}

//---------------------------------------------------------
// nsFigureView::SetRotation: 
//---------------------------------------------------------
void nsFigureView::SetRotation( int r )
{
	m_rotation = abs( r ) % 4;
}

//---------------------------------------------------------
// nsFigureView::GetWidth: 
//---------------------------------------------------------
int	nsFigureView::GetWidth() const
{
	if ( !m_figure ) return 0;

	if ( m_rotation & 1 )
		return m_figure->rows.size();

	return m_figure->rows[0].size();
}

//---------------------------------------------------------
// nsFigureView::GetHeight: 
//---------------------------------------------------------
int	nsFigureView::GetHeight() const
{
	if ( !m_figure ) return 0;

	if ( m_rotation & 1 )
		return m_figure->rows[0].size();

	return m_figure->rows.size();
}

//---------------------------------------------------------
// nsFigureView::GetCell: 
//---------------------------------------------------------
char nsFigureView::GetCell( int x, int y ) const
{
	if ( !m_figure ) return 0;
	if ( x < 0 || x >= GetWidth() ) return 0;
	if ( y < 0 || y >= GetHeight() ) return 0;

	switch ( m_rotation )
	{
	case 0:
		break;
	case 1:
		x = GetWidth() - 1 - x;
		SwapType( x, y );
		break;
	case 2:
		y = GetHeight() - 1 - y;
		x = GetWidth() - 1 - x;
		break;
	case 3:
		y = GetHeight() - 1 - y;
		SwapType( x, y );
		break;
	}

	return m_figure->rows[y][x];
}
