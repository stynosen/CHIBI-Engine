#pragma once
#include "MainData.h"
#include "Timer.h"

class TimerManager;

//!A countdown timer that stops when 0 is reached
class CountDown final: public Timer
{
public:
	//!Set the current time back to the start time.
	void Reset(const bool start = false);
	//!Change the max time
	void SetMaxTime(const double& time);

private:
	friend TimerManager;
	CountDown(const double& startTime);
	friend TimerManager;
	~CountDown();

	//!Call at least once every frame so the counter is ticked. (Normally this is done by the TimerManager)
	friend TimerManager;
	void Update();

	//!The start time of this countdown
	double m_StartTime;

	CountDown(CountDown& t);
	CountDown& operator=(CountDown& t);
};