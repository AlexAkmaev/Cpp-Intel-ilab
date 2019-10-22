#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <iterator>
#include <algorithm>
using namespace std;

template <typename T>
struct Point { 
    T x = 0, y = 0, z = 0;
    Point<T>() = default;
    Point<T> (const T& A, const T& B, const T& C) : x(A), y(B), z(C) {}
};

template <typename T>
struct Vector {
	T x = 0, y = 0, z = 0;
    Vector() = default;
	Vector(const Point<T>& A, const Point<T>& B) : 
        x (A.x - B.x), y (A.y - B.y), z (A.z - B.z) {}
    Vector(const T& x_, const T& y_, const T& z_) : 
        x (x_), y (y_), z (z_) {}
    T length() const;  //module of the vector
};

template <typename T>
struct Triangle {
	Point<T> pts[3];
	Triangle(const Point<T>& A, const Point<T>& B, const Point<T>& C) : pts {A, B, C} {}
	
	T square() const;   //calculates the square of Triangle
	
	bool is_inside(const Point<T>& P) const;  //is P inside Trinagle?
	
	bool is_cross(const Triangle<T>& rhs) const;  //does it intersect with a triangle rhs?
	
	bool is_intersect(const Triangle<T>& rhs) const;   //does both triangles intersect?
};

template <typename T>
struct Line {
	Point<T> fst, sec;
	Line() = default;
	Line(Point<T> A, Point<T> B) : fst(A), sec(B) {}
	
	bool is_inter(const Line<T>& L) const;  //are ends of L2 from different side of L1?
	
	bool is_crossing(const Line<T>& L) const;  //do lines intersect?
	
	bool cross_on_plane(const Triangle<T> &t) const;  //does the line intersect a triangle?
};

template <typename T>
struct Plane {
	Vector<T> n;
	Plane(const Vector<T>& v) : n(v / v.length()) {}
};

template <typename T>
bool operator==(const Point<T>& A, const Point<T>& B);  //comparison operator for Points

template <typename T>
istream& operator>>(istream& stream, Point<T>& P);  //input operator

ostream& operator<<(ostream& stream, const vector<int>& v);  //output operator

template <typename T>
Vector<T> operator+(const Vector<T>& a, const Vector<T>& b);  //operator is vector addition

template <typename T>
T operator*(const Vector<T>& a, const Vector<T>& b);  //scalar product

template <typename T>
Vector<T> operator*(const Vector<T>& a, const T& k);  //operator of multiplication of a vector by a number

template <typename T>
Vector<T> operator/(const Vector<T>& a, const T& k);  //operator of division of a vector by a number

template <typename T>
Vector<T> axb(const Vector<T>& a, const Vector<T>& b);  //vector product

template <typename T>
bool operator!=(const Triangle<T>& t1, const Triangle<T>& t2);  //comparison operator for Trinagles

template <typename T>
map<int, vector<int>> intersecting_triangles(const vector<Triangle<T>>& trgs);  //finds pairs of intersecting triangles
