#pragma once
#include "Components/Scene.h"

class UI;

class TemplateScene : public Scene
{
public:
	TemplateScene(void);
	virtual ~TemplateScene(void);


	// In this method you can load all the scene specific content
	void LoadContent();

	// In this method you add all game objects that should be added directly to the scene
	bool Initialize();

	// In this method you write scene specific update logic
	void Update();

	// In this method you write scene specific paint logic
	void Paint();

private:
	UI* m_UIPtr;

	TemplateScene(TemplateScene& t);
	TemplateScene& operator=(TemplateScene& t);
};

