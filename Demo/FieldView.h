// Copyright (c) 2003-2008, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file FieldView.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_FieldView_H_
#define	_FieldView_H_

#include "common.h"
#include "FigureBase.h"

class nsFigureView;

//---------------------------------------------------------
// nsFieldView: 
//---------------------------------------------------------
class nsFieldView
{
public:
	static bool Init();
	static void Release();

	void		Draw();

private:
	nsVec2			m_startPos;
	float			m_width;
	float			m_height;

	IVertexBuffer	*m_gridVerts;

private:
	nsFieldView();
	~nsFieldView();

	void		DrawFigure( int x, int y, const nsFigureView *fv, const nsColor &c );

	void		DrawCell( int x, int y, const nsColor &c = nsColor() );

	void		DrawGrid();
};

extern nsFieldView *g_fieldView;

#endif //FieldView_H_