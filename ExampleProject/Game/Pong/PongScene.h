#pragma once
#include "Components/Scene.h"

class PongScene : public Scene
{
public:
	PongScene(void);
	virtual ~PongScene(void);
	void LoadContent();
	bool Initialize();
private:
	
private:
	PongScene(PongScene& t);
	PongScene& operator=(PongScene& t);
};