#pragma once

#include <iostream>
#include <vector>
#include <set>
using namespace std;

template <typename T>
struct Point { 
    T x = 0, y = 0, z = 0;
    Point() = default;
    Point(const T& A, const T& B, const T& C) : x(A), y(B), z(C) {}
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
struct Line;

template <typename T>
struct Triangle {
	Point<T> pts[3];
	Triangle(const Point<T>& A, const Point<T>& B, const Point<T>& C) : pts {A, B, C} {}
	
	Line<T> max_side() const;  //max side of triangle
	
	T square() const;   //calculates the square of Triangle
	
	bool is_inside(const Point<T>& P) const;  //is P inside Trinagle?
	
	bool is_far(const Triangle<T>& rhs) const;  //is rhs far from triangle?
	
	bool is_cross(const Triangle<T>& rhs) const;  //does any of the sides of the triangle rhs intersect the triangle 'this'?
	
	bool is_intersect(const Triangle<T>& rhs) const;   //does triangle rhs intersect the triangle 'this'?
};

template <typename T>
struct Line {
	Point<T> fst, sec;
	Line() = default;
	Line(Point<T> A, Point<T> B) : fst(A), sec(B) {}
	
	T length() const;  //length of line
	
	bool is_inter(const Line<T>& L) const;  //are ends of L2 from different sides of L1?
	
	bool is_crossing(const Line<T>& L) const;  //do lines intersect?
	
	bool cross_on_plane(const Triangle<T> &t) const;  //does the line intersect a triangle?
};

template <typename T>
struct Plane {
	Vector<T> n;
	Plane(const Vector<T>& v) : n(v / v.length()) {}
};

template <typename T>
bool operator==(const Point<T>& A, const Point<T>& B) {  //comparison operator for Points
	return ((A.x == B.x) && (A.y == B.y));
}

template <typename T>
istream& operator>>(istream& stream, Point<T>& P) {  //input operator
	stream >> P.x >> P.y >> P.z;
	return stream;
}

template <typename T>
T Vector<T>::length() const {
	return sqrt(x*x + y*y + z*z);
}

template <typename T>
Vector<T> operator+(const Vector<T>& a, const Vector<T>& b) {  //operator is vector addition
	return Vector<T>{a.x + b.x, a.y + b.y, a.z + b.z};
}

template <typename T>
T operator*(const Vector<T>& a, const Vector<T>& b) {  //scalar product
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

template <typename T>
Vector<T> operator*(const Vector<T>& a, const T& k) {  //operator of multiplication of a vector by a number
	return Vector<T>{a.x*k, a.y*k, a.z*k};
}

template <typename T>
Vector<T> operator/(const Vector<T>& a, const T& k) {  //operator of division of a vector by a number
	return Vector<T>{a.x / k, a.y / k, a.z / k};
}

template <typename T>
Vector<T> axb(const Vector<T>& a, const Vector<T>& b) {  //vector product
	Vector<T> c;
	c.x = a.y*b.z - a.z*b.y;
	c.y = a.z*b.x - a.x*b.z;
	c.z = a.x*b.y - a.y*b.x;
	return c;
}

template <typename T>
T Line<T>::length() const{
	return sqrt((fst.x - sec.x)*(fst.x - sec.x) +
	            (fst.y - sec.y)*(fst.y - sec.y) +
                (fst.z - sec.z)*(fst.z - sec.z));
}

template <typename T>
bool operator!=(const Triangle<T>& t1, const Triangle<T>& t2) {  //comparison operator for Trinagles
	return (t1.pts != t2.pts);
}

template <typename T>
T Triangle<T>::square() const {
	Vector<T> AC(pts[0], pts[1]), AB(pts[0], pts[2]);
	T sq = axb(AC, AB).length();
	return abs(sq) / 2.0;
}

template <typename T>
bool Triangle<T>::is_inside(const Point<T>& P) const{   //is P inside t?
	Triangle t1(P, pts[0], pts[1]), 
             t2(P, pts[1], pts[2]),
			 t3(P, pts[2], pts[0]);
    if (t1.square() + t2.square() + t3.square() - square() <= 0.00000000001)
        return true;
    return false;
}

template <typename T>
bool Line<T>::is_inter(const Line<T>& L) const{   // are from different sides?
	Vector<T> left(L.fst, sec), right(L.sec, sec), mid(fst, sec);
	Vector<T> ans1 = axb(mid, left), ans2 = axb(mid, right);
	if (ans1*ans2 < 0)
        return true;
    return false;
}

template <typename T>
bool Triangle<T>::is_far(const Triangle<T>& rhs) const {  //compares the radii of the sphere in which the triangles are enclosed
	Line<T> R1 = max_side(), R2 = rhs.max_side();
	T RO = R1.length() + R2.length();
	return ((RO < Line<T>{R1.fst, R2.fst}.length()) ||
			(RO < Line<T>{R1.fst, R2.sec}.length()) ||
			(RO < Line<T>{R1.sec, R2.fst}.length()) ||
		    (RO < Line<T>{R1.sec, R2.sec}.length()));
}

template <typename T>
bool Triangle<T>::is_intersect(const Triangle<T>& rhs) const{
	return (is_cross(rhs) || rhs.is_cross(*this));
}

template <typename T>
bool Line<T>::is_crossing(const Line<T>& L) const{
	return is_inter(L) && L.is_inter(*this);
}

template <typename T>
bool Line<T>::cross_on_plane(const Triangle<T> &t) const{
	for (int j = 0; j < 3; j++) {
		Line<T> L{t.pts[j], t.pts[(j + 1) % 3]};
		if (is_crossing(L)) {    //peresecautcya
			return true;
		}
	}
	return false;
}

template <typename T>
Line<T> Triangle<T>::max_side() const{
	Line<T> L1{pts[0], pts[1]}, L2{pts[1], pts[2]}, L3{pts[2], pts[0]};
	return max({L1, L2, L3}, [](const Line<T>& Lhs, const Line<T>& Rhs) {
	                            return Lhs.length() < Rhs.length(); });
}

template <typename T>
bool Triangle<T>::is_cross(const Triangle<T>& rhs) const{
	bool irs = false;
	for (int i = 0; i < 3; i++) {
		Vector<T> CV{rhs.pts[(i + 1) % 3], rhs.pts[i]};
		Vector<T> CA{pts[0], rhs.pts[i]};
		Plane<T> pl{axb(Vector<T>{pts[0], pts[1]}, Vector<T>{pts[0], pts[2]})};
		if (CV*pl.n == 0) {
		    if (Line<T>{rhs.pts[(i + 1) % 3], rhs.pts[i]}.cross_on_plane(*this)){
				irs = true;
				break;
		    }
		    continue;
		}
		T K = abs((CA*pl.n) / (CV*pl.n));
		if (K > 1)
		    continue;
		    
		Vector<T> CM = CV*K, OC{rhs.pts[i], Point<T>{}};
		Vector<T> OM = OC + CM;
		if (is_inside(Point<T>{OM.x, OM.y, OM.z})) {
			irs = true;
			break;
		}
	}
	return irs;
}

template <typename T>
set<int> intersecting_triangles(const vector<Triangle<T>>& trgs);  //finds pairs of intersecting triangles
