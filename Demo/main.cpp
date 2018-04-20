#include "common.h"
#include "FigureBase.h"
#include "FieldView.h"
#include "GameField.h"

//---------------------------------------------------------
// nsDemoInfo: 
//---------------------------------------------------------
class nsDemoInfo : public IAppInfo
{
	virtual const char*		GetAppName() { return "Demo"; }
	virtual const char*		GetDefCfgPath() { return 0; }
	virtual IDataReader*	GetCfgReader() { return 0; }
	virtual IDataWriter*	GetCfgWriter() { return 0; }
};

nsDemoInfo	g_appInfo;

//---------------------------------------------------------
// App_GetInfo: 
//---------------------------------------------------------
IAppInfo* App_GetInfo()
{
	return &g_appInfo;	
}

//---------------------------------------------------------
// nsDemoApp: 
//---------------------------------------------------------
class nsDemoApp : public IGameApp
{
private:
	virtual bool		InitDialog() { return true; }
	virtual bool		Init();
	virtual void		Release();

	virtual void		DrawWorld();
	virtual void		Loop( float frameTime );

	virtual void		OnActivate( bool active ) {}
	virtual void		OnPause( bool paused ) {}
	
	virtual int			GetWindowIcon() { return 0; }
	virtual IUserInput*	GetUserInput() { return 0; }
	
	virtual void		GetGUIDimension( int &width, int &height )
	{
		width = DIM_WIDTH;
		height = DIM_HEIGHT;
	}

private:
	ITrack		*m_track;
};

nsDemoApp	g_app;

//---------------------------------------------------------
// App_GetGame: 
//---------------------------------------------------------
IGameApp* App_GetGame()
{
	return &g_app;
}

//---------------------------------------------------------
//  nsDemoApp::Init: 
//---------------------------------------------------------
bool nsDemoApp::Init()
{
	LogPrintf( PRN_ALL, 
		"*****************************************\n" \
		" INIT DEMO: start \n" \
		"*****************************************\n" );

	if ( !nsFigureBase::Init() ) return false;
	if ( !nsGameField::Init() ) return false;
	if ( !nsFieldView::Init() ) return false;

	m_track = g_sndDev->TrackLoad( "sound/track.ogg" );
	g_sndDev->TrackPlay( m_track );

	LogPrintf( PRN_ALL, 
		"*****************************************\n" \
		" INIT DEMO: done! \n" \
		"*****************************************\n" );
	return true;
}

//---------------------------------------------------------
// nsDemoApp::Release: 
//---------------------------------------------------------
void nsDemoApp::Release()
{
	nsFieldView::Release();
	nsGameField::Release();
	nsFigureBase::Release();
}

//---------------------------------------------------------
// nsDemoApp::Loop: 
//---------------------------------------------------------
void nsDemoApp::Loop( float frameTime )
{
	g_gameField->Loop();
}

//---------------------------------------------------------
// nsDemoApp::DrawWorld: 
//---------------------------------------------------------
void nsDemoApp::DrawWorld()
{
	g_renDev->ClearScene( CLR_CBUFF );
	g_fieldView->Draw();
}