#pragma once
#include "MainData.h"
#include <map>

using namespace std;

class Animation;
struct KeyFrame;

//! The class that contains data of a set of animations
class AnimationSet final
{
public :
	AnimationSet(const tstring& name, const tstring& fileName);
	~AnimationSet();
	
	//!Update this animation
	bool			Update();

	//!Play an animation in the map
	void			PlayAnimation(const tstring& animTag,bool reset = true);
	
	//!Set the current animation to another frame (returns if frame has been changed)
	bool			JumpToFrame(const int frame);
	
	//!Go to the next frame
	void			NextFrame();

	//!Start or resume the animation
	void			Play();

	//!Pause the animation at the current KeyFrame
	void			Pause();

	//!Get the paused state
	bool			IsPlaying()const;

	//!Reset the animation to the first KeyFrame
	void			Reset(bool stop = false);
	
	//!Alter animation speed (1 = normal)
	void			SetAnimationSpeed(double speed);
	//!Get the current animation speed (1 = normal)
	const double	GetAnimationSpeed()const;

	//!Get the current animation frame
	const KeyFrame	GetCurrentKeyFrame()const;
	//!Get the tag of the current animation
	const tstring&			GetCurrentAnimationTag()const;
	//!Get the tag of the animation with index x
	const tstring&			GetAnimationTagByIndex(const int index)const;
	//!Check if this animationSet has a certain animation
	bool					HasAnimation(const tstring& animationTag)const;

	//!One animationSet contains multiple animations (eg. walk, idle, run, ...)
	void					AddAnimation(Animation* animation, const tstring& animName);
	//!The Animation Manager always has one instance as a template, if an object want's to use it a clone (copy) is created.
	AnimationSet*			Clone()const;

private:
	//T!he file where the animationSet is located in
	tstring					m_AnimationFile;
	//!A map that holds every animation in the current animation set
	map<tstring,Animation*>	m_AnimationsPtrMap;
	//!The animation that is playing (eg. Walk)
	tstring					m_CurrentAnimation;

	//!The name of this animationSet (eg. Hero)
	tstring					m_AnimationSetName;

	//!Is the animation playing or is it paused?
	bool					m_IsPlaying;

	//!At what speed is the animation playing? 
	double					m_AnimationSpeed;


	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	AnimationSet(const AnimationSet& sRef);
	AnimationSet& operator=(const AnimationSet& sRef);
};