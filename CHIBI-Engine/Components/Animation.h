#pragma once
#include "Engine/EngineMath.h"
#include "Engine/General.h"
#include <vector>

using namespace std;
class StopWatch;

//! A struct that contains data of a single animation frame
struct KeyFrame
{
	KeyFrame()
	{
		FrameLength = 0;
		DrawRect = Rect(0,0,0,0);
		TextureTag = _T("");
	}

	KeyFrame(const Rect& drawRect, double length, const tstring& textureTag)
	{
		FrameLength = length;
		DrawRect = drawRect;
		TextureTag = textureTag;
	}

	//! The lengths in seconds of this frame
	double	FrameLength;

	//! The rectangle that needs to be drawn from the source texture
	Rect	DrawRect;

	//! The tag of the texture that stores this frame
	tstring	TextureTag;
};


//! The class that contains data of an animation
class Animation final
{
	//This class is friend so the animations can be cloned
	friend class AnimationSet;

public:
	//! Animation flags
	enum ANIM_FLAG
	{
		//! No special behavior
		ANIM_FLAG_NONE = 0x00,
		//! Loop the animation (auto play and return to the first frame after the last frame)
		ANIM_FLAG_LOOPING = 0x01,
		//! interpolate position (slide over the source bitmap instead of snapping)
		ANIM_FLAG_INERPOLATE_POSITION = 0x02,
	};

	Animation(const tstring& animationSetName, const tstring& animationName);
	~Animation();

	//! Update the frame
	/*! Return boolean states if the frame changed. */
	bool						Update(double dTime);

	//! Set the animation to KeyFrame X
	void						JumpToKeyframe(int frame, bool resetTimer=true);

	//! Add KeyFrames to the animation
	void						AddKeyFrame(const KeyFrame& frame);
	//! Add KeyFrames to the animation
	void						AddKeyFrame(const KeyFrame& frame, int pos);
	//! Add KeyFrames to the animation
	void						AddKeyFrame(const Rect& drawRect, double length);
	//! Add KeyFrames to the animation
	void						AddKeyFrame(const Rect& drawRect, double length, int pos);
	//! Add KeyFrames to the animation
	void						AddKeyFrame(const Rect& drawRect, double length, const tstring& textureTag);
	//! Add KeyFrames to the animation
	void						AddKeyFrame(const Rect& drawRect,double length, const tstring& textureTag, int pos);

	//! Add an animation flag
	void						AddFlag(ANIM_FLAG flag);
	//! Remove an animation flag
	void						RemoveFlag(ANIM_FLAG flag);
	//! Set the animation flags to a certain combination of flags
	/*! This method is used when loading an animation file.
	Normally you will never need to call this manually*/
	void						SetFlags(int flags);

	//! Remove a KeyFrame from the animation
	void						RemoveKeyFrame(int id);

	//! Get the current drawRect
	const Rect					GetCurrentDrawRect()const;
	//! Get the current Texture tag
	const tstring				GetCurrentTexture()const;
	//! Get the current frame id
	const int					GetCurrentFrameId()const;
	//! Get the current frame
	const KeyFrame		GetCurrentFrame()const;
	//! Get the amount of frames
	const int					GetNrOfFrames()const;

private:

	//! The flags that are used to process this animation
	Flag<ANIM_FLAG>				m_Flags;

	//! The current animation time
	double						m_Timer;

	//! Container that contains all the KeyFrames
	vector<KeyFrame>		m_KeyFrames;
	//! Current KeyFrame
	int							m_CurrentFrame;
	//! Total amount of KeyFrames
	int							m_NrOfFrames;

	//! The texture tag that was used last
	/*! This is stored for optimization purposes*/
	tstring						m_LastTextureTag;
	//! The name of this animation
	tstring						m_AnimationName;
	//! The name of the animationSet that contains this animation
	tstring						m_AnimationSetName;

	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	Animation(const Animation& sRef);
	Animation& operator=(const Animation& sRef);
};