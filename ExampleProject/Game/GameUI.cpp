#include "GameUI.h"

#include "UI/UI.h"
#include "Components/Scene.h"
#include "Managers/FontManager.h"

#include "UI/UIString.h"


GameUI::GameUI()
{
}
GameUI::~GameUI()
{
}

bool GameUI::Initialise()
{
	//Create UI
	auto UIPtr = new UI();
	AddChild(UIPtr);

	UIString* keysHelpPtr = new UIString(_T("Score"), _T("F1: Pong\nF2: Animation example"), Vector2(10, 10), D3DXCOLOR(1, 1, 1, 1));
	
	//Add score to UI
	UIPtr->AddElement(keysHelpPtr);

	return GameObject::Initialise();
}