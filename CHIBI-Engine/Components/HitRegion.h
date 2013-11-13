#pragma once
#include <functional>
#include "Engine/ChibiEngine.h"
#include "Engine/BoostLink.h"
#include "Managers/CollisionManager.h"
#include "MainData.h"
class GameObject;

typedef std::function<void(GameObject*,const tstring& tag)> CollisionAction;
#ifndef DefaultCollisionAction
	#define DefaultCollisionAction [](GameObject* objectPtr,const tstring& tag)->void{}
#endif

class HitRegion final
{
public:
	HitRegion(GameObject* parentPtr, Vector2* firstPoint, int nrOfPoints, const tstring& tag);
	HitRegion(GameObject* parentPtr, const Rect& hitRect, const tstring& tag);
	HitRegion(GameObject* parentPtr, const ShapeMath::Shape& shape, const tstring& tag);
	HitRegion(GameObject* parentPtr, const ShapeMath::ShapeCollection& shape, const tstring& tag);
	~HitRegion();

	void Initialize();

	//Returns the tag of the hitregion
	const tstring& GetTag()const;

	//Adds a tag to the tag list
	void AddCheckTag(const tstring& tag);
	
	//Removes a tag from the tag list
	//Returns if tag was found
	bool RemoveCheckTag(const tstring& tag);

	//Check for every tag except for the tags in the list
	void IgnoreCheckTags();
	//Only check for collisions with hitregions that have a tag that's in the tag list
	void OnlyCheckTags();

	//Should I check this tag? (is it in my white-list)
	bool CheckForTag(const tstring& tag)const;

	//Is there collisions with the other hitregion?
	//Tag is ignored
	bool HitTest(HitRegion* otherRegionPtr)const;
	//Is there collisions with the other hitregion?
	//Tag is ignored
	//Will hive the overlapping polygon as a output parameter.
	bool HitTest(HitRegion* otherRegionPtr, ShapeMath::Shape& outOverlapPolygonRef)const;
	//Calculate the boundingbox of the overlapping polygon
	Rect CalculateIntersectionWith(HitRegion* otherRegionPtr)const;

	//Is the hitregion a rectangle? Used for optimisations
	bool IsRect()const;
	//Get the boundingbox of the hitregion
	const Rect& GetOutline()const;
	//Get the polygon of the hitregion
	const ShapeMath::ShapeCollection& GetSurface();

	//Get the gameobject that owns this hitregion
	GameObject* GetParent();

	//Move the hitregion over a distance
	void Translate(const Vector2& translation);

	//Set the lambda or functor that has to be executed if there is collision with a hitregion
	//Will keep the check-tag list in mind
	void SetListener(CollisionAction listener);

	//This will call the listener lambda and pass the gameobject and tag of the colliding entity as parameters
	void Action(GameObject* objectPtr, const tstring& tag);

	//Check for collision with all hitregions in the CollisionManager that should be checked for
	//Will keep the check-tag list in mind
	void HandleCollision();

	//Cast a ray on this hitregion
	bool Raycast(Ray& ray);

protected:
	//The pointer of the manager that contains and manages this hitregion
	CollisionManager*				m_CollisionManagerPtr;
	//The pointer to the object that contains this hitregion
	GameObject*						m_ParentObjectPtr;
	//The tag of this hitregion
	tstring							m_Tag;

	//A vector of the points that make up the collision polygon
	vector<Vector2>					m_Points;
	//The actual polygon that will be used to calculate intersection
	ShapeMath::ShapeCollection		m_Surface;

	//The tags that will be ignored of checked
	vector<tstring>					m_CheckTags;
	//false will result in ignoring the check tags
	bool							m_OnlyCheckTags;

	//For optimisation goals, we keep a IsRect bool, so box-box collisions van be speeded up
	bool							m_IsRect;
	//The boundingbox of the polygon
	Rect							m_OutlineRect;

	//The hitaction that should be fired when collision is deceted
	CollisionAction					m_Listener;

private:
	HitRegion(HitRegion& t);
	HitRegion& operator=(HitRegion& t);
};