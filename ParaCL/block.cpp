
#include "block.h"
using namespace std;

template <typename Iterator>
Iterator find_pair_bracket(Iterator beg_, Iterator end_, const TokenType& bracket_type) {
	if ((bracket_type != TokenType::Paren_LEFT) && (bracket_type != TokenType::Bracelet_LEFT)) {
		throw logic_error("Unknown type of opening bracket");
	}
	int depth = 1;
	const TokenType& closing_bracket = bracket_type == TokenType::Paren_LEFT ?
                                     TokenType::Paren_RIGHT : TokenType::Bracelet_RIGHT;
	for(Iterator it = beg_; it != end_; ++it) {
		if (it->type == bracket_type) {
			++depth;
		} else if (it->type == closing_bracket) {
			--depth;
		}
		if (depth < 0)
		  throw logic_error("Incorrect bracket sequence");
    if (depth == 0) 
      return it;
	}
	
	return end_;
}

/*** class Block ***/
Block::Block(const map<string, int>& values) : name_value(values) {}

const map<string, int>& Block::map_names() { return name_value; }

void Block::Execution(const vector<Token>& tokens) {
	auto it_beg = tokens.begin(), it_end = tokens.end();
	for(auto token = it_beg; token != it_end; ++token) {
		if (token->type == TokenType::Assign) {
			++token;
			if (token->type == TokenType::Scanf) {
				int value;
				cin >> value;
				string variable_name = (token - 2)->value;
				name_value[variable_name] = value;
			} else {
				auto semicolon = find(token, it_end, Token{";", TokenType::Semicolon});
				int value = Parse(token, semicolon);
				string variable_name = (token - 2)->value;
				name_value[variable_name] = value;
		  }
		} else if (token->type == TokenType::Print) {
			++token;
			if (token->type == TokenType::Endl) {
				cout << endl;
			} else if (token->type == TokenType::String) {
				cout << token->value;
			} else {
				string variable_name = token->value;
				cout << name_value[variable_name];
			}
		} else if (token->type == TokenType::While || token->type == TokenType::If) {
			const TokenType& keyword = token->type;
			++token;
			auto paren_right = find_pair_bracket(token + 1, it_end, TokenType::Paren_LEFT);
			if (token->type != TokenType::Paren_LEFT || paren_right == it_end)
			  throw logic_error("Wrong Syntax");
	    
	    auto bracelet_left = paren_right + 1;
	    auto bracelet_right = find_pair_bracket(bracelet_left + 1, it_end, TokenType::Bracelet_LEFT);
	    if (bracelet_left->type != TokenType::Bracelet_LEFT || bracelet_right == it_end)
			  throw logic_error("Wrong Syntax");
	    
			int condition;
			if (keyword == TokenType::While) {
		    while (condition = Parse(token + 1, paren_right) ) {
		    	vector<Token> tokens_in_block(bracelet_left + 1, bracelet_right);
		    	Block bl{name_value};
		    	bl.Execution(tokens_in_block);
		    	const map<string, int>& new_values = bl.map_names();
		    	for(auto& item : name_value) {
		    		item.second = new_values.at(item.first);
		    	}
		    }
		  } else {
		  	if (condition = Parse(token + 1, paren_right) ) {
		    	vector<Token> tokens_in_block(bracelet_left + 1, bracelet_right);
		    	Block bl{name_value};
		    	bl.Execution(tokens_in_block);
		    	const map<string, int>& new_values = bl.map_names();
		    	for(auto& item : name_value) {
		    		item.second = new_values.at(item.first);
		    	}
		    }
		  }
		  token = bracelet_right;
		}
	}
}
	
bool operator==(const Token& t1, const Token& t2) {
	return tie(t1.value, t1.type) == tie(t2.value, t2.type);
}
