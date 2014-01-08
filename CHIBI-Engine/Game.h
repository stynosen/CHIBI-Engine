//---------------------------------------------------
//	CHIBI ENGINE v0.1
//  copyright Stijn Doyen
//---------------------------------------------------
//	Game.h
//---------------------------------------------------

#pragma once
#include "MainData.h"
#include "Engine/D3DXInitialiser.h"

//!The base Game class
/*!You must create a class that inherits this one only once per game!*/
class Game
{
public:
	virtual ~Game();

	//!This will run the game
	/*!This method should be called in the Main() method of the application*/
	int			Run();

protected:
	//!Protected constructor because you must create a inherited class
	Game(HINSTANCE hInstance);

	//!Method to change the settings of of the game screen before running it
	/*!See the GameSettings struct for more information*/
	virtual void SetWindowInfo(GameSettings& settings);
	//!Initialization of the game
	virtual bool GameInitialize();
	//!Load global content that must be available in all scenes
	virtual void LoadContent(){};
	//!Update the game
	/*!This will update the timers, the engine and the active scene.\n
	/You can Overload this method to add commands that must be executed before or after updating the game*/
	virtual void Update();
	//!This will paint the active scene
	/*!You can Overload this method to add commands that must be executed before or after painting the scene*/
	virtual void Paint();
	//!Overload this method to write specific message handling behavior
	/*!ONLY USE THIS WHEN YOU KNOW WHAT YOU ARE DOING!*/
	virtual void MessageProcedure(UINT msg, WPARAM wParam, LPARAM lParam){};

private:
	Game(const Game& t);
	Game& operator=(const Game& t);
};
