#pragma once

#include <FlexLexer.h>
#include <deque>
#include <fstream>
#include "nodes.hpp"
#include "pcl_parser.tab.hpp"

namespace yy {

class ParaCL_Driver {
  yyFlexLexer *plex_;
public:
  std::deque<Block*> scopes_;
//  const std::string file;
//  location locatio;

  ParaCL_Driver (FlexLexer *plex, std::istream* is) : plex_(plex) { yyin = is; scopes_.push_back(new Block()); }
  //ParaCL_Driver (std::ifstream* is) : plex_(is) { scopes_.push_back(new Block()); }

  ParaCL_Parser::token_type yylex(ParaCL_Parser::semantic_type* yylval) {
    auto tt = static_cast<ParaCL_Parser::token_type>(plex_->yylex());
    if (tt == yy::ParaCL_Parser::token_type::NUMBER) {
      yylval->as<int>() = std::stoi(plex_->YYText());
    }
    if (tt == yy::ParaCL_Parser::token_type::ID) {
      yylval->build<std::string>() = plex_->YYText();
    }
    return tt;
  }

  bool parse() {
    ParaCL_Parser PCL_Parser(this);
    return !PCL_Parser.parse();
  }

  Block* find_id(std::string id) {
    for(int i = scopes_.size() - 1; i >=0; --i) {
        Block* current_scope = scopes_[i];
        if (current_scope->find(id)) {
            return current_scope;
        }
    }
    return scopes_.back();
  }

};

}
