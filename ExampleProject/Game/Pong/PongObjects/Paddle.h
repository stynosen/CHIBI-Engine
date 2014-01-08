#pragma once
#include "Main.h"
#include "Engine/ChibiEngine.h"
#include "Objects/GameObject.h"

class Paddle : public GameObject
{
public :
	Paddle(bool left, int upButton, int downButton);
	virtual ~Paddle();

	virtual bool Initialize();
	virtual void Update();

	UINT GetScore();
	void AddScore(UINT score);
private:
	Vector2 m_Size;
	Vector2 m_Speed;
	UINT m_Score;
	bool m_IsLeft;

	int m_UpButton;
	int m_DownButton;

	Paddle(const Paddle& t);
	Paddle& operator=(const Paddle& t);
};