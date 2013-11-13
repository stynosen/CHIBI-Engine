#include "PongScene.h"

#include "Engine/ChibiEngine.h"
#include "Managers/FontManager.h"

#include "PongObjects/Paddle.h"
#include "PongObjects/Ball.h"
#include "PongObjects/PongUI.h"

#include "../GameUI.h"

PongScene::PongScene(void)
{
	//We create the gameobjects in the initialise method, not in the constructor (no fail!)
}


PongScene::~PongScene(void)
{
	//Nothing to destroy, the Scene destroys the gameobjects when we close the programs
}

void PongScene::LoadContent()
{
	//Create font for the UI
	Font UIFont = Font();
	UIFont.fontName = _T("Arial");
	UIFont.size = 40;
	UIFont.tag = _T("UIFont");
	UIFont.weight = DWRITE_FONT_WEIGHT_BOLD;
	CHIBI->GetFontManager()->AddFont(UIFont);
}

bool PongScene::Initialise()
{
	bool succes = true;
	
	//Create the gameobjects
	auto leftPaddlePtr = new Paddle(true, 'Z', 'S');
	auto rightPaddlePtr = new Paddle(false, VK_UP, VK_DOWN);
	auto pallPtr = new Ball();
	auto UIPtr = new PongUI();
	auto keysUIPtr = new GameUI();

	//Add the gameobjects to the scene
	AddGameObjectToScene(leftPaddlePtr);
	AddGameObjectToScene(rightPaddlePtr);
	AddGameObjectToScene(pallPtr);
	AddGameObjectToScene(UIPtr);
	AddGameObjectToScene(keysUIPtr);

	return succes;
}

// We don't need to overload the Draw and Update methods, since the gameobjects will be drawn and updated by the scene automatically