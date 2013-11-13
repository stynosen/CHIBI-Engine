#pragma once
#include "MainData.h"
#include "Components/StopWatch.h"
#include "Components/Input.h"
#include "Engine/Debug.h"
#include <vector>
#include <list>
#include <map>

using namespace std;

class Camera;
class GameObject;
class CollisionManager;

class Scene
{
public:
	Scene(void);
	virtual ~Scene(void);

	//Load content in this method
	//You can load content elsewhere but this will be called in the beginning of the game
	virtual void LoadContent() = 0;

	//Initialise the scene
	//This will be called by the scenemanager
	bool InitialiseScene();

	//Paint the scene
	//This will be called by the scenemanager
	void PaintScene();

	//Update the scene
	//This will be called by the scenemanager
	void UpdateScene();

	//This method is called when the screen has been resized
	void Resize();

	//Add a gameobject to the scene.
	//You can put it in the back or in the front (in case the draw/update order is important)
	void AddGameObjectToScene(GameObject* gameObject, bool front = false);

	//Remove a gameobject from the scene
	//Use the bool to controll whether the object is deleted from the memory or should be kept
	void RemoveGameObjectFromScene(GameObject* gameObject, bool deleteMe = true);

	//Serialize data
	//Not fully implemented yet, use at own risk
	void SaveData();

	//Is the object initialized?
	//Usefull for optimisations or validity checks
	bool IsInitialised()const;

	//Get the active camera
	Camera* GetActiveCamera();

	//Set the active camera
	//The old camera won't be stored! Make sure you either store it, or delete it
	Camera*	SetActiveCamera(Camera* newCam);

	//Get the collision manager of this scene
	//If there is none, it will be created at the first call
	CollisionManager* GetCollisionManager();

	//Add a gameobject to the scene with a name
	//This way the gameobject can be retrieved from the scene at any point
	void AddGameObjectByName(GameObject* gameObjectPtr, tstring& inOutName);

	//Get a gameobject from the scene that has been added with a name
	template <class T>
	T* GetGameobjectByName(const tstring& name)
	{
		if (m_GameObjectsByName.find(name) == m_GameObjectsByName.end())
		{
			Log(_T("Game object \"") + name + _T("\" can't be found in the scene\n Did you forgot to use the SetName() method?\nCheck the log for errors"), MESSAGE_LEVEL_ERROR);
			return nullptr;
		}

		GameObject* objectPtr = m_GameObjectsByName[name];
		if (objectPtr == nullptr)
			return nullptr;
		//Check if the object actualy is of the type
		T* dObjectPtr = DCAST<T*>(objectPtr);
		return dObjectPtr;
	}

protected:

private:
	//This method will do the actual deletion of the gameobjects (to prevent invalid iterator)
	void		RemoveGameobjects();

	//This lethod will do the actual adding of the new objects (to prevent invalid iterator)
	void		AddGameObjects();

	//Overload this method to write the scene initialisation
	//All gameobjects will be initialised automatically by the scene!
	virtual bool Initialise(){ return true; };

	//Overload this method to write the scene painting
	//All gameobjects will be painted automatically by the scene!
	virtual void Paint(){};

	//Overload this method to write the scene updating
	//All gameobjects will be updated automatically by the scene!
	virtual void Update(){};

	//Is the scene initialised
	bool						m_Initialised;

	//The pointer to the active camera
	Camera*						m_ActiveCamera;

	//A list with all the gameobjects in the scene
	//It's a list so you can swap objects and change positions 
	list<GameObject*>			m_GameObjects;

	//A map to store all the gameobjects that need to be added next update
	map<GameObject*, bool>		m_GameObjectsToAddVec;

	//A map to store all the gameobjects that need to be removed next update
	map<GameObject*, bool>		m_GameObjectsToRemoveVec;

	//A map to retrieve a gameobject by it's name
	map<tstring, GameObject*>	m_GameObjectsByName;

	//The adress of the collision manager of this scene
	//It is also possible that there is none (eg. for tools)
	CollisionManager*			m_CollisionManagerPtr;

private:
	Scene(Scene& t);
	Scene& operator=(Scene& t);
};