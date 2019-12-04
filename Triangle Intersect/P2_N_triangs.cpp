#include <cmath>
#include <iterator>
#include <time.h>
#include "Geometry.hpp"
using namespace std;

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
