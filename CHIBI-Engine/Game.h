//---------------------------------------------------
//	CHIBI ENGINE v0.1
//  copyright Stijn Doyen
//---------------------------------------------------
//	Game.h
//---------------------------------------------------

#pragma once
#include "MainData.h"
#include "Engine/D3DXInitialiser.h"

class Game
{
public:
	Game(HINSTANCE hInstance);
	virtual ~Game();

	//Message handling
	int			Run();

protected:
	// Game methods 
	virtual void SetWindowInfo(GameSettings& settings);
	virtual bool GameInitialize();
	virtual void LoadContent(){};
	virtual void Update();
	virtual void Paint();
	virtual void MessageProcedure(UINT msg, WPARAM wParam, LPARAM lParam){};

private:
	Game(const Game& t);
	Game& operator=(const Game& t);
};
