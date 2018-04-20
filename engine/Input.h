#ifndef _INPUT_H_
#define _INPUT_H_

#include "nsLib/StrTools.h"
#include "Core/Config.h"

typedef enum
{
	IC_NONE = 0,
	IC_VAR,
	IC_CMD
}
ic_type_t;

#define MAX_KEY_NAME	32

typedef struct
{
	char		*keyname;
	char		gameKeyName[MAX_KEY_NAME];
	ic_type_t	type;

	union
	{
		//cmd
		struct
		{
			const cmdDesc_t	*cmd;
			int				argc;
			char			**argv;
			bool			play;		//call command continuous
		};
	
		//var
		struct
		{
			nsVar	*var;
			bool	inc;		//true - increment var by 1 on key down, decrement by 1 on key up... false - otherwise
		};
	};
}
key_t;

//---------------------------------------------------------
// nsInput: 
//---------------------------------------------------------
class nsInput : public ICfgWriter
{
public:
	nsInput();
	void			Init();
	void			Release();
	void			Process();
	
	void			ReleaseAllKeys();
	
	void			Unbind( const char *var_cmd );
	int				GetBind( const char *var_cmd, nsString **keys );

	void			ShowCursor( bool show );
	void			SetCursorPos( float x, float y );
	void			GetCursorPos( float &x, float &y );
	bool			CanDrawCursor();

	//возвращает имя клавиши (идетнификатор, прописаны в коде)
	const char*		GetKeyDesc( int code );
	
	//возвращает имя клавиши из файла scripts/key_names.txt, 0 если там нет описания
	const char*		GetKeyNameByDesc( const char *desc );

	bool			WaitAnyKey();
	bool			IsAnyKeyPressed();

private:
	key_t			m_inKeys[256];
	bool			m_kbPrev[256];

	bool			m_bCurState;	//cursor state (hidden/visible)
	bool			m_bDrawCursor;

	key_t			m_joyKeys[8];
	bool			m_joyPrev[8];
	bool			m_joyUse;

	bool			m_uiActive;
	bool			m_bAnyKey;

private:
	static void		keycmd_f( int argc, const char *argv[] );
	static void		in_showkeys_f( int argc, const char *argv[] );
	static void		keydesc_f( int argc, const char *argv[] );

	virtual void	OnSaveConfig( IDataWriter *out );
	void			LoadBindings();
	void			LoadKeys( char *str );
	void			InitKeyNames();

	void			BindKeyCmd( key_t *key, const cmdDesc_t *cmd, int argc, const char *argv[], bool play );
	void			BindKeyVar( key_t *key, nsVar *var, bool inc );
	void			UnbindKey( key_t *key );

	void			ShowKeys();

	key_t*			GetKey( const char *name );
	void			KeyPressed( key_t *key );
	void			KeyUp( key_t *key );
	void			KeyDown( key_t *key );

	void			GetJoyState( bool keys[8] );

	bool			IsSystemKeyPressed();
	bool			IsPauseKey( key_t *key );
};

extern	nsInput		g_inp;

#endif
