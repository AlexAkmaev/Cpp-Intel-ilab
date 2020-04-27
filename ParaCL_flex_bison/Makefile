CXX = g++
LEX = flex
YACC = bison

CXXFLAGS = -g -std=c++17

HEADERS = ParaCL_Driver.hpp pcl_parser.tab.hpp nodes.hpp

compiler: lex.yy.cc main.cpp pcl_parser.tab.cpp  ParaCL_Driver.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) main.cpp lex.yy.cc pcl_parser.tab.cpp ParaCL_Driver.cpp -o compiler

# Generate scanner and parser

pcl_parser.tab.cpp pcl_parser.tab.hpp: pcl_parser.ypp
	$(YACC) -d pcl_parser.ypp

lex.yy.cc: pcl_lexer.lpp
	$(LEX) pcl_lexer.lpp


.PHONY: clean
clean:
	rm -f lex.yy.cc pcl_parser.tab.cpp pcl_parser.tab.hpp location.hh position.hh stack.hh compiler *.out
