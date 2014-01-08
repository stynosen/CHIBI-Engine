#pragma once
#include "Engine/EngineMath.h"
#include "MainData.h"
#include "GameObject.h"
#include "AnimatedSprite.h"

//!A GameObject that contains an AnimatedSprite and has a certain speed and direction
class Actor : public GameObject
{
public:
	Actor(const tstring& animationSetTag);
	virtual ~Actor(void);

	virtual bool Initialize();
	virtual void Update();
	virtual void Paint();

	//!Play the Animation with given tag
	void PlayAnimation(const tstring& animName);
	//!Get the tag of the current Animation
	const tstring& GetCurrentAnimationTag();
	//!Pause or unpause the current Animation
	void SetPaused(const bool state);
	//!Check if the current Animation is paused
	bool IsPaused();
	
	//!Returns the direction of the actor
	const Vector2& GetDirection();
	//!Returns the current speed of the actor
	/*! The speed is multiplied by the direction to calculate the movement*/
	const Vector2& GetSpeed();
	//!Change the direction of the actor
	void SetDirection(const Vector2& dir);
	//!Change the speed of the actor
	void SetSpeed(const Vector2& speed);
	
	//!Update the actor even if it is outside of the screen
	void SetForceUpdate(bool state);

	//!returns the AnimatedSprite component of the actor
	AnimatedSprite* GetSprite();

protected:
	//!This method will move the actor
	/*!This will move the actor by it's speed in it's direction by default.
	You can overload this method to get a custom movement*/
	virtual void	Move();

	//!The pointer to the AnimatedSprite component of the actor
	AnimatedSprite*	m_SpritePtr;

	//!The current direction
	Vector2			m_Direction;
	//!The current speed
	Vector2			m_Speed;
	//!The tag of the current AnimationSet
	tstring			m_AnimationSetTag;

	//!Is the picot point in the bottom center of the actor
	/*!If this is false, the pivot is in the top-left corner*/
	bool			m_BottomCenter;

	//!Update the actor even if it is outside of the screen
	bool			m_ForceUpdate;

	//These are protected because you are not allowed to make an actor.
	//You should create a custom class that inherits the Actor class instead
	Actor(Actor& t);
	Actor& operator=(Actor& t);
};