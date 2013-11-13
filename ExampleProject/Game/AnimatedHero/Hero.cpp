#include "Hero.h"

#include "Engine/Chibiengine.h"

#include "Managers/AnimationManager.h"
#include "Managers/ImageManager.h"
#include "Managers/InputManager.h"


Hero::Hero() :
	Actor(_T("Hero"))
{

}

Hero::~Hero()
{

}

void Hero::Update()
{
	Actor::Update();
	if (CHIBI->GetInputManager()->CheckKeyState(VK_UP, KEYSTATE::KEYSTATE_DOWN))
	{
		m_Direction.y = -1;
		m_Direction.x = 0;
		m_Speed.x = 100;
		m_Speed.y = 100;
	}
	else if (CHIBI->GetInputManager()->CheckKeyState(VK_DOWN, KEYSTATE::KEYSTATE_DOWN))
	{
		m_Direction.y = 1;
		m_Direction.x = 0;
		m_Speed.x = 100;
		m_Speed.y = 100;
	}
	else if (CHIBI->GetInputManager()->CheckKeyState(VK_LEFT, KEYSTATE::KEYSTATE_DOWN))
	{
		m_Direction.y = 0;
		m_Direction.x = -1;
		m_Speed.x = 100;
		m_Speed.y = 100;
	}
	else if (CHIBI->GetInputManager()->CheckKeyState(VK_RIGHT, KEYSTATE::KEYSTATE_DOWN))
	{
		m_Direction.y = 0;
		m_Direction.x = 1;
		m_Speed.x = 100;
		m_Speed.y = 100;
	}
	else
	{
		m_Speed.x = 0;
		m_Speed.y = 0;
	}

	//Get animation name
	tstring animName;
	if (m_Speed.x <= EPSILON && m_Speed.y <= EPSILON)		animName = _T("Idle");
	else													animName = _T("Walking");

	if (m_Direction.x == -1)
		animName += _T("Left");

	else if (m_Direction.x == 1)
		animName += _T("Right");

	else if (m_Direction.y == -1)
		animName += _T("Up");

	else
		animName += _T("Down");

	if (GetCurrentAnimationTag() != animName)
		PlayAnimation(animName);

}