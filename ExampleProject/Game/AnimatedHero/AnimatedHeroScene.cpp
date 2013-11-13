#include "AnimatedHeroScene.h"

#include "Engine/ChibiEngine.h"

#include "Managers/AnimationManager.h"
#include "Managers/ImageManager.h"
#include "Managers/InputManager.h"

#include "Hero.h"
#include "../GameUI.h"


AnimatedHeroScene::AnimatedHeroScene(void)
{
	//We create the gameobjects in the initialise method, not in the constructor (no fail!)
}


AnimatedHeroScene::~AnimatedHeroScene(void)
{
	//Nothing to destroy, the Scene destroys the gameobjects when we close the programs
}

void AnimatedHeroScene::LoadContent()
{
	CHIBI->GetAnimationManager()->ParseAnimationFile(_T("Resources/Animations/Hero.anim"));
	CHIBI->GetImageManager()->AddTexture(_T("Resources/Images/Hero.bmp"), _T("Hero"));
}

bool AnimatedHeroScene::Initialise()
{
	bool succes = true;
	
	//Create the hero on the screen
	Hero* heroPtr = new Hero();
	heroPtr->PlayAnimation(_T("IdleDown"));
	heroPtr->SetForceUpdate(true);

	auto keysUIPtr = new GameUI();
	AddGameObjectToScene(heroPtr);
	AddGameObjectToScene(keysUIPtr);

	return succes;
}

// We don't need to overload the Draw and Update methods, since the gameobjects will be drawn and updated by the scene automatically