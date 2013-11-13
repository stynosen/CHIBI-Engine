#pragma once
#include "MainData.h"
class Timer
{
public:
	// -------------------------
	// Constructors & Destructor
	// -------------------------
	virtual ~Timer();
	// -------------------------
	// General Methods
	// -------------------------

	//Reset the timer to the starting time
	virtual void Reset(const bool start = false)=0;

	//Call at least once every frame so the counter is ticked. (Normally this is done by the TimerManager)
	virtual void Update()=0;  // Call every frame.
	
	//Get the current time in seconds
	const double GetTime()const;

	//Check if the timer is currently stopped or running
	const bool IsStopped()const;

	//Checks if the timer needs to be deleted
	//This is handled by the TimerManager
	const bool DeleteMe()const;

	//This will tell the TimerManager that the timer should be deleted
	void Delete();

	//Start or unpause the timer
	void Start();

	//Pause the timer
	void Stop();

	//Should the timer pause and unpause when the game pauses?
	void SetPauseWithGame(bool pauseWithGame);

	//returns if the timer pauses with the game
	bool PauseWithGame();	

	//Set the current time
	//Normally you won't need to use this, but it's there in case you do.
	void SetTime(const double& time);	
protected:
	
	Timer();
	//---------------------------
	// Private methods
	//---------------------------
	
	//---------------------------
	// Datamembers
	//---------------------------
	bool	m_IsRunning;
	bool	m_DeleteMe;
	bool	m_PauseWithGame;
	double	m_CurrentTime;
	
private:
	Timer(Timer& t);
	Timer& operator=(Timer& t);
};