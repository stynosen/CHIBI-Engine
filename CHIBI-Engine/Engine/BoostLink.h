//Functions to implement the boost libraries and provide conversions
#pragma once
#include "MainData.h"
#include "ChibiEngine.h"
/*
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
using namespace boost::geometry;
typedef boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian> BoostPoint;
typedef boost::geometry::model::box<BoostPoint> BoostBox;
typedef boost::geometry::model::polygon<BoostPoint> BoostPolygon;

class BoostLink
{
public:
	
	static Vector2 BoostPointToVector2(const BoostPoint& point);
	static BoostPoint Vector2ToBoostPoint(const Vector2& point);
	static void AddPointToPolygon(BoostPolygon& polygonRef, const Vector2& vec);
	static bool Translate(BoostPolygon& polygonRef, const Vector2& translation);
	static Rect	GetBoundingRect(const BoostPolygon& polygon);
	static bool PolygonHitTest(const BoostPolygon& p1, const BoostPolygon& p2);
	static Rect Intersection(const BoostPolygon& p1, const BoostPolygon& p2);
	static bool Append(BoostPolygon& polygonRef, const BoostPolygon& app);

	//The int returns how much polygons there are now
	static int Merge(vector<BoostPolygon>& polygonsVecRef);
	
private:
	//Static class => block constructir, destructor, copy and = operator
	BoostLink();
	~BoostLink();
	BoostLink(BoostLink& t);
	BoostLink& operator=(BoostLink& t);
};
*/