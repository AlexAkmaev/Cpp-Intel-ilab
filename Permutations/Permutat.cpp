#include <iostream>
#include <exception>
#include <stdexcept>
#include <numeric>
#include <time.h>
#include "Combination.h"


std::vector<Combination> search_permutations(std::vector<int>& data) {
	int n = data.size() / 2, size_t = data.size();
	std::vector<Combination> res;
	int min_sum = size_t + 1 + 2, max_sum = size_t + (size_t - 1) + (size_t - 2) - 2;
	
  do {
    Trio tester(Cell{data[0]}, Cell{data[1]}, Cell{data[2]});
    int tester_sum = tester.GetSum();
    if (tester_sum < min_sum || tester_sum > max_sum) {
 	    int cur_sum = tester_sum;
    	do {
    	  Trio cur(Cell{data[0]}, Cell{data[1]}, Cell{data[2]});
    	  cur_sum = cur.GetSum();
    	  bool ret = next_permutation(data.begin(), data.end());
    	  if (ret == false) 
    	    return res;
    	} while(cur_sum < min_sum || cur_sum > max_sum);
    }
    
    Combination combi(n);
		Trio trio_first(Cell{data[0]}, Cell{data[1]}, Cell{data[2]});
 	  combi.Push(trio_first);
		int trio_first_sum = trio_first.GetSum();
		bool indic = true;
		
    for(int i = 2; i < size_t; i += 2) {
   		Trio trio_cur(Cell{data[i + 1]}, Cell{data[i]}, Cell{data[(i + 2) % (size_t - 1)]});
   		if (trio_cur.GetSum() != trio_first_sum) {
   		  indic = false;
			  break;
   		} else {
   			combi.Push(trio_cur);
   		}
    }
    if (indic && combi.Is_minimal_comb())
      res.push_back(combi);
  } while(next_permutation(data.begin(), data.end()));

	
	return res;
}
	  
int main() {
	int N;
	std::cin >> N;
	try {
		if (N % 2 != 0) {
			throw std::invalid_argument("Please enter even numder:)");
		}
	} catch (std::exception& ex) {
		std::cout << ex.what();
		return 0;
	}
	
	std::vector<int> data(N);
	iota(data.begin(), data.end(), 1);
	
	std::vector<Combination> ans;
	ans = search_permutations(data);
	
	for(const auto& comb : ans) {
		std::cout << comb << std::endl;
	}
  
	return 0;
}
