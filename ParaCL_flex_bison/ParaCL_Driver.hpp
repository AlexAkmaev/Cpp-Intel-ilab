#pragma once

#include <FlexLexer.h>
#include <deque>
#include <vector>
#include <algorithm>
#include <fstream>
#include "nodes.hpp"
#include "pcl_parser.tab.hpp"

namespace yy {

class ParaCL_Driver {
  yyFlexLexer *plexer_;
public:
  //std::deque<Block*> scopes_;
  Block* cur_block = nullptr;

  explicit ParaCL_Driver (yyFlexLexer *plexer) : plexer_(plexer) {cur_block = new Block(cur_block);}//scopes_.push_back(new Block()); }

  ParaCL_Parser::token_type yylex(ParaCL_Parser::semantic_type* yylval, ParaCL_Parser::location_type* lloc) {
    *lloc = plexer_->lineno();
    auto tt = static_cast<ParaCL_Parser::token_type>(plexer_->yylex());
    if (tt == yy::ParaCL_Parser::token_type::NUMBER) {
      yylval->as<int>() = std::stoi(plexer_->YYText());
    }
    if (tt == yy::ParaCL_Parser::token_type::ID) {
      yylval->build<std::string>() = plexer_->YYText();
    }
    return tt;
  }

  bool parse() {
    ParaCL_Parser PCL_Parser(this);
    int res = PCL_Parser.parse();
    return !res;
  }

//  Block*& find_id(std::string id) {
//    if (scopes_.empty()) {
//        scopes_.push_back(new Block());
//        return scopes_.front();
//    }
////    for(int i = scopes_.size() - 1; i >=0; --i) {
//    for(int i = 0; i < scopes_.size(); ++i) {
//        Block*& current_scope = scopes_[i];
//        if (current_scope->find(id)) {
//            std::cout << "|" << i << "| ";
//            return current_scope;
//        }
//    }
////    return scopes_.back();
//    return scopes_.front();
//  }

};

}
