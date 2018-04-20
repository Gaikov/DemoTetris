// Copyright (c) 2003-2008, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file GameField.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_GameField_H_
#define	_GameField_H_

#include "common.h"
#include "FigureView.h"

#define FIELD_WIDTH			20
#define FIELD_HEIGHT		30

class nsGameField
{
public:
	struct cell_t
	{
		char	ch;
		nsColor	color;
	};

	struct field_t
	{
		cell_t	cell[FIELD_HEIGHT][FIELD_WIDTH];
	};

public:
	static bool			Init();
	static void			Release();

	const field_t&		GetFieldArray() { return m_field; }
	const nsFigureView&	GetCurrFigure() { return m_figView; }
	void				GetFigurePos( int pos[2] );
	const nsColor&		GetFigureColor() { return m_figColor; }

	void				Loop();

private:
	field_t				m_field;
	nsFigureView		m_figView;
	const figure_t		*m_figCurr;
	int					m_figPosX, m_figPosY;
	int					m_figRot;
	nsColor				m_figColor;

	float				m_stepTime;
	float				m_strafeTime;

	bool				m_up;
	bool				m_down;
	bool				m_right;
	bool				m_left;

private:
	nsGameField();
	~nsGameField();

	void				FigureStrafe();
	void				FigureStep();
	void				FigureAppear();
	void				FigurePlace();
	bool				CheckCollision();

	bool				RowCheck( int y );
	void				RowCopy( int srcY, int destY );
	void				RowClear( int y );

	void				FieldClear();

};

extern nsGameField *g_gameField;

#endif //GameField_H_