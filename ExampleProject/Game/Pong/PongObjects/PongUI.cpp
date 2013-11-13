#include "PongUI.h"

#include "UI/UI.h"
#include "Components/Scene.h"
#include "Managers/FontManager.h"

#include "UI/UIString.h"
#include "Paddle.h"


PongUI::PongUI():
	m_ScoreDigitsPtr(nullptr)
{
}
PongUI::~PongUI()
{
}

bool PongUI::Initialise()
{
	//Create UI
	auto UIPtr = new UI();
	AddChild(UIPtr);

	m_ScoreDigitsPtr = new UIString(_T("Score"), _T("0 - 0"), Vector2(450, 0),D3DXCOLOR(1,1,1,1),_T("UIFont"));
	
	//Add score to UI
	UIPtr->AddElement(m_ScoreDigitsPtr);

	return GameObject::Initialise();
}

void PongUI::Update()
{
	//update the string to the current score
	tstringstream buffer;
	buffer << GetScene()->GetGameobjectByName<Paddle>(_T("PaddleLeft"))->GetScore() << _T(" - ") << GetScene()->GetGameobjectByName<Paddle>(_T("PaddleRight"))->GetScore();
	m_ScoreDigitsPtr->SetValue(buffer.str());
	GameObject::Update();
}