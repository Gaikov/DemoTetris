// Copyright (c) 2003-2008, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file FigureBase.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_FigureBase_H_
#define	_FigureBase_H_

#include "common.h"

//---------------------------------------------------------
// figure_t: 
//---------------------------------------------------------
struct figure_t
{
	typedef std::vector<char>	row_t;
	typedef std::vector<row_t>	rows_t;

	rows_t	rows;
	int		rowCount;
	int		colCount;
};

//---------------------------------------------------------
// nsFigureBase: 
//---------------------------------------------------------
class nsFigureBase
{
public:
	static bool			Init();
	static void			Release();

	const figure_t* GetFigure( int idx );
	int					GetFigureCount();

private:
	typedef std::vector<figure_t>	figureList_t;
	
	figureList_t						m_list;

private:
	nsFigureBase();
	~nsFigureBase();

	bool				ParseFigure( script_state_t *ss, figure_t &fv );
};

extern nsFigureBase	*g_figBase;

#endif //FigureBase_H_