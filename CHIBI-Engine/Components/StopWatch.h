#pragma once
#include "MainData.h"
#include "Timer.h"

class Timermanager;

//!A timer that starts at 0 and counts up
class StopWatch final: public Timer
{
public:
	//!Set the current time back to 0
	void Reset(const bool start = false);


private:

	friend TimerManager;
	StopWatch();
	friend TimerManager;
	~StopWatch();

	friend TimerManager;
	//!Call at least once every frame so the counter is ticked. (Normally this is done by the TimerManager)
	void Update();
	StopWatch(StopWatch& t);
	StopWatch& operator=(StopWatch& t);
};