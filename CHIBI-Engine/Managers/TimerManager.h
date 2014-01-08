#pragma once
#include "Manager.h"

#include "MainData.h"
#include <list>
#include <functional>
class Timer;
class CountDown;
class CountDownAction;
class StopWatch;

using namespace std;

//!The manager that creates, stores and handles all timers
class TimerManager final : public Manager
{
public:
	TimerManager();
	~TimerManager();

	//!Update all timers
	/*!This is called once per frame to tick every timer*/
	void				Update();

	//!Pause the game
	void				PauseGame();
	//!UnPause the game
	void				UnPauseGame();

	//!Create a new stopwatch
	/*!Creates the stopwatch and adds it to the manager. It will return the new stopwatch*/
	StopWatch*			CreateStopWatch();
	//!Create a new countdown timer
	/*!Creates the countdown timer and adds it to the manager. It will return the new countdown timer*/
	CountDown*			CreateCountDown(const double& runTime);
	//!Create a new countdown action timer
	/*!Creates the countdown action timer and adds it to the manager. It will return the new countdown action timer*/
	CountDownAction*	CreateCountDownAction(const double& runTime, Action functionToFire);

	//!Use this method to remove a timer.
	/*!Don't delete them manually because the manager won't know if it's already deleted!*/
	void				RemoveTimer(Timer* timerPtr);

private:
	//!A list that contains all the timers that still exist in memory
	list<Timer*>		m_TimersPtrList;

	TimerManager(TimerManager& t);
	TimerManager& operator=(TimerManager& t);
};