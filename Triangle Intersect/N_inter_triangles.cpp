#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <iterator>
#include <algorithm>
#include "Geometry.hpp"
using namespace std;

template <typename T>
set<int> intersecting_triangles(const vector<Triangle<T>>& trgs) {
	set<int> res;
	for (int i = 0; i < trgs.size(); i++) {
		for (int j = i + 1; j < trgs.size(); j++) {
			if (trgs[i].is_far(trgs[j]))
			    continue;
		    if (trgs[i].is_intersect(trgs[j])) {
		        res.insert(i);
		        res.insert(j);
		    }
	    }
	}
	return res;
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
	
	set<int> ans = intersecting_triangles(trgs);
	for (auto it = ans.begin(); it != ans.end(); it++) {
		cout << *it << endl;
	}
	
	return 0;
}
