#pragma once
#include "MainData.h"
#include <vector>
#include "Externals/clipper/clipper.hpp"
using std::vector;
//**************************************
//
// Vector2
//
//**************************************
#ifdef Vector2
	#undef Vector2
#endif
//!A vector that contains 2 doubles
struct Vector2
{
	//CONSTRUCTORS
	Vector2();
	Vector2(double nx, double ny);
	Vector2(const D3DXVECTOR2& vec);
	Vector2& operator=(const Vector2& vec);
	//VECTOR2 + VECTOR2
	Vector2& operator +=(const Vector2& vec);
	Vector2 operator +(const Vector2& vec)const;
	//VECTOR2 + X
	Vector2& operator +=(double d);
	Vector2 operator +(double d)const;
	//VECTOR2 - VECTOR2
	Vector2& operator -=(const Vector2& vec);
	Vector2 operator -(const Vector2& vec)const;
	//VECTOR2 - X
	Vector2& operator -=(double d);
	Vector2 operator -(double d)const;
	//VECTOR2 / VECTOR2
	Vector2& operator /=(const Vector2& vec);
	Vector2 operator /(const Vector2& vec)const;
	//VECTOR2 / X
	Vector2& operator /=(double d);
	Vector2 operator /(double d)const;
	//VECTOR2 * VECTOR2
	Vector2& operator *=(const Vector2& vec);
	Vector2 operator *(const Vector2& vec)const;
	//VECTOR2 * X
	Vector2& operator *=(double d);
	Vector2 operator *(double d)const;
	//VECTOR2 % X
	Vector2& operator %=(int d);
	Vector2 operator %(int d)const;

	Vector2 operator-()const;

	bool operator ==(const Vector2& vec)const;
	double Dot(const Vector2& vec)const;
	double Cross(const Vector2& vec)const;
	double Length()const;
	//!Normalizes the vector
	Vector2 Normalize();
	//Convert to D3DXVECTOR2
	D3DXVECTOR2 DX()const;

	double x;
	double y;
};

//**************************************
//
// Rect
//
//**************************************
#ifdef Rect
	#undef Rect
#endif
//!A rectangle struct
/*!Contains methods for fast intersections and hit test*/
struct Rect
{
	Rect();
	Rect(double x, double y, double width, double height);
	Rect(const Vector2& pos, const Vector2& size);
	Rect(const Rect& rect);
	Rect& operator=(const Rect&  rect);
	bool operator==(const Rect&  rect)const;
	void SetPosition(const Vector2& pos);
	void SetSize(const Vector2& size);
	void Translate(const Vector2& deltaPos);
	bool Contains(const Vector2& pos)const;
	Vector2 GetPosition()const;
	Vector2 GetSize()const;
	bool HitTest(const Rect& r2)const;
	const Rect GetCollision(const Rect& r2)const;
	bool ContainsPoint(const Vector2& pt)const;
	bool ContainsRect(const Rect& r2)const;

	double top;
	double bottom;
	double left;
	double right;
};


//**************************************
//
// Extensions for the clipper library
//
//**************************************

ClipperLib::IntPoint& operator += (ClipperLib::IntPoint& p1, const ClipperLib::IntPoint& p2);
ClipperLib::IntPoint operator + (const ClipperLib::IntPoint& p1, const  ClipperLib::IntPoint& p2);

//**************************************
//
// Shape math methods
//
//**************************************


using namespace ClipperLib;

//!Static class for collision and hit detections
/*!This is a wrapper around the ClipperLib shape library*/
class ShapeMath
{
public:
	//!A point of a collision shape
	typedef IntPoint	Point; 
	//!A shape that can be used for collisions
	typedef Path		Shape;
	//!A collection of shapes that can be used for collision
	typedef Paths		ShapeCollection;
	//!A collisions shape bounding box
	typedef IntRect		ShapeBox;

	//!This is the floating point precision
	static const int PRECISSION = 100000;

