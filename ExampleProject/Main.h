//--------------------------------------------------------------------------
// This file contains all settings to load the Engine correctly.
// Only make changes in this file if you know what you are doing!
//-------------------------------------------------------------------------


// We include the MainData.h from the engine here.
// This file contains all the macros, structs and typedefs used across the engines
#pragma once

//*****************************************************************************
// Include CHIBI libs
//*****************************************************************************

//Visual studio 2013
#ifndef _UNICODE
	#error The CHIBI-Engine is compiled with Unicode support. Please change the character settings to UNICODE to contiue using the CHIBI-Engine.
#endif

#if (_MSC_PLATFORM_TOOLSET == 120)
	#if defined(DEBUG) | defined(_DEBUG)
		#pragma comment(lib, "CHIBI-Engine_120_Debug.lib")
	#else
		#pragma comment(lib, "CHIBI-Engine_120_Release.lib")
	#endif
#else
	//Visual studio 2012
	#if(_MSC_PLATFORM_TOOLSET == 110)
		#if defined(DEBUG) | defined(_DEBUG)
			#pragma comment(lib, "CHIBI-Engine_110_Debug.lib")
		#else
			#pragma comment(lib, "CHIBI-Engine_110_Release.lib")
		#endif
	#else
	//Older or newer version (no lib file)
		#error This version of the visual studio compiler is not supported by the CHIBI-Engine. Change the compiler version to v110 (vs2012) or v120 (vs2013) in the project settings
	#endif
#endif

#include "MainData.h"