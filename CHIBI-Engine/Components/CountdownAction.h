#pragma once
#include "MainData.h"
#include "Timer.h"
#include <functional>

class TimerManager;

//!A countdown timer that runs and action when 0 is reached
class CountDownAction final: public Timer 
{
public:
	// -------------------------
	// General Methods
	// -------------------------
	//!Set the current time back to the start time.
	void Reset(const bool start = false);
	//!Change the max time
	void SetMaxTime(const double& time);	

private:
	friend TimerManager;
	CountDownAction(const double& startTime, Action action);
	friend TimerManager;
	~CountDownAction();

	//!Call at least once every frame so the counter is ticked. (Normally this is done by the TimerManager)
	friend TimerManager;
	void Update();

	//!The start time of this countdown
	double			 m_StartTime;
	//!The lambda or functor that will be fired when the timer hits 0
	Action			 m_Action;

	CountDownAction(CountDownAction& t);
	CountDownAction& operator=(CountDownAction& t);
};