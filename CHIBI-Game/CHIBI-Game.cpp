#include "CHIBI-Game.h"

#include "Engine/ChibiEngine.h"

#include "Managers/ImageManager.h"
#include "Managers/EffectManager.h"
#include "Managers/SceneManager.h"

#include "GameData/TemplateScene/TemplateScene.h"

#include <sstream>
#include <iostream>

CHIBIGame::CHIBIGame(HINSTANCE hInstance)
	:Game(hInstance)
{

}

CHIBIGame::~CHIBIGame()
{

}

// This method is used to set all data to initialize the game screen
void CHIBIGame::SetWindowInfo(GameSettings& settings)
{
	Game::SetWindowInfo(settings);
	settings.enableResize = true;
	settings.windowTitle = _T("CHIBI-Game");
}

// In this method all resources that are used in multiple scenes can be pre-loaded.
// This way changing scenes will be much faster
void CHIBIGame::LoadContent()
{

	// Load pixel bitmap
	CHIBI->GetImageManager()->AddTexture(_T("Resources/Images/Pixel.bmp"), _T("Pixel"));

	// Load shaders
	CHIBI->GetEffectManager()->AddEffect(_T("Resources/Shaders/PosTexTile.fx"), _T("TileMaterial"));
	CHIBI->GetEffectManager()->AddEffect(_T("Resources/Shaders/PosTex.fx"),		_T("PosTexMaterial"));
	CHIBI->GetEffectManager()->AddEffect(_T("Resources/Shaders/PosColor.fx"),	_T("PosColorMaterial"));
}

// Create and initialize scenes
bool CHIBIGame::GameInitialize()
{
	CHIBI->GetSceneManager()->AddScene(_T("TemplateScene"), new TemplateScene());
	CHIBI->GetSceneManager()->SetActiveScene(_T("TemplateScene"));

	return Game::GameInitialize();
}

// Add game Update logic here
void CHIBIGame::Update()
{
	tstringstream buffer;
	buffer << CHIBI->GetD3DXInit()->GetTitle() << _T(" - ") << CHIBI->GetFPS() << _T(" FPS");
	SetWindowText(CHIBI->GetD3DXInit()->GetWindow(), buffer.str().c_str());

	Game::Update();
}

// Add game paint logic here
void CHIBIGame::Paint()
{
	Game::Paint();
}