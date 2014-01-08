#include "Main.h"
//--------------------------------------------------------------------------
//To change the game, change the following function to suit your game class
//eg. Change ExampleProject to SpaceInvaders
//	
//		#define GAME SpaceInvaders
//		#include "SpaceInvaders.h"
//
//-------------------------------------------------------------------------

#define GAME CHIBIGame
#include "CHIBI-Game.h"


//--------------------------------------------------------------------------
// This file contains code to start the actual game application.
// I strongly suggest that you don't change anything below this point
// Only make changes in this file if you know what you are doing!!
//-------------------------------------------------------------------------
void RunGame(HINSTANCE hInstance)
{
	GAME* pGameApp = new GAME(hInstance);
	//Run the game loop
	pGameApp->Run();
	delete pGameApp;
}

//-----------------------------------------------------------------
// application entry point called by Windows
//-----------------------------------------------------------------

int _tmain(int argc, _TCHAR* argv[])
{
	_tWinMain(GetModuleHandle(0),0,0,SW_SHOW);
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   TCHAR* cmdLine, int showCmd)
{
	//notify user if heap is corrupt
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL,0);

	// Enable run-time memory leak check for debug builds.
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
		//_CrtSetBreakAlloc(15722337);
	#endif
	RunGame(hInstance);
	return 0;
}