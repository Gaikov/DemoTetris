#ifndef _EDIT_
#define _EDIT_

#include "local.h"
#include "Room.h"

class CEditGame
{
protected:
	//testing room
	bool	m_test_room;
	CRoom	*m_pRoomPrev;
	CRoom	m_testRoom;

	bool	m_test_level;

public:
	CEditGame()
	{
		//testing room
		m_pRoomPrev = 0;
		memset( &m_testRoom, 0, sizeof(m_testRoom) );
		m_test_room = false;
	}

	void release();
	void init();
	
	void TestRoomCancel();
	bool TestRoom( char *filename );

	bool IsEdit();
};

extern	CEditGame	edit;

#endif