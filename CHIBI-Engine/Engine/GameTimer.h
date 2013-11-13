#pragma once
#include "MainData.h"
//=======================================================================================
// GameTimer.h by Frank Luna (C) 2008 All Rights Reserved.
// Adapted for DAE GP1 by Bart Uyttenhove
// Adapted for CHIBI-Engine by Stijn Doyen
//=======================================================================================
class GameTimer final
{
public:
	// -------------------------
	// Constructors & Destructor
	// -------------------------
	static void CreateTimer();	
	// -------------------------
	// General Methods
	// -------------------------

	static const double GetTime();  // in seconds
	static const double GetDeltaTime(); // in seconds

	static void Reset(); // Call before message loop.
	static void Start(); // Call when unpaused.
	static void Stop();  // Call when paused.
	static void Update();  // Call every frame.
	static const bool IsStopped();

private:
	//---------------------------
	// Private methods
	//---------------------------
	GameTimer();
	//---------------------------
	// Datamembers
	//---------------------------
	static __int64 m_BaseTime; //The computer time at the beginning of the timer
	static __int64 m_PausedTime; //The time the GameTimer got paused
	static __int64 m_StopTime;  //The time the GameTimer was stopped
	static __int64 m_PrevTime; 
	static __int64 m_CurrTime;

	static bool m_IsStopped;

	static double m_SecondsPerCount;
	static double m_DeltaTime;
};