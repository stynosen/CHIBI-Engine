#pragma once
#include "MainData.h"

class TimerManager;

//!A base timer class
class Timer
{
public:
	//!Reset the timer to the starting time
	virtual void Reset(const bool start = false)=0;
	
	//!Get the current time in seconds
	const double GetTime()const;

	//!Check if the timer is currently stopped or running
	const bool IsStopped()const;

	//!This will tell the TimerManager that the timer should be deleted
	void Release();

	//!Start or unpause the timer
	void Start();

	//!Pause the timer
	void Stop();

	//!Should the timer pause and unpause when the game pauses?
	void SetPauseWithGame(bool pauseWithGame);

	//!returns if the timer pauses with the game
	bool PauseWithGame();	

	//!Set the current time
	/*!Normally you won't need to use this, but it's there in case you do.*/
	void SetTime(const double& time);	
protected:

	friend TimerManager;
	//!Call at least once every frame so the counter is ticked.
	/*!Call this method once per frame.
	Normally this is done by the TimerManager*/
	virtual void Update() = 0;

	friend TimerManager;
	//!Checks if the timer needs to be deleted
	/*!This is handled by the TimerManager*/
	const bool DeleteMe()const;

	friend TimerManager;
	virtual ~Timer();

	friend TimerManager;
	Timer();


	bool	m_IsRunning;
	//!can the timer be deleted?
	bool	m_DeleteMe;
	//!Does the timer pause/resume when the game pauses
	bool	m_PauseWithGame;
	//!The current time of the timer
	double	m_CurrentTime;
	
private:
	Timer(Timer& t);
	Timer& operator=(Timer& t);
};