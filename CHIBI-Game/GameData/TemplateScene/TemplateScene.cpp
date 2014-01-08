#include "TemplateScene.h"

// Include the actual Engine
#include "Engine/ChibiEngine.h"

// Include all managers used in this file
#include "Managers/InputManager.h"
#include "Managers/AnimationManager.h"
#include "Managers/Imagemanager.h"
#include "Managers/ActionManager.h"
#include "Managers/SceneManager.h"

// Include pre-created objects that reside in the engine
#include "Objects/LimitCamera.h"
#include "UI/UI.h"

TemplateScene::TemplateScene(void):
	m_UIPtr(nullptr)
{

}

TemplateScene::~TemplateScene(void)
{

}

// In this method you can load all the scene specific content.
// If you switch to another scene after this one was active, the resources will remain available for the other scene to use.
void TemplateScene::LoadContent()
{
	
}

// In this method you add all game objects that should be added directly to the scene
bool TemplateScene::Initialize()
{
	bool succes = true;
	
	m_UIPtr = new UI();
	m_UIPtr->SetPosition(Vector2(10, 10));
	AddGameObjectToScene(m_UIPtr);
	m_UIPtr->SetName(_T("HUD"));

	GameTimer::Stop();
	GameTimer::Reset();
	GameTimer::Start();

	return succes;
}

// In this method you write scene specific update logic
void TemplateScene::Update()
{

}

// In this method you write scene specific paint logic
// Keep in mind that GameObjects that are added to the scene will be drawn automatically
void TemplateScene::Paint()
{

}