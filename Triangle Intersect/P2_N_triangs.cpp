#include <cmath>
#include <iterator>
#include <time.h>
#include "Geometry.hpp"
using namespace std;

template <typename T>
set<int> intersecting_triangles(const vector<Triangle<T>>& trgs) {
	set<int> res;
	vector<pair<Point<T>, int>> spheres;
	T max_R = 0;

	for (int i = 0; i < trgs.size(); ++i) {
		const Sphere<T> s{trgs[i]};
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
	auto trgs_beg = trgs.begin();

	while (it_x != it_end) {
		sort(x_beg, x_end, comp_x<T>());
		if (k == 0) {
			x_end = lower_bound(x_beg, it_end, pair<Point<T>, int>{Point<T>{dist_x + max_D, 100, 100}, 0}, comp_x<T>());
			++k;
		} else {
			x_beg = lower_bound(x_beg, it_end, pair<Point<T>, int>{Point<T>{dist_x - max_D, 100, 100}, 0}, comp_x<T>());
			x_end = lower_bound(x_beg, it_end, pair<Point<T>, int>{Point<T>{dist_x + max_D, 100, 100}, 0}, comp_x<T>());
		}

		area_y(x_beg, x_end, max_D, trgs_beg, res);

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
    unsigned int start_time =  clock();
	set<int> ans = intersecting_triangles(trgs);
    unsigned int end_time = clock();
	for (auto it = ans.begin(), ite = ans.end(); it != ite; ++it) {
		cout << *it << endl;
	}
    cout << (end_time - start_time) / 1000000.0 << endl;
	return 0;
}
