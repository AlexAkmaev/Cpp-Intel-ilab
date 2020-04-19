//#include "Block.h"
//#include "token.h"
//
///* token_parsed_file *
//	To print a parsed file for tokens, pass the ParFile keyword
//	as the third parameter to the command line parameters.
//*/
//void token_parsed_file(const std::vector<Token>& tokens) {
//	for(const auto& i : tokens) {
//		std::cout << i.Value << "  ";
//		if (i.type == TokenType::Semicolon) {
//	    std::cout << std::endl;
//		}
//	}
//}
//
//int main(int argc, char *argv[]) {
//
//	std::fstream is;
//	is.open(argv[1], std::ios::in);
//
//	std::vector<Token> tokens = Tokenize(is);
//
//	if (argc == 3 && static_cast<std::string>(argv[2]) == "ParFile") {
//	  token_parsed_file(tokens);
//  }
//
//	std::map<std::string, int> name_Value;
//	Block main_block{name_Value};
//	main_block.Execution(tokens);
//
//	is.close();
//	return 0;
//}
#include <iostream>

#include "ParaCL_Driver.hpp"

int main(int argc, char *argv[]) {
  std::fstream is;
  is.open(argv[1], std::ios::in);

  if (argc != 2) {
    std::cerr << "No file to read";
    return 1;
  }

  FlexLexer* lexer = new yyFlexLexer;
  yy::ParaCL_Driver driver(lexer, is);
  driver.parse();

  is.close();
  return 0;
}
