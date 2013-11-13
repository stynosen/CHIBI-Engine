#include "Main.h"

#include "ExampleProject.h"
void RunGame(HINSTANCE hInstance)
{
	ExampleProject* pGameApp = new ExampleProject(hInstance);
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