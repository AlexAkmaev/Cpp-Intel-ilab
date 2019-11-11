#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
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

    Vector<T>& operator+=(const Vector<T>& b);  //adds a vector to Vector

    Vector<T>& operator*=(const T& k);   //multiplies vectors by a number

    T length() const;  //module of the vector
};

template <typename T>
struct Line;

template <typename T>
struct Sphere;

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
struct Sphere {
	Point<T> centr;
	T R;
	Sphere(const Triangle<T>& t) : centr(Point<T>{(t.pts[0].x + t.pts[1].x + t.pts[2].x) / 3.0,
                       (t.pts[0].y + t.pts[1].y + t.pts[2].y) / 3.0,
					   (t.pts[0].z + t.pts[1].z + t.pts[2].z) / 3.0}),
		R(max({Line<T>{t.pts[0], centr}, Line<T>{t.pts[1], centr}, Line<T>{t.pts[2], centr}},
        [](const Line<T>& Lhs, const Line<T>& Rhs) {
            return Lhs.length_squared() < Rhs.length_squared(); }).length()) {}

	bool intersect(const Sphere<T>& rhs) const;   //if spheres intersect returns True
};


template <typename T>
struct Line {
	Point<T> fst, sec;
	Line() = default;
	Line(Point<T> A, Point<T> B) : fst(A), sec(B) {}

	T length() const;  //length of line

	T length_squared() const;  //length squared

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
	return ((A.x == B.x) && (A.y == B.y) && (A.z == B.z));
}

template <typename T>
bool operator<(const Point<T>& A, const Point<T>& B) {  //comparison operator for Points
    if (A.x != B.x)
	    return A.x < B.x;
    if (A.y != B.y)
	    return A.y < B.y;
    return A.z < B.z;
}

template <typename T>
struct comp_x{
	bool operator()(const pair<Point<T>, int>& p1, const pair<Point<T>, int>& p2) {
	    return p1.first.x < p2.first.x;
	}
};

template <typename T>
struct comp_y{
	bool operator()(const pair<Point<T>, int>& p1, const pair<Point<T>, int>& p2) {
	    return p1.first.y < p2.first.y;
	}
};

