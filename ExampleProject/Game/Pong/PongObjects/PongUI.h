#pragma once
#include "Main.h"
#include "Objects/GameObject.h"

class UIString;

class PongUI : public GameObject
{
public:

	PongUI();
	virtual ~PongUI();

	virtual bool Initialize();
	virtual void Update();
private:
	UIString* m_ScoreDigitsPtr;

	PongUI(const PongUI& t);
	PongUI& operator=(const PongUI& t);
};