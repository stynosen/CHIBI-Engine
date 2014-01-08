#pragma once
#include "MainData.h"
#include "Engine/EngineMath.h"
//#include "Managers/SaveGameManager.h"
#include <vector>
#include <list>
#include <map>

using namespace std;
class Scene;

//!The base GameObject class
/*!This class is the backbone of every object in the game.
All actors, rectangles, levels, tiles, ... are based on this class*/
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	//!Initialization of the GameObject, and all of it's children
	virtual bool Initialize();
	//!Update the GameObject, and all of its children
	/*!This method will update the world position, scale and rotation based on their locals.
	This method also takes care of the removal or adding of the children*/
	virtual void Update();

	//!Paint the GameObject, and all of its children
	virtual void Paint();

	//!Serialize (save) the data of the GameObject
	/*!All data that should be serialized, must be added in the overloaded method*/
	virtual void SaveData();

	//!De-serialize (load) the data of the GameObject
	/*!All data that should be loaded, must be added in the overloaded method*/
	virtual void LoadData();

	//!Sets the local position of the GameObject
	void SetPosition(const Vector2& newPos);

	//!Sets the local scale of the GameObject
	void SetScale(const Vector2& newScale);

	//!Sets the local rotation of the GameObject
	void SetRotation(double newRotation);

	//!Get the current position of the GameObject
	/*!world = true will give you the position in world-space.
	world = false will give you the position in local-space*/
	const Vector2& GetPosition(bool world = true)const;

	//!Get the last movement of the GameObject
	const Vector2& GetTranslation()const;

	//!Get the current scale of the GameObject
	/*!world = true will give you the scale in world-space.
	world = false will give you the scale in local-space*/
	const Vector2& GetScale(bool world = true)const;

	//!Get the current rotation of the GameObject
	/*!world = true will give you the rotation in world-space.
	world = false will give you the rotation in local-space*/
	const double& GetRotation(bool world=true)const;

	//!Move the GameObject over a given distance
	void Translate(const Vector2& pos);

	//!Scale the GameObject
	/*!Note that the scale method will multiply the current scale with given scale.
	To change the scale to a given scale, use the SetScale method instead*/
	void Scale(const Vector2& scale);

	//!Rotate the GameObject
	/*!Note that the Rotate method will add the given angle to the current angle.
	To change the angle to a given angle, use the SetRotation method instead*/
	void Rotate(double rotation);

	//!Called whenever the window is resized
	/*!This will be called by the Scene that contains the GameObject, or by the parent
	You should not call this method manually, as it won't change anything unless the window is actually resized*/
	virtual void Resize(){};

	//!Get the world matrix of the object
	/*!This matrix is used by a lot of effects, to make sure the object is drawn on the correct position on the screen*/
	const D3DXMATRIX& GetWorldMatrix() const;

	//!Add a GameObject as a child to this one
	/*!Children will be updated and painted automatically after the parent has been updated or painted*/
	void AddChild(GameObject* gameObjectPtr);

	//!Remove a child from this GameObject
	/*!Make sure you either delete the object (by setting the deleteObject boolean to true).
	or add it to another GameObject.
	or add it directly to the scene*/
	void RemoveChild(GameObject* gameObjectPtr, bool deleteObject = true);

	//!Set the gameObject as the parent of this one
	/*!Please note that this GameObject will not be added as a child!
	It can, however, be used to create structures where you want to inherit the transformation of another GameObject,
	but don't want it to be drawn or updated directly after the parent.
	To add a GameObject as a child, call the AddChild method instead*/
	void SetParent(GameObject* gameObjectPtr);
	
	//!Get the parent object
	GameObject* GetParent()const;

	//!Remove the parentObject
	/*!Please note that this GameObject will not be removed as a child!
	this method can, however, be used to create structures where you want a GameObject to be drawn or updated after another,
	but don't want it to inherit its transformation.
	To remove a GameObject as a child, call the RemoveChild method instead*/
	void RemoveParent();

	//!Add the GameObject to a scene
	void SetScene(Scene* scenePtr);

	//!Get the pointer to the scene that contains the GameObject
	Scene* GetScene();

	//!Sets the name of the GameObject
	/*!A GameObject doesn't require a name, but it can be used to find a object in the scene.
	You an do this by calling the GetGameobjectByName method of the Scene*/
	void SetName(const tstring& name);

	//!Get the name of GameObject
	const tstring& GetName()const;

	//!Create a bounding rectangle for a GameObject
	/*!The bounding rect must be defined in local-space, with the pivot point as the center*/
	void CreateBoundingRect(const Rect& boundRect);

	//!Sets the bounding rectangle to another rectangle
	/*!Make sure the GameObject has a bounding rect before calling this.
	To create a bounding rectangle instead, call the CreateBoundingRect method*/
	void SetBoundingRect(const Rect& boundRect);

	//!Get the bounding rectangle of this GameObject
	Rect GetBoundingRect()const;

	//!Checks whether this GameObject has a bounding rect
	bool HasBoundingRect()const;

	//!Set the draw priority of the GameObject
	/*!The lowest priority will be drawn first (behind everything else)*/
	void SetDrawingPriority(int drawPriority);

	//!Retrieves the drawing priority of the GameObject
	int GetDrawingPriority(bool child = false) const;

	//!Check whether or not the GameObject has been initialized
	const bool IsInitialized()const;
protected:
	//!Remove all children of a GameObject
	/*!Please make sure to re-add them to another GameObject or to a scene to prevent memory leaks!*/
	void RemoveAllChilds();

private:

	void					RemoveChildren();
	Rect*					m_BoundingRectPtr;

	Vector2					m_LocalPosition;
	Vector2					m_Translation;
	Vector2					m_LocalScale;

	double					m_LocalRotation;
	Vector2					m_WorldPosition;

	Vector2					m_WorldScale;
	double					m_WorldRotation;

	D3DXMATRIX				m_MatWorld;

	int						m_DrawPriority;

	bool					m_Initialised;

	tstring					m_Name;

	GameObject*				m_ParentPtr;
	Scene*					m_ScenePtr;

	list<GameObject*>		m_ChildPtrList;
	vector<GameObject*>		m_ChildsToAddVec;
	map<GameObject*,bool>	m_ChildsToRemoveVec;

private:
	GameObject(GameObject& t);
	GameObject& operator=(GameObject& t);
};