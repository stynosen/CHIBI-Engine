#include "ExampleProject.h"

#include "Engine/ChibiEngine.h"

#include "Managers/ImageManager.h"
#include "Managers/EffectManager.h"
#include "Managers/Inputmanager.h"
#include "Managers/Scenemanager.h"

#include "Game/Pong/PongScene.h"
#include "Game/AnimatedHero/AnimatedHeroScene.h"

#include <sstream>
#include <iostream>

ExampleProject::ExampleProject(HINSTANCE hInstance)
	:Game(hInstance)
{

}

ExampleProject::~ExampleProject()
{

}

void ExampleProject::LoadContent()
{
	//Load pixel bitmap
	CHIBI->GetImageManager()->AddTexture(_T("Resources/Images/Pixel.bmp"), _T("Pixel"));

	//Load Effects
	CHIBI->GetEffectManager()->AddEffect(_T("Resources/Shaders/PosTexTile.fx"), _T("TileMaterial"));
	CHIBI->GetEffectManager()->AddEffect(_T("Resources/Shaders/PosTex.fx"), _T("PosTexMaterial"));
	CHIBI->GetEffectManager()->AddEffect(_T("Resources/Shaders/PosColor.fx"), _T("PosColorMaterial"));
}

void ExampleProject::SetWindowInfo(GameSettings& settings)
{
	Game::SetWindowInfo(settings);
	settings.enableResize = false;
	settings.windowTitle = _T("ExampleProject");
}
bool ExampleProject::GameInitialize()
{
	//Create game scenes here

	//Create and initialise scenes
	CHIBI->GetSceneManager()->AddScene(_T("AnimatedHeroScene"), new AnimatedHeroScene());
	CHIBI->GetSceneManager()->AddScene(_T("PongScene"),new PongScene());
	CHIBI->GetSceneManager()->SetActiveScene(_T("PongScene"));
	return Game::GameInitialize();
}

void ExampleProject::Update()
{
	//Add game Update here
	tstringstream buffer;
	buffer << CHIBI->GetD3DXInit()->GetTitle() << _T(" - ") << CHIBI->GetFPS() << _T(" FPS");
	SetWindowText(CHIBI->GetD3DXInit()->GetWindow(),buffer.str().c_str());

	//Code to switch scene
	if (CHIBI->GetInputManager()->CheckMessage(VK_F1, KEYSTATE_PRESSED))
	{
		CHIBI->GetSceneManager()->SetActiveScene(_T("PongScene"));
		CHIBI->GetInputManager()->RemoveMessage(VK_F1, KEYSTATE_PRESSED);
	}

	if (CHIBI->GetInputManager()->CheckMessage(VK_F2, KEYSTATE_PRESSED))
	{
		CHIBI->GetSceneManager()->SetActiveScene(_T("AnimatedHeroScene"));
		CHIBI->GetInputManager()->RemoveMessage(VK_F2, KEYSTATE_PRESSED);
	}

	Game::Update();
}