	//!Append a point to a shape
	static void AddPointToPolygon(Shape& polygonRef, const Vector2& vec);

	//!Move a shape with a certain offset
	static void Translate(Shape& polygonRef, const Vector2& translation);
	//!Move a shape with a certain offset
	static void Translate(ShapeCollection& polygonCollectionRef, const Vector2& translation);

	//!Get the bounding box of a shape as a Rect
	static Rect	GetBoundingRect(const Shape& polygon);
	//!Get the bounding box of a shape collection as a Rect
	static Rect	GetBoundingRect(const ShapeCollection& polygonCollection);

	//!Check if 2 shapes intersect
	static bool PolygonHitTest(const Shape& p1, const Shape& p2);
	//!Check if 2 shapes intersect
	static bool PolygonHitTest(const ShapeCollection& p1, const ShapeCollection& p2);
	//!Check if 2 shapes intersect
	static bool PolygonHitTest(const ShapeCollection& p1, const Shape& p2);
	//!Check if 2 shapes intersect
	static bool PolygonHitTest(const Shape& p1, const ShapeCollection& p2);

	//!Calculate the intersection box in between 2 shapes
	static Rect Intersection(const Shape& p1, const Shape& p2);
	//!Calculate the intersection box in between 2 shapes
	static Rect Intersection(const ShapeCollection& p1, const ShapeCollection& p2);
	//!Calculate the intersection box in between 2 shapes
	static Rect Intersection(const ShapeCollection& p1, const Shape& p2);
	//!Calculate the intersection box in between 2 shapes
	static Rect Intersection(const Shape& p1, const ShapeCollection& p2);

	//!Transform the shape into a vector of Vector2 points
	static std::vector<Vector2>			GetPointList(const Shape& polygon);
	//!Transform the shape collection into a vector (shape) of vectors (points) of Vector2 points
	static std::vector<vector<Vector2>>	GetPointList(const ShapeCollection& polygonCollection);

	//!Returns the amount of points in a shape
	static UINT NrOfPoints(const Shape& polygon);
	//!Returns the amount of points in a shape collection
	static UINT NrOfPoints(const ShapeCollection& polygonCollection);

	//!Appends shape b to shape a
	static bool Append(Shape& polygonRef, const Shape& app);
	//!Appends shape collection b to shape collection a
	static bool Append(Shape& polygonRef, const ShapeCollection& app);

	//!Merge a collection of shapes to become the most optimized shape
	/*!The int returns how much polygons there are now*/
	static int Merge(ShapeCollection& polygonCollectionRef);

	//!Check if 2 lines intersect
	/*!The hit point can be retrieved by checking the outHitPoint parameter*/
	static bool DoLinesIntersect(const Vector2& ua, const Vector2& ub, const Vector2& va, const Vector2& vb, Vector2& outHitPoint);

	//!Convert a shape point into a normal Vector2 point
	static Vector2 ShapePointToVector2(const Point& point);
	//!Convert a normal Vector2 point into a shape point 
	static Point Vector2ToShapePoint(const Vector2& point);
	//!Convert a shape box into a normal Rect box
	static Rect ShapeBoxToRect(const ShapeBox& box);

private:
	
	//Static class => block constructor, destructor, copy and = operator
	ShapeMath();
	~ShapeMath();

	ShapeMath(ShapeMath& t);
	ShapeMath& operator=(ShapeMath& t);
};


//**************************************
//
// String left shift operators for tstring conversions
//
//**************************************


std::tstringstream&	operator <<(std::tstringstream& os, const D3DXMATRIX& mat);

std::tstringstream&	operator <<(std::tstringstream& os, const D3DXVECTOR2& vec);

std::tstringstream&	operator <<(std::tstringstream& os, const Vector2& vec);

std::tstringstream&	operator <<(std::tstringstream& os, const Rect& rect);

std::tstring		operator <<(const std::tstring& os, const  std::tstring& as);