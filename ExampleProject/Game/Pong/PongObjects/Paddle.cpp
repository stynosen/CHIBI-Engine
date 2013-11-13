#include "Paddle.h"

#include "Engine/Chibiengine.h"
#include "Managers/CollisionManager.h"
#include "Managers/InputManager.h"
#include "Objects/FilledRect.h"
#include "Components/Scene.h"


Paddle::Paddle(bool left, int upButton, int downButton) :
	m_IsLeft(left)
	, m_Score(0)
	, m_Size(20,100)
	, m_Speed(0,100)
	, m_UpButton(upButton)
	, m_DownButton(downButton)
{
}

Paddle::~Paddle()
{
}

bool Paddle::Initialise()
{
	//Be optimistic
	bool succes = true;

	//Draw the "paddle" as a filled rect.
	auto filledRectPtr = new FilledRect(D3DXCOLOR(1, 0, 0, 1), m_Size.x, m_Size.y);
	AddChild(filledRectPtr);

	//We create a bounding rect to base the collision shape on
	CreateBoundingRect(Rect(Vector2(0, 0), m_Size));

	//Give a name to the object so it can be found in the scene
	tstring name = "Paddle";
	if (m_IsLeft)
	{
		name += "Left";
		SetPosition(Vector2(-(CHIBI->GetD3DXInit()->GetWidth() / 2) + 100, 0));
	}
	else
	{
		name += "Right";
		SetPosition(Vector2((CHIBI->GetD3DXInit()->GetWidth() / 2) - 100, 0));
	}
	SetName(name);

	//Initialise before craeting the hitregion so the position of the boudningbox matches the world position instead of local position
	succes = GameObject::Initialise();

	//Create a hitregion for the paddle.
	//The paddle itself doensn't need to check anything since the ball will be checking for the paddles.
	GetScene()->GetCollisionManager()->CreateHitRegionForObject(this, _T("Paddle"));

	return succes;
}

void Paddle::Update()
{
	//Translate accoring to the keypressed
	if (CHIBI->GetInputManager()->CheckKeyState(m_UpButton, KEYSTATE_DOWN))
		Translate(-m_Speed*CHIBI->GetDeltaTime());

	if (CHIBI->GetInputManager()->CheckKeyState(m_DownButton, KEYSTATE_DOWN))
		Translate(m_Speed*CHIBI->GetDeltaTime());

	GameObject::Update();
}

UINT Paddle::GetScore()
{
	return m_Score;
}

void Paddle::AddScore(UINT score)
{
	m_Score += score;
}