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

class ShapeMath
{
public:
	typedef IntPoint	Point;
	typedef Path		Shape;
	typedef Paths		ShapeCollection;
	typedef IntRect		ShapeBox;

	//This is the floating point precission
	static const int PRECISSION = 100000;

	static void AddPointToPolygon(Shape& polygonRef, const Vector2& vec);

	static void Translate(Shape& polygonRef, const Vector2& translation);
	static void Translate(ShapeCollection& polygonCollectionRef, const Vector2& translation);

	static Rect	GetBoundingRect(const Shape& polygon);
	static Rect	GetBoundingRect(const ShapeCollection& polygonCollection);

	static bool PolygonHitTest(const Shape& p1, const Shape& p2);
	static bool PolygonHitTest(const ShapeCollection& p1, const ShapeCollection& p2);
	static bool PolygonHitTest(const ShapeCollection& p1, const Shape& p2);
	static bool PolygonHitTest(const Shape& p1, const ShapeCollection& p2);

	static Rect Intersection(const Shape& p1, const Shape& p2);
	static Rect Intersection(const ShapeCollection& p1, const ShapeCollection& p2);
	static Rect Intersection(const ShapeCollection& p1, const Shape& p2);
	static Rect Intersection(const Shape& p1, const ShapeCollection& p2);

	static std::vector<Vector2>			GetPointList(const Shape& polygon);
	static std::vector<vector<Vector2>>	GetPointList(const ShapeCollection& polygonCollection);

	static UINT NrOfPoints(const Shape& polygon);
	static UINT NrOfPoints(const ShapeCollection& polygonCollection);

	static bool Append(Shape& polygonRef, const Shape& app);
	static bool Append(Shape& polygonRef, const ShapeCollection& app);

	//The int returns how much polygons there are now
	static int Merge(ShapeCollection& polygonCollectionRef);
	static bool DoLinesIntersect(const Vector2& ua, const Vector2& ub, const Vector2& va, const Vector2& vb, Vector2& outHitPoint);

	static Vector2 ShapePointToVector2(const Point& point);
	static Point Vector2ToShapePoint(const Vector2& point);
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
// String leftshift operators for tstring conversions
//
//**************************************


std::tstringstream&	operator <<(std::tstringstream& os, const D3DXMATRIX& mat);

std::tstringstream&	operator <<(std::tstringstream& os, const D3DXVECTOR2& vec);

std::tstringstream&	operator <<(std::tstringstream& os, const Vector2& vec);

std::tstringstream&	operator <<(std::tstringstream& os, const Rect& rect);

std::tstring&		operator <<(std::tstring& os, std::tstring& as);