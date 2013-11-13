//---------------------------------------------------
//	CHIBI ENGINE v0.1
//  copyright Stijn Doyen
//---------------------------------------------------
//	SceneManager.h
//---------------------------------------------------
#pragma once
#include "MainData.h"
#include <map>

using namespace std;

class Scene;

class SceneManager final
{
public:
	SceneManager(void);
	~SceneManager(void);

	//Initialse the scene with given name
	void Initialise(const tstring& name);

	//Initialise the active scene
	void Initialise();

	//update the active scene
	void Update();

	//Paint the active scene
	void Paint();

	//Adds a scene to the manager
	//This will call the LoadContent and initialise of that scene
	bool AddScene(const tstring& name, Scene* scenePtr);

	//Change the scene
	void SetActiveScene(const tstring& name);

	//Get a pointer the active scene
	Scene* GetActiveScene();
private:
	map<tstring,Scene*> m_GameScenes;
	tstring m_ActiveScene;

private:
	SceneManager(SceneManager& t);
	SceneManager& operator=(SceneManager& t);
};