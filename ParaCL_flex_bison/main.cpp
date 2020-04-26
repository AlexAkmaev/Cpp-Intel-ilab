#include <iostream>

#include "ParaCL_Driver.hpp"

int main(int argc, char *argv[]) {

  if (argc < 2) {
    std::cerr << "No file to read\n";
    return 1;
  } else if (argc > 2) {
    std::cerr << "Wrong number of arguments given\n";
    return 2;
  }

  std::ifstream input(argv[1]);
  yy::ParaCL_Driver driver(new yyFlexLexer(&input));
  driver.parse();

  return 0;
}
