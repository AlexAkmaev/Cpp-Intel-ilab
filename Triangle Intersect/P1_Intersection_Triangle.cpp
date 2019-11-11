#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <set>
#include <iterator>
#include <algorithm>
#include "P1_Triangle.h"
using namespace std;

template <typename T>
T Triangle<T>::square() const {
	T sq = pts[0].x * (pts[1].y - pts[2].y) +
	       pts[1].x * (pts[2].y - pts[0].y) +
	       pts[2].x * (pts[0].y - pts[1].y);
	return abs(sq) / 2.0;
}

template <typename T>
void Polygon<T>::make_clockwise() {
	int cap = Polygon<T>::pts.size() - 1;
	bool run = cap < 3 ? false : true;
	while (run) {
		if (!is_crossing(Line<T>{pts[0], pts[2]}, Line<T>{pts[3], pts[1]})) {
			for(int i = 1; i < 4; i += 2) {
				if (is_crossing(Line<T>{pts[0], pts[2]}, Line<T>{pts[1], pts[3]}))
		            continue;
		        else
		        	swap(pts[2], pts[i]);
			}
		}

		if (cap > 3 && !is_crossing(Line<T>{pts[0], pts[3]}, Line<T>{pts[2], pts[4]})) {
			if (is_crossing(Line<T>{pts[3], pts[4]}, Line<T>{pts[1], pts[0]}))
			    reverse(begin(pts) + 1, end(pts) - 1);
			else
				swap(pts[3], pts[4]);
			continue;
		}

		if (cap > 4 && !is_crossing(Line<T>{pts[0], pts[4]}, Line<T>{pts[5], pts[3]})) {
			if (!is_crossing(Line<T>{pts[5], pts[0]}, Line<T>{pts[1], pts[4]}))
			    reverse(begin(pts) + 1, end(pts) - 1);
			else
				swap(pts[5], pts[4]);
			continue;
		}
		break;
	}
}

template <typename T>
T Polygon<T>::square() const {
	T total_square;
    switch(pts.size()) {
	    case (3): {
	    	Triangle<T> t;
	    	for (int i = 0; i < 3; i++)
	            t.pts[i] = pts[i];
	        total_square = t.square();
	    	break;
	    }
	    case (4): {
	    	Triangle<T> t1, t2;
	    	for (int i = 0; i < 3; i++) {
	            t1.pts[i] = pts[i];
	            t2.pts[i] = pts[(i + 2) % 4];
	        }
	        total_square = t1.square() + t2.square();
	        break;
	    }
	    case (5): {
	    	Triangle<T> t1, t2, t3;
	    	for (int i = 0; i < 3; i++) {
	            t1.pts[i] = pts[i];
	            t2.pts[i] = pts[(i + 2) % 4];
	            t3.pts[i] = pts[(i + 3) % 5];
	        }
	        total_square = t1.square() + t2.square() + t3.square();
	        break;
	    }
	    case (6): {
	    	Triangle<T> t1, t2, t3, t4;
	    	for (int i = 0; i < 3; i++) {
	            t1.pts[i] = pts[i];
	            t2.pts[i] = pts[(i + 2) % 4];
	            t3.pts[i] = pts[(i + 3) % 5];
	            t4.pts[i] = pts[(i + 4) % 6];
	        }
	        total_square = t1.square() + t2.square() + t3.square() + t4.square();
	        break;
	    }
	    default:
	    	total_square = 0.0;
	    	break;
	}
	return total_square;
}

template <typename T>
bool operator==(const Point<T>& A, const Point<T>& B) {
	return ((A.x == B.x) && (A.y == B.y));
}

template <typename T>
bool operator<(const Point<T>& A, const Point<T>& B) {
	if(A.x != B.x)
        return A.x < B.x;
    else
        return A.y < B.y;
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
bool is_inter(const Line<T>& L1, const Line<T>& L2) {   // are from different sides?
	Vector<T> left(L2.fst, L1.sec), right(L2.sec, L1.sec), mid(L1.fst, L1.sec);
	Vector<T> ans1 = axb(mid, left), ans2 = axb(mid, right);
	if (ans1.z*ans2.z < 0)
        return true;
    return false;
}

template <typename T>
bool is_crossing(const Line<T>& L1, const Line<T>& L2) {
	return is_inter(L1, L2) && is_inter(L2, L1);
}

template <typename T>
vector<Point<T>> Triangle<T>::cross(const Triangle<T> &t) const{
	vector<Point<T>> ans;
	for (int i = 0; i < 3; i++) {
		Line<T> L1{pts[i], pts[(i + 1) % 3]};
		for (int j = 0; j < 3; j++) {
			Line<T> L2{t.pts[j], t.pts[(j + 1) % 3]};
			if (is_crossing(L1, L2)) {    //peresecautcya
				Vector<T> left(L2.fst, L1.sec), right(L2.sec, L1.sec), mid(L1.fst, L1.sec);
				Vector<T> ans1 = axb(mid, left), ans2 = axb(mid, right);
				T z1 = abs(ans1.z), z2 = abs(ans2.z);   //squares
				Point<T> P;
				P.x = L2.fst.x + (L2.sec.x - L2.fst.x)*z1 / abs(z2 + z1);
				P.y = L2.fst.y + (L2.sec.y - L2.fst.y)*z1 / abs(z2 + z1);
			    ans.push_back(P);
			}
		}
	}
	return ans;
}

template <typename T>
bool Triangle<T>::is_inside(const Point<T>& P) const{   //is P inside t?
	Triangle t1(P, pts[0], pts[1]),
             t2(P, pts[1], pts[2]),
			 t3(P, pts[2], pts[0]);
    if (t1.square() + t2.square() + t3.square() == square())
        return true;
    return false;
}

template <typename T>
vector<Point<T>> Triangle<T>::find_tops(const Triangle<T>& rhs) const{
	vector<Point<T>> in_tops;
	for(int i = 0; i < 3; i++) {
       	if (rhs.is_inside(pts[i])) {
       		in_tops.push_back(pts[i]);
       	}
       	if (is_inside(rhs.pts[i])) {
       		in_tops.push_back(rhs.pts[i]);
	    }
    }
	return in_tops;
}

template <typename T>
T Triangle<T>::intersection_area(const Triangle<T>& rhs) const{
	vector<Point<T>> points = cross(rhs);   //points of intersection
	vector<Point<T>> tops = find_tops(rhs);
	set<Point<T>> all_points;
	for(const auto& i : points) {
		all_points.insert(i);
	}
	for(const auto& i : tops) {
		all_points.insert(i);
	}
	vector<Point<T>> res;
	for (typename set<Point<T>>::iterator it = all_points.begin(); it != all_points.end(); it++)
        res.push_back(*it);
	Polygon<T> pol;
	pol.pts = res;
	pol.make_clockwise();
	return pol.square();
}

int main() {
	Triangle<double> t1, t2;
	for(int i = 0; i < 3; i++) {
		cin >> t1.pts[i].x >> t1.pts[i].y;
	}

	for(int i = 0; i < 3; i++) {
		cin >> t2.pts[i].x >> t2.pts[i].y;
	}

	cout << t1.intersection_area(t2);

	return 0;
}
