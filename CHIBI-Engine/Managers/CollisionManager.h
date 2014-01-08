//---------------------------------------------------
//	CHIBI ENGINE v0.1
//  copyright Stijn Doyen
//---------------------------------------------------
//	CollisionManager.h
//---------------------------------------------------
#pragma once
#include "Manager.h"

#include "MainData.h"
#include <map>
#include <vector>
#include <algorithm>

#include "Engine/ChibiEngine.h"

using namespace std;

class GameObject;
class HitRegion;
class Scene;

//!A struct that contains data of a ray hit
struct RayResult
{
	RayResult()
	{
		hitPos = Vector2(0, 0);
		distance = INFINITE;
	}

	RayResult(const Vector2& pos, const double dist, HitRegion* hitObjectPtr)
	{
		hitPos = pos;
		distance = dist;
		hitRegionPtr = hitObjectPtr;
	}

	//!The position where the ray hit the object
	Vector2				hitPos;
	//!The distance from the start of the ray to the hit point
	double				distance;
	//!The address of the HitRegion that the ray hit
	HitRegion*			hitRegionPtr;
};

//!The struct that is used to cast rays
struct Ray
{
	Ray(
		//!The start position of the ray
		const Vector2& start 
		//!The direction of the ray
		, const Vector2& dir
		//!The length of the ray
		, const double& length = INFINITE
		//!Maximum amount of results
		, const int nrOfResults = 1
		//!Only hit tags
		, const bool onlyHitTags = false
	)
	{
		origin = start;
		direction = dir;
		distance = length;
		onlyTags = onlyHitTags;
		maxResults = nrOfResults;
		results.reserve(nrOfResults);
	}

	//!Add a tag to the ray
	void AddTag(const tstring& tag)
	{
		tags.push_back(tag);
	}

	//!Sorts the results by their distance
	void SortResultsByDistance()
	{
		//Sort results based on distance
		sort(results.begin(), results.end(), [](const RayResult & a, const RayResult & b) -> bool
		{
			return a.distance < b.distance;
		});
	}

	//!The start position of the ray
	Vector2				origin;
	//!The direction of the ray
	Vector2				direction;
	//!The distance of the ray
	double				distance;
	//!The maximum amount of results
	/*!The actual amount of results van be slightly higher*/
	UINT				maxResults;

	//!Only check or ignore all tags in the list
	/*!true  : Only search for the tags
	false : Ignore tags*/
	bool				onlyTags;
	//!All tags to consider
	vector<tstring>		tags;
	//!Results that have been found
	vector<RayResult>	results;
};

//!A buffer struct to build hit shapes by adding points
struct CollisionBuffer
{
	CollisionBuffer()
	{
		curShape = ShapeMath::Shape();
	}

	//!Advance to the next shape
	void NextPolygon()
	{
		shapes.push_back(curShape);
		curShape = ShapeMath::Shape();
	}

	//!Add a point to the current shape
	void AddPoint(const Vector2& point)
	{
		ShapeMath::AddPointToPolygon(curShape, point);
	}

	//!Returns the collection that contains every point and shape that have been added
	ShapeMath::ShapeCollection GetCollection()
	{
		ShapeMath::Merge(shapes);
		return shapes;
	}

	//!Currently present shapes
	vector<ShapeMath::Shape> shapes;
	//!Current shape
	ShapeMath::Shape curShape;
};

//!The manager that takes care of collision detection and handling
class CollisionManager final : public Manager
{
public:
	CollisionManager(Scene* scenePtr);
	~CollisionManager();

	//!Method for creating and adding a HitRegion
	HitRegion* CreateHitRegionForObject(GameObject* gameObjectPtr, Vector2* firstPoint, int nrOfPoints, const tstring& tag = _T("Default"));
	//!Method for creating and adding a HitRegion
	HitRegion* CreateHitRegionForObject(GameObject* gameObjectPtr, const ShapeMath::ShapeCollection& shape, const tstring& tag = _T("Default"));
	//!Method for creating and adding a HitRegion
	HitRegion* CreateHitRegionForObject(GameObject* gameObjectPtr, const ShapeMath::Shape& shape, const tstring& tag = _T("Default"));
	//!Method for creating and adding a HitRegion
	HitRegion* CreateHitRegionForObject(GameObject* gameObjectPtr, const Rect& hitRect, const tstring& tag = _T("Default"));
	//!Method for creating and adding a HitRegion for a GameObject
	/*!This method will use the BoundingRect of the GameObject*/
	HitRegion* CreateHitRegionForObject(GameObject* gameObjectPtr, const tstring& tag = _T("Default"));

	//!Method for retrieving a HitRegion for the given object
	HitRegion* GetHitregionByObject(GameObject* gameObjectPtr);
	//!Methods for retrieving a HitRegion for the object with given name
	/*!The object must be added to the scene with given name*/
	HitRegion* GetHitregionByName(const tstring& name);

	//!Check if a certain GameObject has a HitRegion
	bool HasHitRegionForObject(GameObject* gameObjectPtr);

	//!Remove the HitRegion of a GameObject
	void RemoveObject(GameObject* gameObjectPtr);

	//!Will cross check every HitRegion in the scene
	/*!This will keep the check tags in mind*/
	void HandleCollisions();

	//!This method tells the manager 2 HitRegions are colliding
	/*!Don't call this yourself unless you know what you are doing.*/
	void AddCollisionPair(GameObject* obj1Ptr, GameObject* obj2Ptr);

	//!Returns if there are HitRegions with given tag
	bool GetHitrectsWithTag(const tstring& tag, vector<HitRegion*>& hitRectVectorRef);

	//!Returns a vector with all tags present (by ref)
	const vector<tstring>& GetTags();

	//!Raycast methods
	bool Raycast(Ray& ray);

private:
	//!Method to add a HitRegion to the manager
	void	AddHitRegion(HitRegion* hitRegionPtr);
	//!Raycast on every HitRegion with given tag
	bool	RaycastOnTag(Ray& ray,const tstring& tag);

	//!Address of the scene that is managed by this manager
	Scene* m_ScenePtr;

	//!Map that stores the HitRegions, by it's parent objects address
	map<GameObject*, HitRegion*> m_HitRegionPtrMap;
	//!Map that stores the HitRegions, by it's tag
	map<tstring, vector<HitRegion*>> m_HitRegionsByTag;
	//!Vector that contains every tag that is currently present
	vector<tstring>	m_Tags;

	//!The pairs of the objects that have been colliding last frame
	multimap<GameObject*,GameObject*> m_CollisionPairs;

private:
	CollisionManager(CollisionManager& t);
	CollisionManager& operator=(CollisionManager& t);
};