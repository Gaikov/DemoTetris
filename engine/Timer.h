#ifndef _TIMER_H_
#define _TIMER_H_

extern	float	global_time;

class CTimer  
{
public:
	void Update();
	void Activate( bool active );
	CTimer();
	virtual ~CTimer();

	

protected:
	bool	m_bActive;
	DWORD	m_dwPrevTime;
};

#endif
