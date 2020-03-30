#include <cmath>
#include <ctime>
#include "test_runner.h"
#include "..\search_tree.hpp"

void Test_push() {
	SearchTree<int> tree;
	int data;
	while(std::cin >> data) {
		tree.push(data);
		ASSERT(tree.is_balanced());
	}
	std::cin.clear();
	cin.seekg(0, std::ios::beg);
}

void Test_exists() {
	SearchTree<int> tree;
	vector<int> tree_data;
	int data;
	while(std::cin >> data) {
		tree.push(data);
		tree_data.push_back(data);
	}
	
	int limiter = tree_data.size() / 2;
	srand(time(nullptr));
	while(limiter > 0) {
		int idx = rand() % (tree_data.size() - 1);
		--limiter;
		ASSERT(tree.exists(tree_data[idx]));
	}
	std::cin.clear();
	cin.seekg(0, std::ios::beg);
}

void Test_copy_ctor() {
	SearchTree<int> tree;
	vector<int> tree_data;
	int data;
	while(std::cin >> data) {
		tree.push(data);
		tree_data.push_back(data);
	}
	
	SearchTree<int> copy_tree(tree);
	for(const int& i : tree_data) {
		ASSERT(copy_tree.exists(i));
	}
	
	std::cin.clear();
	cin.seekg(0, std::ios::beg);
}

void Test_assignment_op() {
	SearchTree<int> tree;
	vector<int> tree_data;
	int data;
	while(std::cin >> data) {
		tree.push(data);
		tree_data.push_back(data);
	}
	
	SearchTree<int> copy_tree;
	int limiter = tree_data.size() * 0.9;
	int peak_value = tree_data.size() * 9;
	srand(time(nullptr));
	for(int i = 0; i < limiter; ++i) {
		data = rand() % peak_value;
		copy_tree.push(data);
	}
	
	copy_tree = tree;
	for(const int& i : tree_data) {
		ASSERT(copy_tree.exists(i));
	}
	
	std::cin.clear();
	cin.seekg(0, std::ios::beg);
}

void Test_remove() {
	SearchTree<int> tree;
	vector<int> tree_data;
	int data;
	while(std::cin >> data) {
		tree.push(data);
		tree_data.push_back(data);
	}
	
	int tree_size = tree_data.size();
	const int limiter = tree_size / 2;
	srand(time(nullptr));
	while(tree_size > limiter) {
		int idx = rand() % (tree_data.size() - 1);
		tree.remove(tree_data[idx]);
		tree_data.erase(tree_data.begin() + idx);
		--tree_size;
		ASSERT(tree.is_balanced());
	}
	std::cin.clear();
	cin.seekg(0, std::ios::beg);
}

void Test_addition_op() {
	SearchTree<int> lhs, rhs;
	vector<int> tree_data;
	int ldata, rdata;
	while(std::cin >> ldata && std::cin >> rdata) {
		lhs.push(ldata);
		rhs.push(rdata);
		tree_data.push_back(ldata);
		tree_data.push_back(rdata);
		ASSERT(lhs.is_balanced());
		ASSERT(rhs.is_balanced());
	}
	
	SearchTree<int> uni = lhs + rhs;
	for(const auto& i : tree_data) {
		ASSERT(uni.exists(i));
	}
	ASSERT(uni.is_balanced());
	std::cin.clear();
	cin.seekg(0, std::ios::beg);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, Test_push);
  RUN_TEST(tr, Test_exists);
  RUN_TEST(tr, Test_copy_ctor);
  RUN_TEST(tr, Test_assignment_op);
  RUN_TEST(tr, Test_remove);
  RUN_TEST(tr, Test_addition_op);
  return 0;
}
