#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

template <typename T>
struct Point { 
    T x = 0, y = 0, z = 0; 
};

template <typename T>
struct Vector {
	T x = 0, y = 0, z = 0;
    Vector() = default;
	Vector(const Point<T>& A, const Point<T>& B) : 
        x (A.x - B.x), y (A.y - B.y), z (A.z - B.z) {}
};

template <typename T>
struct Triangle {
	Point<T> A, B, C;
	Point<T> pts[3];
	Triangle() : pts {A, B, C} {}
	Triangle(const Point<T>& A, const Point<T>& B, const Point<T>& C) : pts {A, B, C} {}
	
	T square() const;   //calculates the square of Triangle
	
	vector<Point<T>> cross(const Triangle<T> &t) const;  //points that intersect the sides of the triangle t
	
	bool is_inside(const Point<T>& P) const;  //is P inside Trinagle?
	
	vector<Point<T>> find_tops(const Triangle<T>& rhs) const;  //finds tops inside both triangles
	
	T intersection_area(const Triangle<T>& rhs) const;   //calculates the intersection area with triangle rhs
};

template <typename T>
struct Polygon {
	vector<Point<T>> pts;
	void make_clockwise();  //number the tops clockwise in Polygon
	T square() const;   //calculates the square of Polygon
};

template <typename T>
struct Line {
	Point<T> fst, sec;
	Line() = default;
	Line(Point<T> A, Point<T> B) : fst(A), sec(B) {}
};

template <typename T>
bool operator==(const Point<T>& A, const Point<T>& B);

template <typename T>
bool operator<(const Point<T>& A, const Point<T>& B);

template <typename T>
Vector<T> axb(const Vector<T>& a, const Vector<T>& b);  //vector product

template <typename T>
bool is_inter(const Line<T>& L1, const Line<T>& L2);   // are ends of L2 from different side of L1?

template <typename T>
bool is_crossing(const Line<T>& L1, const Line<T>& L2);   //do lines intersect?
