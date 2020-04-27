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

  explicit ParaCL_Driver (yyFlexLexer *plexer);

  ParaCL_Parser::token_type yylex(ParaCL_Parser::semantic_type*, ParaCL_Parser::location_type*);

  bool parse();

};

}
