#pragma once
#include "Components/Scene.h"

class AnimatedHeroScene : public Scene
{
public:
	AnimatedHeroScene(void);
	virtual ~AnimatedHeroScene(void);
	void LoadContent();
	bool Initialize();
private:
	
private:
	AnimatedHeroScene(AnimatedHeroScene& t);
	AnimatedHeroScene& operator=(AnimatedHeroScene& t);
};

