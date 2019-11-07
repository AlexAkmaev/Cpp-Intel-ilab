#include <cmath>
#include <iterator>
#include <time.h>
#include "Geometry.hpp"
using namespace std;

template <typename T>
void search_area(const typename vector<pair<Point<T>, int>>::iterator& y_beg, const typename vector<pair<Point<T>, int>>::iterator& y_end,
                 T max_D, const vector<Triangle<T>>& trgs, set<int>& res) {
	auto z_beg = y_beg, z_end = y_beg, it_z = y_beg, it_z_end = y_end;
	int kz = 0;
	T dist_z = max_D;
	
	while (it_z != it_z_end) {
		if (kz == 0) {
			z_end = lower_bound(z_beg, it_z_end, pair<Point<T>, int>{Point<T>{100, 100, dist_z + max_D}, 0}, comp_z<T>());
			++kz;
		} else {
			z_beg = lower_bound(z_beg, it_z_end, pair<Point<T>, int>{Point<T>{100, 100, dist_z - max_D}, 0}, comp_z<T>());
			z_end = lower_bound(z_beg, it_z_end, pair<Point<T>, int>{Point<T>{100, 100, dist_z + max_D}, 0}, comp_z<T>());
		}
		
		for (it_z = z_beg; it_z != z_end; ++it_z) {
		    for (auto j_it = it_z + 1; j_it != z_end + 1; ++j_it) {
		    	int i = it_z->second, j = j_it->second;
		    	if (trgs[i].is_far(trgs[j])) {
				    continue;
				}
			    if (trgs[i].is_intersect(trgs[j])) {
			        res.insert(i);
			        res.insert(j);
			    }
		    }
		}
		dist_z += max_D;
	}
}

template <typename T>
set<int> intersecting_triangles(const vector<Triangle<T>>& trgs) {
	set<int> res;
	vector<pair<Point<T>, int>> spheres;
	T max_R = 0;
	
	for (int i = 0; i < trgs.size(); ++i) {
		Sphere<T> s = {trgs[i]};
		spheres.push_back(pair<Point<T>, int>{s.centr, i});
		T r;
		if ((r = s.R) > max_R)
		    max_R = r;
	}
	T max_D = 2*max_R, dist_x = max_D;
	
	sort(spheres.begin(), spheres.end(), comp_x<T>());
	auto it_x = spheres.begin(), x_beg = it_x, x_end = it_x;
	auto it_end = spheres.end();
	int k = 0;
	
	while (it_x != it_end) {
		sort(x_beg, x_end, comp_x<T>());
		if (k == 0) {
			x_end = lower_bound(x_beg, it_end, pair<Point<T>, int>{Point<T>{dist_x + max_D, 100, 100}, 0}, comp_x<T>());
			++k;
		} else {
			x_beg = lower_bound(x_beg, it_end, pair<Point<T>, int>{Point<T>{dist_x - max_D, 100, 100}, 0}, comp_x<T>());
			x_end = lower_bound(x_beg, it_end, pair<Point<T>, int>{Point<T>{dist_x + max_D, 100, 100}, 0}, comp_x<T>());
		}
		
		sort(x_beg, x_end, comp_y<T>());
		auto y_beg = x_beg, y_end = x_beg, it_y = x_beg, it_y_end = x_end;
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
			search_area(y_beg, y_end, max_D, trgs, res);
			
			it_y = y_end;
			dist_y += max_D;
		}
		it_x = x_end;
		dist_x += max_D;
	}

	return res;
}

int main() {
	vector<Triangle<double>> trgs;
	int N;
	cin >> N;
	for (int i = 0; i < N; ++i) {
		Point<double> A, B, C;
		cin >> A >> B >> C;
		Triangle<double> t{A, B, C};
		trgs.push_back(t);
	}
	
	set<int> ans = intersecting_triangles(trgs);
	
	for (auto it = ans.begin(), ite = ans.end(); it != ite; ++it) {
		cout << *it << endl;
	}
	
	return 0;
}
