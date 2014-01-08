#pragma once
#include "Main.h"
#include "Objects/GameObject.h"

class UIString;

class GameUI : public GameObject
{
public:

	GameUI();
	virtual ~GameUI();

	virtual bool Initialize();
private:

	GameUI(const GameUI& t);
	GameUI& operator=(const GameUI& t);
};