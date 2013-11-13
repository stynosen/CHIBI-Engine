#pragma once
#include "MainData.h"
#include "Timer.h"

class CountDown final: public Timer
{
public:
	// -------------------------
	// Constructors & Destructor
	// -------------------------
	CountDown(const double& startTime);
	~CountDown();
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
	double m_StartTime;

	CountDown(CountDown& t);
	CountDown& operator=(CountDown& t);
};