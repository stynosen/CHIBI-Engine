#pragma once
#include <functional>
#include "Engine/ChibiEngine.h"
#include "Engine/BoostLink.h"
#include "Managers/CollisionManager.h"
#include "MainData.h"

class GameObject;
class CollisionManager;

typedef std::function<void(GameObject*,const tstring& tag)> CollisionAction;
#ifndef DefaultCollisionAction
	#define DefaultCollisionAction [](GameObject* objectPtr,const tstring& tag)->void{}
#endif

//!A region that is used by the CollisionManager to detect collision between GameObjects
class HitRegion final
{
public:
	//!Returns the tag of the HitRegion
	const tstring& GetTag()const;

	//!Adds a tag to the tag list
	void AddCheckTag(const tstring& tag);
	
	//!Removes a tag from the tag list
	/*!Returns if tag was found*/
	bool RemoveCheckTag(const tstring& tag);

	//!Check for every tag except for the tags in the list
	void IgnoreCheckTags();
	//!Only check for collisions with HitRegion that have a tag that's in the tag list
	void OnlyCheckTags();

	//!Is the tag in my white-list?
	bool CheckForTag(const tstring& tag)const;

	//!Check if the HitRegion collides with another one
	/*!Is there collisions with the other HitRegion?
	Tag is ignored*/
	bool HitTest(HitRegion* otherRegionPtr)const;

	//!Check if the HitRegion collides with another one
	/*!Is there collisions with the other HitRegion?
	Tag is ignored
	Will hive the overlapping polygon as a output parameter.*/
	bool HitTest(HitRegion* otherRegionPtr, ShapeMath::Shape& outOverlapPolygonRef)const;
	//!Calculate the bounding box of the overlapping polygon
	Rect CalculateIntersectionWith(HitRegion* otherRegionPtr)const;

	//!Is the HitRegion a rectangle? Used for optimizations
	bool IsRect()const;
	//!Get the bounding box of the HitRegion
	const Rect& GetOutline()const;
	//!Get the polygon of the HitRegion
	const ShapeMath::ShapeCollection& GetSurface();

	//!Get the GameObject that owns this HitRegion
	GameObject* GetParent();

	//!Move the HitRegion over a distance
	void Translate(const Vector2& translation);

	//!Set the lambda or functor that has to be executed if there is collision with a HitRegion
	void SetListener(CollisionAction listener);

	//!This will call the listener lambda and pass the GameObject and tag of the colliding entity as parameters
	void Action(GameObject* objectPtr, const tstring& tag);

	//!Check for collision with all HitRegions in the CollisionManager
	/*!Will keep the check-tag list in mind*/
	void HandleCollision();

	//!Cast a ray on this HitRegion
	bool Raycast(Ray& ray);

private:
	friend CollisionManager;
	HitRegion(GameObject* parentPtr, Vector2* firstPoint, int nrOfPoints, const tstring& tag);
	friend CollisionManager;
	HitRegion(GameObject* parentPtr, const Rect& hitRect, const tstring& tag);
	friend CollisionManager;
	HitRegion(GameObject* parentPtr, const ShapeMath::Shape& shape, const tstring& tag);
	friend CollisionManager;
	HitRegion(GameObject* parentPtr, const ShapeMath::ShapeCollection& shape, const tstring& tag);
	friend CollisionManager;
	~HitRegion();

	//!Initialize the HitRegion
	/*!This will be called by the CollisionManager*/
	friend CollisionManager;
	void Initialize();



	//The pointer of the manager that contains and manages this HitRegion
	CollisionManager*				m_CollisionManagerPtr;
	//The pointer to the object that contains this HitRegion
	GameObject*						m_ParentObjectPtr;
	//The tag of this HitRegion
	tstring							m_Tag;

	//A vector of the points that make up the collision polygon
	vector<Vector2>					m_Points;
	//The actual polygon that will be used to calculate intersection
	ShapeMath::ShapeCollection		m_Surface;

	//The tags that will be ignored of checked
	vector<tstring>					m_CheckTags;
	//false will result in ignoring the check tags
	bool							m_OnlyCheckTags;

	//For optimization goals, we keep a IsRect boolean, so box-box collisions can be speed up
	bool							m_IsRect;
	//The bounding box of the polygon
	Rect							m_OutlineRect;

	//The hit action that should be fired when collision is detected
	CollisionAction					m_Listener;

private:
	HitRegion(HitRegion& t);
	HitRegion& operator=(HitRegion& t);
};