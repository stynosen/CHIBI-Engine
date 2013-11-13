#pragma once
#include "MainData.h"
#include <map>

using namespace std;

class AnimationSet;

class AnimationManager final
{
public:
	AnimationManager(void);
	~AnimationManager(void);

	//Add an animation file to the manager
	void ParseAnimationFile(const tstring& filePath);
	void RemoveAnimation(const tstring& setName);
	void RemoveAllAnimations();
	bool IsAnimationSetPresent(const tstring& setName)const;
	AnimationSet* GetAnimationSet(const tstring& setName)const;

private:
	map<tstring,AnimationSet*> m_AnimationSetPtrMap;

private:
	AnimationManager(AnimationManager& t);
	AnimationManager& operator=(AnimationManager& t);
};