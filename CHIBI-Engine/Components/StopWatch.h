#pragma once
#include "MainData.h"
#include "Timer.h"

class StopWatch final: public Timer
{
public:
	// -------------------------
	// Constructors & Destructor
	// -------------------------
	StopWatch();
	~StopWatch();
	// -------------------------
	// General Methods
	// -------------------------
	//Set the current time back to 0
	void Reset(const bool start = false);

	//Call at least once every frame so the counter is ticked. (Normally this is done by the TimerManager)
	void Update();

private:

	StopWatch(StopWatch& t);
	StopWatch& operator=(StopWatch& t);
};