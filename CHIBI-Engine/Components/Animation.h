#pragma once
#include "Engine/EngineMath.h"
#include "Engine/General.h"
#include <vector>

using namespace std;
class StopWatch;

struct AnimationFrame
{
	AnimationFrame()
	{
		FrameLength = 0;
		DrawRect = Rect(0,0,0,0);
		TextureTag = _T("");
	}

	AnimationFrame(const Rect& drawRect, double length, const tstring& textureTag)
	{
		FrameLength = length;
		DrawRect = drawRect;
		TextureTag = textureTag;
	}

	double	FrameLength;
	Rect	DrawRect;
	tstring	TextureTag;
};


class Animation final
{
	//This class is friend so the animations can be cloned
	friend class AnimationSet;

public:
	enum ANIM_FLAG
	{
		ANIM_FLAG_NONE = 0x00,
		ANIM_FLAG_LOOPING = 0x01,
		ANIM_FLAG_INERPOLATE_POSITION = 0x02,
	};

	Animation(const tstring& animationSetName, const tstring& animationName);
	~Animation();

	//Update the frame
	// Return bool states if the frame changed
	bool						Update(double dTime);

	//Set the animation to keyframe X
	void						JumpToKeyframe(int frame, bool resetTimer=true);

	//Add keyframes to the animation
	void						AddKeyFrame(const AnimationFrame& frame);
	void						AddKeyFrame(const AnimationFrame& frame, int pos);
	void						AddKeyFrame(const Rect& drawRect,double length);
	void						AddKeyFrame(const Rect& drawRect,double length, int pos);
	void						AddKeyFrame(const Rect& drawRect,double length, const tstring& textureTag);
	void						AddKeyFrame(const Rect& drawRect,double length, const tstring& textureTag, int pos);

	//Handle tags
	void						AddFlag(ANIM_FLAG flag);
	void						RemoveFlag(ANIM_FLAG flag);
	void						SetFlags(int flags);

	//Remove a keyframe from the animation
	void						RemoveKeyFrame(int id);

	//Get the current drawRect
	const Rect					GetCurrentDrawRect()const;
	const tstring				GetCurrentTexture()const;
	const int					GetCurrentFrameId()const;
	const AnimationFrame		GetCurrentFrame()const;
	const int					GetNrOfFrames()const;

private:

	Flag<ANIM_FLAG>				m_Flags;

	double						m_Timer;
	
	vector<AnimationFrame>		m_KeyFrames;
	int							m_CurrentFrame;
	int							m_NrOfFrames;

	tstring						m_LastTextureTag;
	tstring						m_AnimationName;
	tstring						m_AnimationSetName;


	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	Animation(const Animation& sRef);
	Animation& operator=(const Animation& sRef);
};