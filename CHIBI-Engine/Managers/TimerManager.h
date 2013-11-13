#pragma once
#include "MainData.h"
#include <list>
#include <functional>
class Timer;
class CountDown;
class CountDownAction;
class StopWatch;

using namespace std;

class TimerManager final
{
public:
	TimerManager();
	~TimerManager();

	//This is called once per frame to tick every timer
	void				Update();

	void				PauseGame();
	void				UnPauseGame();

	StopWatch*			CreateStopWatch();
	CountDown*			CreateCountDown(const double& runTime);
	CountDownAction*	CreateCountDownAction(const double& runTime, Action functionToFire);

	//Use this method to remove a timer.
	//Don't delete it manualy because the manager won't know if it's already deleted!
	void				RemoveTimer(Timer* timerPtr);

private:
	list<Timer*>		m_TimersPtrList;

	TimerManager(TimerManager& t);
	TimerManager& operator=(TimerManager& t);
};