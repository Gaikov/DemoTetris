// Copyright (c) 2003-2008, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file FigureView.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_FigureView_H_
#define	_FigureView_H_

struct figure_t;

class nsFigureView
{
public:
	nsFigureView();

	void			SetFigure( const figure_t *f );
	void			SetRotation( int r );	//0..3
	int				GetWidth() const;
	int				GetHeight() const;
	char			GetCell( int x, int y ) const;

private:
	const figure_t	*m_figure;
	int				m_rotation;
};

#endif //FigureView_H_