#include "ParaCL_Driver.hpp"

namespace yy {

  ParaCL_Driver::ParaCL_Driver(yyFlexLexer *plexer) : plexer_(plexer) {
      cur_block = new Block(cur_block);
  }

  ParaCL_Parser::token_type ParaCL_Driver::yylex(ParaCL_Parser::semantic_type* yylval, ParaCL_Parser::location_type* lloc) {
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

  bool ParaCL_Driver::parse() {
    ParaCL_Parser PCL_Parser(this);
    int res = PCL_Parser.parse();
    return !res;
  }

}
