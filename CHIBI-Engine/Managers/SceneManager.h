//---------------------------------------------------
//	CHIBI ENGINE v0.1
//  copyright Stijn Doyen
//---------------------------------------------------
//	SceneManager.h
//---------------------------------------------------
#pragma once
#include "Manager.h"

#include "MainData.h"
#include <map>

using namespace std;

class Scene;

//!The manager that stores and handles all scenes
class SceneManager final : public Manager
{
public:
	SceneManager(void);
	~SceneManager(void);

	//!Initialize the scene with given name
	void Initialize(const tstring& name);

	//!Initialize the active scene
	void Initialize();

	//!update the active scene
	void Update();

	//!Paint the active scene
	void Paint();

	//!Adds a scene to the manager
	/*!This will call the LoadContent and initialize of that scene*/
	bool AddScene(const tstring& name, Scene* scenePtr);

	//!Change the scene
	void SetActiveScene(const tstring& name);

	//!Get a pointer the active scene
	Scene* GetActiveScene();
private:
	//!A container that stores all the scenes
	map<tstring, Scene*> m_GameScenes;
	//!The tag of the active scene
	tstring m_ActiveScene;

private:
	SceneManager(SceneManager& t);
	SceneManager& operator=(SceneManager& t);
};