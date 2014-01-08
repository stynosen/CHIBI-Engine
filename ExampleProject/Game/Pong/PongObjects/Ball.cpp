#include "Engine/Chibiengine.h"

#include "Objects/FilledRect.h"
#include "Components/Scene.h"
#include "Components/Hitregion.h"
#include "Managers/CollisionManager.h"

#include "Ball.h"
#include "Paddle.h"

Ball::Ball() :
	m_Size(20,20)
	, m_Direction(1,1)
	, m_Speed(100)
{
}

Ball::~Ball()
{
}

bool Ball::Initialize()
{
	//Be optimistic
	bool succes = true;

	//Draw the "ball" as a filled rect.
	auto filledRectPtr = new FilledRect(D3DXCOLOR(1, 1, 0, 1), m_Size.x, m_Size.y);
	AddChild(filledRectPtr);

	//We create a bounding rect to base the collision shape on
	CreateBoundingRect(Rect(Vector2(0, 0), m_Size));

	//Set the name of the object to Ball so it can be found in the scene
	SetName(_T("Ball"));

	//call the respawn method so the ball has a random direction and the correct position and speed
	Respawn();

	//Initialize before craeting the hitregion so the position of the boudningbox matches the world position instead of local position
	succes = GameObject::Initialize();

	//Use the collision manager to detect collision with a paddle
	auto hitRegionPtr = GetScene()->GetCollisionManager()->CreateHitRegionForObject(this, _T("Ball"));
	hitRegionPtr->AddCheckTag(_T("Paddle"));
	hitRegionPtr->OnlyCheckTags();
	hitRegionPtr->SetListener([&](GameObject* objectPtr, const tstring& tag)->void{OnPaddleHit();});

	//return if everyting went well
	return succes;
}

void Ball::Update()
{
	//Move the ball in the current direction with current speed, depending on delta time
	Translate(m_Direction*m_Speed*CHIBI->GetDeltaTime());
	
	//Get the half screen size since the origin is currently in teh center of the screen
	Vector2 halfScreenSize = Vector2(CHIBI->GetD3DXInit()->GetWidth(), CHIBI->GetD3DXInit()->GetHeight()) / 2;

	//Retrieve the position (GetPosition() instead of m_Position for global space)
	Vector2 position = GetPosition();

	//If the ball leaves the screen 
	if ((m_Direction.y == -1 && position.y < -halfScreenSize.y) || (m_Direction.y == 1 && position.y > halfScreenSize.y))
		m_Direction.y *= -1;

	//If the ball left the screen to the left, give right paddle a point and respawn
	if (position.x < -halfScreenSize.x)
	{
		GetScene()->GetGameobjectByName<Paddle>(_T("PaddleRight"))->AddScore(1);
		Respawn();
	}

	//If the ball left the screen to the right, give left paddle a point and respawn
	else if (position.x > halfScreenSize.x)
	{
		GetScene()->GetGameobjectByName<Paddle>(_T("PaddleLeft"))->AddScore(1);
		Respawn();
	}

	GameObject::Update();
}

void Ball::Respawn()
{
	//Random int between 0 and 100
	int randomNr = rand() % 100;

	SetPosition(Vector2(0, 0));
	m_Speed = 100;
	// 0->25   (-1, 1)
	// 25->50  (-1,-1)
	// 50->75  (1, -1)
	// 75->100 (1,  1)
	m_Direction = Vector2((randomNr>50) ? 1 : -1, (randomNr<25 || randomNr>75)? 1 : -1);
}

void Ball::OnPaddleHit()
{
	//This method will be fired if the ball has collision with a paddle
	if (GetPosition().x > 0 && m_Direction.x == 1)
	{
		m_Direction.x = -1;
		m_Speed += 10;
	}
	else if (GetPosition().x < 0 && m_Direction.x == -1)
	{
		m_Direction.x = 1;
		m_Speed += 10;
	}
}