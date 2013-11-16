#pragma once
#include "MainData.h"
#include "Engine/EngineMath.h"
#include <vector>
#include <list>
#include <map>

using namespace std;
class Scene;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	//This method initialises the GameObject.
	//Create and add children here
	virtual bool Initialise();

	//This method updates the GameObject
	//Add specific code that has to be executed every frame here
	//It will also update the world position, scale and rotatation of the object.
	virtual void Update();

	//This method paints the object and all of its children
	virtual void Paint();

	//Methods for the savegame manager
	//Not yet implemented
	virtual void SaveData();
	virtual void LoadData();

	void SetPosition(const Vector2& newPos);
	void SetScale(const Vector2& newScale);
	void SetRotation(double newRotation);

	const Vector2& GetPosition(bool world = true)const;
	const Vector2& GetTranslation()const;
	const Vector2& GetScale(bool world=true)const;
	const double& GetRotation(bool world=true)const;

	void Translate(const Vector2& pos);
	void Scale(const Vector2& scale);
	void Rotate(double rotation);

	//Called whenever the window is resized
	virtual void Resize(){};

	//Get the world matrix. This contains the position, scale and rotation of the object in worldspace
	const D3DXMATRIX& GetWorldMatrix() const;

	
	void AddChild(GameObject* gameObjectPtr);
	void RemoveChild(GameObject* gameObjectPtr, bool deleteObject = true);


	void SetParent(GameObject* gameObjectPtr);
	GameObject* GetParent()const;
	void RemoveParent();

	void SetScene(Scene* scenePtr);
	Scene* GetScene();

	void SetName(const tstring& name);
	const tstring& GetName()const;

	//Create a rectangle that can be used for collision detection
	void CreateBoundingRect(const Rect& boundRect);

	//Set the boundingrect for this object
	void SetBoundingRect(const Rect& boundRect);

	//Set the boundingrect for this object
	void SetBoundingRect(Rect* boundRectPtr);
	Rect GetBoundingRect()const;
	Rect* GetBoundingRectPtr();
	bool HasBoundingRect()const;

	//Change the drawing priority of the object. this manipulates the draw order.
	//Objects with highest priority will be drawn last (in front of the rest)
	void SetDrawingPriority(int drawPriority);
	int GetDrawingPriority(bool child = false) const;

	const bool IsInitialised()const;
protected:
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