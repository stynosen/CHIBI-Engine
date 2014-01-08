#pragma once
#include "MainData.h"
//=======================================================================================
// GameTimer.h by Frank Luna (C) 2008 All Rights Reserved.
// Adapted for DAE GP1 by Bart Uyttenhove
// Adapted for CHIBI-Engine by Stijn Doyen
//=======================================================================================
class Game;
class TimerManager;

//!The timer used to calculate the game time and the delta time
/*!All times are calculated and stored in seconds*/
class GameTimer final
{
public:
	// -------------------------
	// General Methods
	// -------------------------
	
	//!Get the current game time in seconds
	static const double GetTime();
	//!Get the time since the last frame in seconds
	static const double GetDeltaTime();

	//!Reset the game timer
	/*!Sets the game time and delta time back to 0*/
	static void Reset();
	//!Start or unpause the game
	static void Start();
	//!Pause the game
	static void Stop();
	//!Check if the game is currently paused
	static const bool IsStopped();

private:
	//---------------------------
	// Private methods
	//---------------------------
	GameTimer();

	friend Game;
	static void CreateTimer();

	friend TimerManager;
	//!Call this once per frame
	/*!It is called automatically by the engine*/
	static void Update();

	//---------------------------
	// Data members
	//---------------------------
	//!The computer time at the beginning of the timer (in seconds)
	static __int64 m_BaseTime;
	//!The time the GameTimer got paused (in seconds)
	static __int64 m_PausedTime;
	//!The time the GameTimer was stopped (in seconds)
	static __int64 m_StopTime;
	//!The time at the last frame (in seconds)
	static __int64 m_PrevTime; 
	//!The time at the current frame (in seconds)
	static __int64 m_CurrTime;

	//!Is the game paused or not
	static bool m_IsStopped;

	//!Amount of seconds per CPU clock count
	static double m_SecondsPerCount;

	//!The time since the last frame (in seconds)
	static double m_DeltaTime;
};