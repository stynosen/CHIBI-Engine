#pragma once
#include "Manager.h"

#include "MainData.h"
#include <map>

using namespace std;

class AnimationSet;

//!The manager that stores and manages all the animation sets
class AnimationManager final : public Manager
{
public:
	AnimationManager(void);
	~AnimationManager(void);

	//!Add an animation file to the manager
	void ParseAnimationFile(const tstring& filePath);
	//!Remove an animation set from the manager
	void RemoveAnimation(const tstring& setName);
	//!Remove all animation sets from the manager
	void RemoveAllAnimations();
	//!Check if an animation set is present
	bool IsAnimationSetPresent(const tstring& setName)const;
	//!Retrieve an animation set from the manager
	AnimationSet* GetAnimationSet(const tstring& setName)const;

private:
	//!A map that stores all animation sets with a tag
	/*!By storing it with a tag, it can be retrieved much faster*/
	map<tstring,AnimationSet*> m_AnimationSetPtrMap;

private:
	AnimationManager(AnimationManager& t);
	AnimationManager& operator=(AnimationManager& t);
};