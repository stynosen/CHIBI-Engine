#pragma once
#include "Game.h"

class ExampleProject : public Game
{
public:
	ExampleProject(HINSTANCE hInstance);
	virtual ~ExampleProject(void);
	virtual void LoadContent();
	virtual void SetWindowInfo(GameSettings& settings);
	virtual bool GameInitialize();
	virtual void Update();

private:
	ExampleProject(ExampleProject& t);
	ExampleProject& operator=(ExampleProject& t);
};