//---------------------------------------------------
//	CHIBI ENGINE v0.1
//  copyright Stijn Doyen
//---------------------------------------------------
//	Debug.h	
//---------------------------------------------------

#pragma once

#include "MainData.h"
#include "Engine/EngineMath.h"
#include <iostream>
#include <sstream>

enum MESSAGE_LEVEL
{
	MESSAGE_LEVEL_NORMAL
	,MESSAGE_LEVEL_INFO
	,MESSAGE_LEVEL_WARNING
	,MESSAGE_LEVEL_ERROR
};

#ifndef DEBUG_HEADER_LOG
#define DEBUG_HEADER_LOG
void Log(const std::tstring& message, const MESSAGE_LEVEL level = MESSAGE_LEVEL_NORMAL, const bool condition = false);
#endif


//Is debug macro
#ifdef IS_DEBUG
	#undef IS_DEBUG
#endif

#if defined(DEBUG) | defined(_DEBUG)
	#define IS_DEBUG true
#else
	#define IS_DEBUG false;
#endif


//Debug class
class Debug final
{
public:

	//Write messages to the console that are not tstrings
	template <class T>
	static void LogN(const T& message, const MESSAGE_LEVEL level = MESSAGE_LEVEL_NORMAL, const bool condition = false)
	{
		//Only preform logs in debug mode
		#if defined(DEBUG) | defined(_DEBUG)
			if(!condition)
			{
				HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
				std::tstringstream buffer;
				buffer << message << endl;
				switch(level)
				{
					case MESSAGE_LEVEL_NORMAL:
						SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
						tcout << buffer.str();
					break;

					case MESSAGE_LEVEL_INFO:
						SetConsoleTextAttribute(hStdout, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
						tcout << buffer.str();
					break;	

					case MESSAGE_LEVEL_WARNING:
						SetConsoleTextAttribute(hStdout, FOREGROUND_RED|FOREGROUND_INTENSITY);
						tcout << buffer.str();
					break;	

					case MESSAGE_LEVEL_ERROR:
						ASSERT(false,buffer.str().c_str());
					break;
				}
			}
		#endif
	}

	//write tstrings to the console
	static void LogMessage(const std::tstring& message, const MESSAGE_LEVEL level = MESSAGE_LEVEL_NORMAL, const bool condition = false);
	
	//write the contents of a var to the console
	template <class T>
	static void LogValue(const std::tstring& name, const T& value, const MESSAGE_LEVEL level = MESSAGE_LEVEL_NORMAL)
	{
		std::tstringstream buffer;
		buffer << _T("[") << name << _T("] : ");
		buffer << value;
		LogN<std::tstring>(buffer.str(), level, false);
	}

	//Popup message or assert
	static void Popup(const std::tstring& message, const std::tstring& title, const bool quit = true);

	//Condition based critical popup
	static void Assert(const bool condition, const std::tstring& message, const std::tstring& title = _T("ERROR"));

private:
	Debug();
	Debug(Debug& t);
	Debug& operator=(Debug& t);
};

class ErrorMessage
{
public:
	ErrorMessage(const std::tstring& message, const std::tstring& title, const bool quit = true);
	~ErrorMessage();
	void Fire();

private:
	std::tstring m_Message;
	std::tstring m_Title;
	bool	m_Quit;
};