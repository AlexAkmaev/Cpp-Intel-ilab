#include "test_runner.h"
#include "..\search_tree.hpp"
using namespace std;


int main() {
  TestRunner tr;
  RUN_TEST(tr, TestComparison);
  RUN_TEST(tr, TestSorting);
  return 0;
}
