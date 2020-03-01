#include "token.h"

#include <sstream>
#include <sstream>
#include <cstdio>
#include <stdexcept>
#include <iostream>

using namespace std;



bool is_not_a_tokentype(const char& c) {
	return (c != '+' && c != '-' && c != '*' && c != '/' &&
	        c != '=' && c != '(' && c != ')' && c != '{' &&
	        c != '}' && c != '<' && c != '>'  && c != '&' &&
          c != '|' && c != ';' && c != '?' && c != '!');
}

string read_var_name(istream& is) {
	string res;
	char c;
	while(is.peek() != ' ' && is_not_a_tokentype(is.peek()) && is >> c) {
		res += c;
	}
	return res;
}


vector<Token> Tokenize(istream& cl) {
  vector<Token> tokens;
  char c;
  while (cl >> c) {
    if (isdigit(c)) {
      string data(1, c);
      while (isdigit(cl.peek())) {
        data += cl.get();
      }
      tokens.push_back({data, TokenType::Data});
/////////while
    } else if (c == 'w') {
    	string s = "w";
    	if ((s += cl.get()) == "wh" && (s += cl.get()) == "whi" && (s += cl.get()) == "whil" && (s += cl.get()) == "while") {
        tokens.push_back({s, TokenType::While});
      } else {
      	string var_name;
      	var_name = s;
        var_name += read_var_name(cl);
        tokens.push_back({var_name, TokenType::VarName});
      }
/////////if      
    } else if (c == 'i') {
    	string s = "i";
    	if ((s += cl.get()) == "if") {
        tokens.push_back({s, TokenType::If});
      } else {
      	string var_name;
        var_name = s;
        var_name += read_var_name(cl);
        tokens.push_back({var_name, TokenType::VarName});
      }
/////////print
    } else if (c == 'p') {
    	string s(1, c);
    	if ((s += cl.get()) == "pr" && (s += cl.get()) == "pri" && (s += cl.get()) == "prin" && (s += cl.get()) == "print") {
        tokens.push_back({s, TokenType::Print});
	    } else {
	    	string var_name;
	    	var_name = s;
	      var_name += read_var_name(cl);
	      tokens.push_back({var_name, TokenType::VarName});
	    }
////////ENDL
		} else if (c == 'E') {
    	string s(1, c);
    	if ((s += cl.get()) == "EN" && (s += cl.get()) == "END" && (s += cl.get()) == "ENDL") {
        tokens.push_back({s, TokenType::Endl});
	    } else {
	    	string var_name;
	    	var_name = s;
	      var_name += read_var_name(cl);
	      tokens.push_back({var_name, TokenType::VarName});
	    }
		} else if (c == '"') {
    	string str;
    	getline(cl, str, '"');
    	tokens.push_back({str, TokenType::String});
		} else if (c == '?') {
    	tokens.push_back({"?", TokenType::Scanf});
 	  } else if (c == ';') {
    	tokens.push_back({";", TokenType::Semicolon});
 	  } else if (c == '(') {
      tokens.push_back({"(", TokenType::Paren_LEFT});
    } else if (c == ')') {
      tokens.push_back({")", TokenType::Paren_RIGHT});
    } else if (c == '{') {
      tokens.push_back({"{", TokenType::Bracelet_LEFT});
    } else if (c == '}') {
      tokens.push_back({"}", TokenType::Bracelet_RIGHT});
    } else if (c == '<') {
      if (cl.peek() == '=') {
        cl.get();
        tokens.push_back({"<=", TokenType::Compare_Op});
      } else {
        tokens.push_back({"<", TokenType::Compare_Op});
      }
    } else if (c == '>') {
      if (cl.peek() == '=') {
        cl.get();
        tokens.push_back({">=", TokenType::Compare_Op});
      } else {
        tokens.push_back({">", TokenType::Compare_Op});
      }
    } else if (c == '=') {
      if (cl.peek() == '=') {
      	cl.get();
        tokens.push_back({"==", TokenType::Compare_Op});
      } else {
        tokens.push_back({"=", TokenType::Assign});
      }
    } else if (c == '!') {
      if (cl.get() == '=') {
        tokens.push_back({"!=", TokenType::Compare_Op});
      } else {
        throw logic_error("Unknown token 2");
      }
    } else if (c == '&') {
      if (cl.get() == '&') {
        tokens.push_back({"&&", TokenType::Compare_Op});
      } else {
        throw logic_error("Unknown token 3");
      }
    } else if (c == '|') {
      if (cl.get() == '|') {
        tokens.push_back({"||", TokenType::Compare_Op});
      } else {
        throw logic_error("Unknown token 4");
      }
    } else if (c == '+') {
      tokens.push_back({"+", TokenType::Arithmetic_Op});
    } else if (c == '-') {
      tokens.push_back({"-", TokenType::Arithmetic_Op});
    } else if (c == '*') {
      tokens.push_back({"*", TokenType::Arithmetic_Op});
    } else if (c == '/') {
      tokens.push_back({"/", TokenType::Arithmetic_Op});
    } else if (c == ' ') {
    	continue;
    } else {
    	string var_name(1, c);
    	var_name += read_var_name(cl);
    	tokens.push_back({var_name, TokenType::VarName});
    }
  }

  return tokens;
}


ostream& operator<< (ostream& os, const TokenType& t) {
	if(t == TokenType::Logic_Op) {
		os << "Logic_Op";
	} else if(t == TokenType::Compare_Op) {
		os << "Compare_Op";
	} else if(t == TokenType::Assign) {
		os << "Assign";
	} else if(t == TokenType::While) {
		os << "While";
	} else if(t == TokenType::If) {
		os << "If";
	} else if(t == TokenType::Print) {
		os << "Print";
	} else if(t == TokenType::Scanf) {
		os << "Scanf";
	} else if(t == TokenType::VarName) {
		os << "VarName";
	} else if(t == TokenType::Data) {
		os << "Data";
	} else if(t == TokenType::String) {
		os << "String";
	} else if(t == TokenType::Endl) {
		os << "Endl";
	} else if(t == TokenType::Paren_LEFT) {
		os << "Paren_LEFT";
	} else if(t == TokenType::Paren_RIGHT) {
		os << "Paren_RIGHT";
	} else if(t == TokenType::Bracelet_LEFT) {
		os << "Bracelet_LEFT";
	} else if(t == TokenType::Bracelet_RIGHT) {
		os << "Bracelet_RIGHT";
	} else if(t == TokenType::Arithmetic_Op) {
		os << "Arithmetic_Op";
	}else if(t == TokenType::Semicolon) {
		os << "Semicolon";
	}
}	

