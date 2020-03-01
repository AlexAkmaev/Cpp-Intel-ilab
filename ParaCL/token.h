#pragma once

#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

enum class TokenType {
	Logic_Op,
	Compare_Op,
	Arithmetic_Op,
	Assign,
	While,
	If,
	Print,
	Scanf,
	VarName,
	Data,
	Endl,
	String,
  Paren_LEFT,
  Paren_RIGHT,
  Bracelet_LEFT,
  Bracelet_RIGHT,
  Semicolon,
};

struct Token {
  const string value;
  const TokenType type;
};

vector<Token> Tokenize(istream& is);
ostream& operator<< (ostream& os, const TokenType& t);  //output operator for the token

