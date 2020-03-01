#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "block.h"
#include "token.h"

using namespace std;

//output a parsed file
void token_parsed_file(const vector<Token>& tokens) {
	for(const auto& i : tokens) {
		cout << i.value << "  ";
		if (i.type == TokenType::Semicolon) {
	    cout << endl;
		}
	}
}

int main(int argc, char *argv[]) {
	
	fstream is;
	is.open(argv[1], ios::in);
	
	vector<Token> tokens = Tokenize(is);
	
	if (argc == 3 && string(argv[2]) == "parfile") {
	  token_parsed_file(tokens);
  }
  
	map<string, int> name_value;
	Block bl{name_value};
	bl.Execution(tokens);
	
	is.close();
	return 0;
}
