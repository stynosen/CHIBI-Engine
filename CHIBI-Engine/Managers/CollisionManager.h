//---------------------------------------------------
//	CHIBI ENGINE v0.1
//  copyright Stijn Doyen
//---------------------------------------------------
//	CollisionManager.h
//---------------------------------------------------
#pragma once
#include "MainData.h"
#include <map>
#include <vector>
#include <algorithm>

#include "Engine/ChibiEngine.h"

using namespace std;

class GameObject;
class HitRegion;
class Scene;

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

	Vector2				hitPos;
	double				distance;
	HitRegion*			hitRegionPtr;
};

struct Ray
{
	Ray(const Vector2& start, const Vector2& dir, const double& length = INFINITE, const int nrOfResults = 1, const bool onlyHitTags = false)
	{
		origin = start;
		direction = dir;
		distance = length;
		onlyTags = onlyHitTags;
		maxResults = nrOfResults;
		results.reserve(nrOfResults);
	}

	void AddTag(const tstring& tag)
	{
		tags.push_back(tag);
	}

	void SortResultsByDistance()
	{
		//Sort results based on distance
		sort(results.begin(), results.end(), [](const RayResult & a, const RayResult & b) -> bool
		{
			return a.distance < b.distance;
		});
	}

	Vector2				origin;
	Vector2				direction;
	double				distance;
	UINT				maxResults;

	//true  : Only search for the tags
	//false : Ignore tags
	bool				onlyTags;
	vector<tstring>		tags;
	vector<RayResult>	results;
};

struct CollisionBuffer
{
	CollisionBuffer()
	{
		curShape = ShapeMath::Shape();
	}

	void NextPolygon()
	{
		shapes.push_back(curShape);
		curShape = ShapeMath::Shape();
	}

	void AddPoint(const Vector2& point)
	{
		ShapeMath::AddPointToPolygon(curShape, point);
	}

	ShapeMath::ShapeCollection GetCollection()
	{
		ShapeMath::Merge(shapes);
		return shapes;
	}

	vector<ShapeMath::Shape> shapes;
	ShapeMath::Shape curShape;
};

class CollisionManager final
{
public:
	CollisionManager(Scene* scenePtr);
	~CollisionManager();

	// Methods for adding a hitregion
	HitRegion* CreateHitRegionForObject(GameObject* gameObjectPtr, Vector2* firstPoint, int nrOfPoints, const tstring& tag = _T("Default"));
	HitRegion* CreateHitRegionForObject(GameObject* gameObjectPtr, const ShapeMath::ShapeCollection& shape, const tstring& tag = _T("Default"));
	HitRegion* CreateHitRegionForObject(GameObject* gameObjectPtr, const ShapeMath::Shape& shape, const tstring& tag = _T("Default"));
	HitRegion* CreateHitRegionForObject(GameObject* gameObjectPtr, const Rect& hitRect, const tstring& tag = _T("Default"));
	HitRegion* CreateHitRegionForObject(GameObject* gameObjectPtr, const tstring& tag = _T("Default"));

	// Methods for retrieving a hitregion
	HitRegion* GetHitregionByObject(GameObject* gameObjectPtr);
	HitRegion* GetHitregionByName(const tstring& name);

	//Check if a certain GameObject has a hitregion
	bool HasHitRegionForObject(GameObject* gameObjectPtr);

	//Remove the hitregion of a gameobject
	void RemoveObject(GameObject* gameObjectPtr);

	//Will cross check every hitregion in the scene
	//This will keep the checktags in mind
	void HandleCollisions();

	//This method tells the manager 2 gameobjects are colliding
	//Don't call this yourself unless you know what you are doing.
	void AddCollisionPair(GameObject* obj1Ptr, GameObject* obj2Ptr);

	//Returns if there are hitrects with given tag
	bool GetHitrectsWithTag(const tstring& tag, vector<HitRegion*>& hitRectVectorRef);

	//Returns a vector with all tags present (by ref)
	const vector<tstring>& GetTags();

	//Raycast methods
	bool Raycast(Ray& ray);

private:
	void	AddHitRegion(HitRegion* hitRegionPtr);
	bool	RaycastOnTag(Ray& ray,const tstring& tag);

	Scene* m_ScenePtr;
	map<GameObject*, HitRegion*> m_HitRegionPtrMap;
	map<tstring, vector<HitRegion*>> m_HitRegionsByTag;
	vector<tstring>	m_Tags;

	multimap<GameObject*,GameObject*> m_CollisionPairs;

private:
	CollisionManager(CollisionManager& t);
	CollisionManager& operator=(CollisionManager& t);
};