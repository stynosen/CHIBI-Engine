#pragma once
#include "MainData.h"
#include "Timer.h"
#include <functional>

class CountDownAction final: public Timer 
{
public:
	// -------------------------
	// Constructors & Destructor
	// -------------------------
	CountDownAction(const double& startTime, Action action);
	~CountDownAction();
	// -------------------------
	// General Methods
	// -------------------------
	//Set the current time back to the start time.
	void Reset(const bool start = false);
	//Call at least once every frame so the counter is ticked. (Normally this is done by the TimerManager)
	void Update();
	//Change the max time
	void SetMaxTime(const double& time);	

private:
	double			 m_StartTime;
	//The lambda or functor that will be fired when the timer hits 0
	Action			 m_Action;

	CountDownAction(CountDownAction& t);
	CountDownAction& operator=(CountDownAction& t);
};