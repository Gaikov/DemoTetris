// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file RenAux.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_RenAux_H_
#define	_RenAux_H_

#include "nsLib/comm_types.h"
#include "nsLib/Vec2.h"
#include "nsLib/color.h"
#include "nsLib/BBox2.h"
#include "RenDevice.h"

bool RX_Init();
void RX_Release();

void RX_DrawFPS( float x, float y, uint frameTime );
void RX_BuildSpriteVerts( nsVec2 v[4], const nsVec2 &pos, const nsVec2 &size, const nsVec2 &center = nsVec2( 0, 0 ), float angle = 0 );

struct drawSprite_t
{
	inline drawSprite_t() :
		tex( 0 ),
		angle( 0 ),
		useTex( false ),
		tex2( 1, 1 )
	{}

	ITexture	*tex;
	nsVec2		pos;
	nsVec2		center;
	nsVec2		size;
	nsColor		color;
	float		angle;

	bool		useTex;
	nsVec2		tex1, tex2;	//������� �����, ������ ������ (���������� ����������)
};

void RX_DrawSprite( drawSprite_t &desc );

void RX_DrawStrip( ITexture *tex, const nsVec2 &pos1, const nsVec2 &pos2, float width, const nsColor &color = nsColor::white );

//������� ������ ������� �������
void RX_DrawQuad( ITexture *tex, vbVertex_t quad[4] );

void RX_DrawBBox( const nsVec2 &pos, const nsBBox2 &box, const nsColor &color = nsColor::white );
void RX_DrawLine( const nsVec2 &v1, const nsVec2 &v2, const nsColor &color = nsColor::white );
void RX_DrawLine( const nsVec3 &v1, const nsVec3 &v2, const nsColor &color = nsColor::white );

void RX_IndicesStrip( IVertexBuffer *vb, int vertCount );

//void RX_DrawSprite( ITexture *tex, const nsVec2 &pos, const nsVec2 &size, const nsColor &color = nsColor::white, nsVec2 &warping =  );

#endif //_RenAux_H_