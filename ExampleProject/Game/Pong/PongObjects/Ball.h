#pragma once
#include "Main.h"
#include "Engine/ChibiEngine.h"
#include "Objects/GameObject.h"

class Ball : public GameObject
{
public :
	Ball();
	virtual ~Ball();

	virtual bool Initialize();
	virtual void Update();

	void Respawn();
private:
	void OnPaddleHit();

	Vector2 m_Size;
	Vector2 m_Direction;
	double	m_Speed;

	Ball(const Ball& t);
	Ball& operator=(const Ball& t);
};