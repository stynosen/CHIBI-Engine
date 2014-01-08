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
	MESSAGE_LEVEL_NORMAL //!Messages will be displayed in white
	,MESSAGE_LEVEL_INFO //!Messages will be displayed in yellow
	,MESSAGE_LEVEL_WARNING //!Messages will be displayed in red
	,MESSAGE_LEVEL_ERROR  //!Messages will be displayed in a pop-up, and close the application
};

#ifndef DEBUG_HEADER_LOG
#define DEBUG_HEADER_LOG
//!Log a message to the console
void Log(const std::tstring& message, const MESSAGE_LEVEL level = MESSAGE_LEVEL_NORMAL, const bool condition = false);
#endif


//Is_debug macro
#ifdef IS_DEBUG
	#undef IS_DEBUG
#endif

#if defined(DEBUG) | defined(_DEBUG)
	#define IS_DEBUG true
#else
	#define IS_DEBUG false
#endif


//!Debug class
class Debug final
{
public:

	//!Write messages to the console that can be casted into a tstring
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

	//!Write tstrings to the console
	static void LogMessage(const std::tstring& message, const MESSAGE_LEVEL level = MESSAGE_LEVEL_NORMAL, const bool condition = false);
	
	//!Write the contents of a var to the console
	template <class T>
	static void LogValue(const std::tstring& name, const T& value, const MESSAGE_LEVEL level = MESSAGE_LEVEL_NORMAL)
	{
		std::tstringstream buffer;
		buffer << _T("[") << name << _T("] : ");
		buffer << value;
		LogN<std::tstring>(buffer.str(), level, false);
	}

	//!Pop-up message or assert
	static void Popup(const std::tstring& message, const std::tstring& title, const bool quit = true);

	//!Condition based critical pop-up
	/*!This will close the application*/
	static void Assert(const bool condition, const std::tstring& message, const std::tstring& title = _T("ERROR"));

private:
	Debug();
	Debug(Debug& t);
	Debug& operator=(Debug& t);
};

//!Error class that can be used in a try/catch block
class ErrorMessage
{
public:
	ErrorMessage(const std::tstring& message, const std::tstring& title, const bool quit = true);
	~ErrorMessage();
	//!Fire the pop-up with the provided information
	void Fire();

private:
	//!Message that will be displayed in the pop-up
	std::tstring m_Message;
	//!Title of the pop-up
	std::tstring m_Title;
	//!Should the application close after closing the pop-up
	bool	m_Quit;
};