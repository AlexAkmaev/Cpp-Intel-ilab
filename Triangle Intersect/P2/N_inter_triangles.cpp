#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <iterator>
#include "N_Triangles.hpp"
using namespace std;

template <typename T>
Vector<T> operator+(const Vector<T>& a, const Vector<T>& b) {
	return Vector<T>{a.x + b.x, a.y + b.y, a.z + b.z};
}

template <typename T>
Vector<T> axb(const Vector<T>& a, const Vector<T>& b) {
	Vector<T> c;
	c.x = a.y*b.z - a.z*b.y;
	c.y = a.z*b.x - a.x*b.z;
	c.z = a.x*b.y - a.y*b.x;
	return c;
}

template <typename T>
bool operator==(const Point<T>& A, const Point<T>& B) {
	return ((A.x == B.x) && (A.y == B.y));
}

template <typename T>
T operator*(const Vector<T>& a, const Vector<T>& b) {  //scalar
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

template <typename T>
Vector<T> operator*(const Vector<T>& a, const T& k) {
	return Vector<T>{a.x*k, a.y*k, a.z*k};
}

template <typename T>
Vector<T> operator/(const Vector<T>& a, const T& k) {
	return Vector<T>{a.x / k, a.y / k, a.z / k};
}

template <typename T>
T Vector<T>::length() const{
	return sqrt(x*x + y*y + z*z);
}

template <typename T>
bool operator!=(const Triangle<T>& t1, const Triangle<T>& t2) {
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
bool Triangle<T>::is_intersect(const Triangle<T>& rhs) const{
	return (is_cross(rhs) || rhs.is_cross(*this));
}

template <typename T>
map<int, vector<int>> intersecting_triangles(const vector<Triangle<T>>& trgs) {
	map<int, vector<int>> res;
	for (int i = 0; i < trgs.size(); i++) {
		for (int j = 0; j < trgs.size(); j++) {
		    if ((trgs[i] != trgs[j]) && (trgs[i].is_intersect(trgs[j])))
		        res[i].push_back(j);
	    }
	    if (res.count(i) == 0) 
	        res[i];
	}
	return res;
}

template <typename T>
istream& operator>>(istream& stream, Point<T>& P) {
	stream >> P.x >> P.y >> P.z;
	return stream;
}

ostream& operator<<(ostream& stream, const vector<int>& v) {
	for (int i = 0; i < v.size(); i++) {
	    if (i != 0) 
	        stream << ", ";
	    stream << v[i];
	}
	return stream;
}

int main() {
	vector<Triangle<double>> trgs;
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		Point<double> A, B, C;
		cin >> A >> B >> C;
		Triangle<double> t{A, B, C};
		trgs.push_back(t);
	}
	
	map<int, vector<int>> ans = intersecting_triangles(trgs);
	for (auto it = ans.begin(); it != ans.end(); it++) {
		if (it->second.size() == 0)
		    cout << it->first << " -> No intersections";
        else
			cout << it->first << " -> "  << it->second;
		cout << endl;
	}
	
	return 0;
}
