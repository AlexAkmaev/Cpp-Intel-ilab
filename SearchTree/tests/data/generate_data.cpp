#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

const int amount_of_data = 10000;
const int peak_value = 5*amount_of_data;

int main() {
	srand(time(nullptr));
	for(int i = 0; i < amount_of_data; ++i) {
		cout << rand() % peak_value << '\n';
	}
	
	return 0;
}
