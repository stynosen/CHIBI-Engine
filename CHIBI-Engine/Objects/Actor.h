#pragma once
#include "Engine/EngineMath.h"
#include "MainData.h"
#include "GameObject.h"
#include "AnimatedSprite.h"

class Actor : public GameObject
{
public:
	Actor(const tstring& animationFile);
	virtual ~Actor(void);

	virtual bool Initialise();
	virtual void Update();
	virtual void Paint();

	void PlayAnimation(const tstring& animName);
	const tstring& GetCurrentAnimationTag();
	void SetPaused(const bool state);
	bool IsPaused();
	
	const Vector2& GetDirection();
	const Vector2& GetSpeed();
	void SetDirection(const Vector2& dir);
	void SetSpeed(const Vector2& speed);
	
	//Update the actor even if it is outside of the screen
	void SetForceUpdate(bool state);

	AnimatedSprite* GetSprite();

protected:
	virtual void	Move();

	AnimatedSprite*	m_SpritePtr;

	Vector2			m_Direction;
	Vector2			m_Speed;
	tstring			m_AnimationFile;

	bool			m_BottomCenter;
	bool			m_ForceUpdate;

	Actor(Actor& t);
	Actor& operator=(Actor& t);
};