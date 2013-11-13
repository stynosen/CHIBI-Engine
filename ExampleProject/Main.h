// We include the MainData.h from the engine here.
// This file contains all the macros, structs and typedefs used across the engines
#pragma once
#if defined(DEBUG) || defined(_DEBUG)
	#pragma comment(lib, "CHIBI-Engine_Debug.lib")
#else
	#pragma comment(lib, "CHIBI-Engine.lib")
#endif
#include "MainData.h"