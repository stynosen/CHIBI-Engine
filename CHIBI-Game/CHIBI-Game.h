#pragma once
#include "Game.h"

class CHIBIGame : public Game
{
public:
	CHIBIGame(HINSTANCE hInstance);
	virtual ~CHIBIGame(void);
	

	// This method is used to set all data to initialize the game screen
	virtual void SetWindowInfo(GameSettings& settings);

	// In this method all resources that are used in multiple scenes can be pre-loaded.
	virtual void LoadContent();

	// Create and initialize scenes
	virtual bool GameInitialize();

	// Add game Update logic here
	virtual void Update();

	// Add game paint logic here
	virtual void Paint();

private:
	CHIBIGame(CHIBIGame& t);
	CHIBIGame& operator=(CHIBIGame& t);
};