template <typename T>
struct comp_z{
	bool operator()(const pair<Point<T>, int>& p1, const pair<Point<T>, int>& p2) {
	    return p1.first.z < p2.first.z;
	}
};

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
Vector<T>& Vector<T>::operator+=(const Vector<T>& b) {  //operator is vector addition
    x += b.x; y += b.y; z += b.z;
	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator*=(const T& k) {  //operator of multiplication of a vector by a number
    x *= k; y *= k; z *= k;
	return *this;
}

template <typename T>
Vector<T> operator/(const Vector<T>& a, const T& k) {  //operator of division of a vector by a number
	return Vector<T>{a.x / k, a.y / k, a.z / k};
}

template <typename T>
T operator*(const Vector<T>& a, const Vector<T>& b) {  //scalar product
	return a.x*b.x + a.y*b.y + a.z*b.z;
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
T Line<T>::length_squared() const{
	return  (fst.x - sec.x)*(fst.x - sec.x) +
            (fst.y - sec.y)*(fst.y - sec.y) +
            (fst.z - sec.z)*(fst.z - sec.z);
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
    if (t1.square() + t2.square() + t3.square() - square() <= 0.000000000001)
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
bool Sphere<T>::intersect(const Sphere<T>& rhs) const {  //compares the radii of the sphere in which the triangles are enclosed
	T RO = R + rhs.R;
	return (RO*RO - Line<T>{centr, rhs.centr}.length_squared() >= 0.00000000001);
}

template <typename T>
bool Triangle<T>::is_far(const Triangle<T>& rhs) const {
	return !Sphere<T>{*this}.intersect(Sphere<T>{rhs});  //if Cubes don't intersect returns True
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
	for (int i = 0; i < 3; i++) {
		Vector<T> CV{rhs.pts[(i + 1) % 3], rhs.pts[i]};
		Vector<T> CA{pts[0], rhs.pts[i]};
		Plane<T> pl{axb(Vector<T>{pts[0], pts[1]}, Vector<T>{pts[0], pts[2]})};
		if (CV*pl.n == 0) {
		    if (Line<T>{rhs.pts[(i + 1) % 3], rhs.pts[i]}.cross_on_plane(*this)){
				return true;
		    }
		    continue;
		}
		T K = abs((CA*pl.n) / (CV*pl.n));
		if (K > 1)
		    continue;

		Vector<T> CM = CV *= K, OC{rhs.pts[i], Point<T>{}};
		Vector<T> OM = OC += CM;
		if (is_inside(Point<T>{OM.x, OM.y, OM.z})) {
			return true;
		}
	}
	return false;
}

template <typename T>
bool Triangle<T>::is_intersect(const Triangle<T>& rhs) const{
	return (is_cross(rhs) || rhs.is_cross(*this));
}


template <typename T, typename It, typename It_trgs>
void area_y(It x_beg, It x_end, T max_D, const It_trgs trgs_beg, set<int>& res) {  //the area sorted for y
    sort(x_beg, x_end, comp_y<T>());
	It y_beg = x_beg, y_end = x_beg, it_y = x_beg, it_y_end = x_end;
	int ky = 0;
	T dist_y = max_D;

	while (it_y != it_y_end) {
		sort(y_beg, y_end, comp_y<T>());
		if (ky == 0) {
			y_end = lower_bound(y_beg, it_y_end, pair<Point<T>, int>{Point<T>{100, dist_y + max_D, 100}, 0}, comp_y<T>());
			++ky;
		} else {
			y_beg = lower_bound(y_beg, it_y_end, pair<Point<T>, int>{Point<T>{100, dist_y - max_D, 100}, 0}, comp_y<T>());
			y_end = lower_bound(y_beg, it_y_end, pair<Point<T>, int>{Point<T>{100, dist_y + max_D, 100}, 0}, comp_y<T>());
		}

		sort(y_beg, y_end, comp_z<T>());
		search_area(y_beg, y_end, max_D, trgs_beg, res);

		it_y = y_end;
		dist_y += max_D;
	}
}

template <typename T, typename It, typename It_trgs>
void search_area(It y_beg, It y_end, T max_D, const It_trgs trgs_beg, set<int>& res) {  //the area that we search intersections in
	T dist_z = max_D;
    It z_beg = y_beg, z_end = y_beg, it_z = y_beg, it_z_end = y_end;
	int kz = 0;

	while (it_z != it_z_end) {
		if (kz == 0) {
			z_end = lower_bound(z_beg, it_z_end, pair<Point<T>, int>{Point<T>{100, 100, dist_z + max_D}, 0}, comp_z<T>());
			++kz;
		} else {
			z_beg = lower_bound(z_beg, it_z_end, pair<Point<T>, int>{Point<T>{100, 100, dist_z - max_D}, 0}, comp_z<T>());
			z_end = lower_bound(z_beg, it_z_end, pair<Point<T>, int>{Point<T>{100, 100, dist_z + max_D}, 0}, comp_z<T>());
		}

		for (it_z = z_beg; it_z != z_end; ++it_z) {
		    for (auto j_it = it_z + 1; j_it != z_end; ++j_it) {
		    	int i = it_z->second, j = j_it->second;
		    	if ((*(trgs_beg + i)).is_far(*(trgs_beg + j))) {
				    continue;
				}
			    if ((*(trgs_beg + i)).is_intersect(*(trgs_beg + j))) {
			        res.insert(i);
			        res.insert(j);
			    }
		    }
		}
		dist_z += max_D;
	}
}

template <typename T>
set<int> intersecting_triangles(const vector<Triangle<T>>& trgs);  //finds pairs of intersecting triangles
