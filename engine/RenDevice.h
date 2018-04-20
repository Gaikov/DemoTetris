// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file RenDevice.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_RenDevice_H_
#define	_RenDevice_H_

#include "nsLib/matrix4.h"
#include "nsLib/comm_types.h"

class	nsVar;

/*=========================================
raster configuration desc
=========================================*/
struct rasterConfig_t
{
	uint	defPixelBits;						//default screen pixel depth
	uint	defScreenWidth, defScreenHeight;	//default screen dimention
	uint	currWidth, currHeight;
};

/*-------------------------------------------------------------------------------------
render config waribales
-------------------------------------------------------------------------------------*/
extern	nsVar	*r_fullscreen;
extern	nsVar	*r_pixel_bits;
extern	nsVar	*r_tex_bits;
extern	nsVar	*r_vsync;
extern	nsVar	*r_tex_filter;
extern	nsVar	*r_brightness;
extern	nsVar	*r_width;
extern	nsVar	*r_height;
extern	nsVar	*r_refresh;
extern	nsVar	*r_fov;//*/

//texture format GetTexture
typedef enum
{
	TF_RGB,
	TF_RGBA
}
texfmt_t;

#define	CLR_ZBUFF	1
#define CLR_CBUFF	2

//DrawChar
typedef struct
{
	float	coord[2];	//in textures
	float	tex_size[2];	//size on texture
	
	float	size[2];	//real size
	float	offs[2];	//offset in screen
}
rchar_t;

//---------------------------------------------------------
// IRenState: 
//---------------------------------------------------------
struct IRenState
{
	virtual bool IsAlphaTest() = 0;
	virtual bool IsAlphaBlend() = 0;
};

//веришна буфера вершин
typedef struct
{
	nsVec3	v;			//вершина
	nsVec3	n;			//нормаль
	dword	c;			//цвет вершины
	float	tu, tv;		//текстурные координаты
}
vbVertex_t;

//режим примитивов буфера вершин
typedef enum  
{
	PM_TRIANGLES,
	PM_TRISTRIPS,
	PM_LINES
}
primitiveMode_t;

//---------------------------------------------------------
// IVertexBuffer: буфер вершин
//---------------------------------------------------------
struct IVertexBuffer
{
	virtual void		SetValidVertices( uint count ) = 0;
	virtual uint		GetValidVertices() = 0;
	
	virtual void		SetValidIndices( uint count ) = 0;
	virtual uint		GetValidIndices() = 0;
	
	virtual void		SetPrimitiveMode( primitiveMode_t mode ) = 0;	//default PM_TRIANGLES
	
	virtual uint		GetVerticesCount() = 0;
	virtual uint		GetIndicesCount() = 0;
	
	//работа с вершинами
	virtual vbVertex_t*	GetReadVertices() = 0;	//для чтения
	virtual vbVertex_t*	GetWriteVertices() = 0;	//! только для записи
	
	//работа с индексами
	virtual word*		GetReadIndices() = 0;	//для чтения
	virtual word*		GetWriteIndices() = 0;	//! только для записи
};

//---------------------------------------------------------
// ITexture: 
//---------------------------------------------------------
struct ITexture
{
	virtual void GetSize( int &width, int &height ) = 0;
};

//---------------------------------------------------------
// IRenDevice: 
//---------------------------------------------------------
struct IRenDevice
{
	virtual const char*		GetName() = 0;

	//init render
	virtual bool					ConfigDlg( uint hWnd, const char *localPath, const char *locaPostfix ) = 0; //диалог конфигурации, вызывается приложением только перед началом использования
	virtual bool					Init( uint hWnd ) = 0;	//инициализация, вызывается приложением перед началом использования
	virtual	void					Release() = 0; //освобождение, вызывается приложением после использования 
	virtual int						GetModeList( int **modes ) = 0;
	virtual const rasterConfig_t*	GetCurrentConfig() = 0;

	//текущий цвет отображения примитивов
	virtual void			SetColor( const float c[4] ) = 0; 

	//textures
	virtual ITexture*		TextureLoad( const char *filename, bool mipmap = true, texfmt_t fmt = TF_RGBA ) = 0;
	virtual ITexture*		TextureGenerate( int width, int height, const void *data, texfmt_t fmt, bool mipmap ) = 0;
	virtual void			TextureRelease( ITexture *texture ) = 0;
	virtual void			TextureBind( ITexture *texture ) = 0;
	virtual void			TextureTranform( const float *offs2, const float *scale2 ) = 0; //in 

	//render state
	virtual IRenState*		StateLoad( const char *fileName ) = 0;
	virtual void			StateRelease( IRenState *state ) = 0;
	virtual void			StateApply( IRenState *state ) = 0;

	//scene functions
	virtual void			ClearScene( uint flags ) = 0;
	virtual bool			BeginScene() = 0;
	virtual	void			EndScene() = 0;

	virtual void			LoadProjMatrix( const float m[16] ) = 0;
	virtual void			LoadViewMartix( const float m[16] ) = 0;

	 //влияет на прорисовку объектов, умножается на WORLD_MATRIX (OBJECT_MATRIX)
	virtual void			LoadMatrix( const float m[16] ) = 0;
	virtual void			MultMatrix( const float m[16] ) = 0;
	virtual void			MultMatrixLocal( const float m[16] ) = 0;
	
	//========= 2d graphics ==========
	//pictures
	virtual void			DrawSprite( float x, float y, float width, float height, float tu1 = 0, float tv1 = 0, float tu2 = 1, float tv2 = 1 ) = 0;
	virtual void			DrawLinedSprite( float x1, float y1, float x2, float y2, float width, float height ) = 0;
	virtual void			DrawFadeScreen() = 0; //0 - no fade, 1 - full fade
	
	virtual void			DrawChar( float x, float y, rchar_t *ch ) = 0;
	virtual void			DrawCharScaled( float x, float y, rchar_t *ch, float sx, float sy ) = 0;

	//========= 3d graphics ==========
	virtual IVertexBuffer*	VerticesCreate( uint vertsCount, uint indexCount, bool dynamic = false ) = 0;
	virtual void			VerticesRelease( IVertexBuffer* vb ) = 0;
	virtual void			VerticesDraw( IVertexBuffer* vb ) = 0;

	virtual void			DrawLine( float, float, float, float, float, float ) = 0;
		
	//sprites
	virtual void			DrawSprite3D( const nsMatrix &view, const nsVec3 &pos, float width, float height, float angle, float w_scale = 1 ) = 0;
	virtual void			DrawChar3D( rchar_t *ch, nsVec3 &pos, float sx, float sy ) = 0;
	virtual void			DrawPlaneSprite( const nsMatrix &view, nsVec3& p1, nsVec3& p2, float width, uint wrap_count ) = 0;
	
	//задание 2-х источников света, работает только в 3D режиме
	virtual void			Lighting( bool enable ) = 0;
	virtual void			LightEnable( int source, const nsVec3 &dir, const float c[4] ) = 0;
	virtual void			LightDisable( int source ) = 0;
	virtual void			SetLightAmbient( const float c[4] ) = 0;
};

#endif //_RenDevice_H_