#pragma once

#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <map>
#include <tuple>
#include <vector>
#include <cstdlib>
#include "token.h"
#include "node.h"


using namespace std;


class Block {
public:	
  
	explicit Block(const map<string, int>& values);

	const map<string, int>& map_names();
	
	/*** Shunting-yard algorithm ***/
	template <class Iterator>
	int Parse(Iterator beg, Iterator end) {
		Iterator token = beg;
		// Empty expression
	  if (token == end) {
	    return 0;
	  } else if (end - token == 1 && token->type == TokenType::Data) {
	  	return atoi(token->value.c_str());
	  }
	
	  stack<shared_ptr<Node>> values;
	  stack<shared_ptr<Op>> ops;
	  
	  auto PopOps = [&](int precedence) {
	    while (!ops.empty() && ops.top()->precedence >= precedence) {
	      auto value1 = values.top();
	      values.pop();
	      auto value2 = values.top();
	      values.pop();
	      auto op = ops.top();
	      ops.pop();
	
	      op->SetRight(value1);
	      op->SetLeft(value2);
	
	      values.push(op);
	    }
	  };
	  while (token != end) {
	    const auto &val = *token;
	    if (val.value == "*" || val.value == "/") {
	      PopOps(6);
	      ops.push(make_shared<Op>(val.value));
	    } else if (val.value == "+" || val.value == "-") {
	      PopOps(5);
	      ops.push(make_shared<Op>(val.value));
	    } else if (val.value == "<" || val.value == "<=" || val.value == ">" || val.value == ">=") {
	      PopOps(4);
	      ops.push(make_shared<Op>(val.value));
	    } else if (val.value == "!=" || val.value == "==") {
	      PopOps(3);
	      ops.push(make_shared<Op>(val.value));
	    } else if (val.value == "&&") {
	      PopOps(2);
	      ops.push(make_shared<Op>(val.value));
	    } else if (val.value == "||") {
	      PopOps(1);
	      ops.push(make_shared<Op>(val.value));
	    } else {
	      if (val.type == TokenType::Data) {
	      	values.push(make_shared<Variable>(atoi(val.value.c_str())));
	      } else if (val.type == TokenType::Paren_LEFT) {
	      	auto paren_right = find_pair_bracket(token + 1, end, TokenType::Paren_LEFT);
	      	if (paren_right == end)
					  throw logic_error("Wrong Syntax");
	        values.push(make_shared<Variable>(Parse(token + 1, paren_right)));
	        if ((token = paren_right + 1) == end)
	          break;
	      } else {
	        values.push(make_shared<Variable>(name_value.at(val.value)));
	      }
	    }
	
	    ++token;
	  }
	  
	  while (!ops.empty()) {
	    PopOps(0);
	  }
	  
	  auto node = values.top();
	  return node->Evaluate();
	}

	void Execution(const vector<Token>& tokens);
	
private:
	map<string, int> name_value;
};

bool operator==(const Token& t1, const Token& t2);
