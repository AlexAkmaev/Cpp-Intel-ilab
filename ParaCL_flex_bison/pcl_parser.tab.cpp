// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "pcl_parser.tab.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "pcl_parser.tab.hpp"

// User implementation prologue.

#line 51 "pcl_parser.tab.cpp" // lalr1.cc:412
// Unqualified %code blocks.
#line 40 "pcl_parser.ypp" // lalr1.cc:413

#include "ParaCL_Driver.hpp"

    namespace yy {
        ParaCL_Parser::token_type yylex
        (ParaCL_Parser::semantic_type* yylval, ParaCL_Parser::location_type* yylloc,
        ParaCL_Driver* driver);
    }


#line 64 "pcl_parser.tab.cpp" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 150 "pcl_parser.tab.cpp" // lalr1.cc:479

  /// Build a parser object.
  ParaCL_Parser::ParaCL_Parser (yy::ParaCL_Driver* driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  ParaCL_Parser::~ParaCL_Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  ParaCL_Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  ParaCL_Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  ParaCL_Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
      switch (other.type_get ())
    {
      case 37: // EXPR
      case 38: // EXPR_L
      case 39: // EXPR1
      case 40: // EXPR2
      case 41: // TERM
      case 42: // VAL
      case 43: // ifexpr
        value.copy< Expr_t* > (other.value);
        break;

      case 31: // PROGRAM
      case 32: // OPS
      case 33: // OP1
      case 34: // OP2
      case 35: // ifscope
      case 36: // OP
        value.copy< Oper_t* > (other.value);
        break;

      case 14: // NUMBER
        value.copy< int > (other.value);
        break;

      case 15: // ID
        value.copy< std::string > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
  ParaCL_Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {
    (void) v;
      switch (this->type_get ())
    {
      case 37: // EXPR
      case 38: // EXPR_L
      case 39: // EXPR1
      case 40: // EXPR2
      case 41: // TERM
      case 42: // VAL
      case 43: // ifexpr
        value.copy< Expr_t* > (v);
        break;

      case 31: // PROGRAM
      case 32: // OPS
      case 33: // OP1
      case 34: // OP2
      case 35: // ifscope
      case 36: // OP
        value.copy< Oper_t* > (v);
        break;

      case 14: // NUMBER
        value.copy< int > (v);
        break;

      case 15: // ID
        value.copy< std::string > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  ParaCL_Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  ParaCL_Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Expr_t* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  ParaCL_Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Oper_t* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  ParaCL_Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const int v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  ParaCL_Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  template <typename Base>
  inline
  ParaCL_Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  ParaCL_Parser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
    switch (yytype)
    {
      case 37: // EXPR
      case 38: // EXPR_L
      case 39: // EXPR1
      case 40: // EXPR2
      case 41: // TERM
      case 42: // VAL
      case 43: // ifexpr
        value.template destroy< Expr_t* > ();
        break;

      case 31: // PROGRAM
      case 32: // OPS
      case 33: // OP1
      case 34: // OP2
      case 35: // ifscope
      case 36: // OP
        value.template destroy< Oper_t* > ();
        break;

      case 14: // NUMBER
        value.template destroy< int > ();
        break;

      case 15: // ID
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  ParaCL_Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  ParaCL_Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 37: // EXPR
      case 38: // EXPR_L
      case 39: // EXPR1
      case 40: // EXPR2
      case 41: // TERM
      case 42: // VAL
      case 43: // ifexpr
        value.move< Expr_t* > (s.value);
        break;

      case 31: // PROGRAM
      case 32: // OPS
      case 33: // OP1
      case 34: // OP2
      case 35: // ifscope
      case 36: // OP
        value.move< Oper_t* > (s.value);
        break;

      case 14: // NUMBER
        value.move< int > (s.value);
        break;

      case 15: // ID
        value.move< std::string > (s.value);
        break;

      default:
        break;
    }

    location = s.location;
  }

  // by_type.
  inline
  ParaCL_Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  ParaCL_Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  ParaCL_Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  ParaCL_Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  ParaCL_Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  ParaCL_Parser::by_type::type_get () const
  {
    return type;
  }
  // Implementation of make_symbol for each symbol type.
  ParaCL_Parser::symbol_type
  ParaCL_Parser::make_WHILE (const location_type& l)
  {
    return symbol_type (token::WHILE, l);
  }

  ParaCL_Parser::symbol_type
  ParaCL_Parser::make_IF (const location_type& l)
  {
    return symbol_type (token::IF, l);
  }

  ParaCL_Parser::symbol_type
  ParaCL_Parser::make_ELSE (const location_type& l)
  {
    return symbol_type (token::ELSE, l);
  }

  ParaCL_Parser::symbol_type
  ParaCL_Parser::make_PRINT (const location_type& l)
  {
    return symbol_type (token::PRINT, l);
  }

  ParaCL_Parser::symbol_type
  ParaCL_Parser::make_LESS_EQ (const location_type& l)
  {
    return symbol_type (token::LESS_EQ, l);
  }

  ParaCL_Parser::symbol_type
  ParaCL_Parser::make_GRT_EQ (const location_type& l)
  {
    return symbol_type (token::GRT_EQ, l);
  }

  ParaCL_Parser::symbol_type
  ParaCL_Parser::make_AND (const location_type& l)
  {
    return symbol_type (token::AND, l);
  }

  ParaCL_Parser::symbol_type
  ParaCL_Parser::make_OR (const location_type& l)
  {
    return symbol_type (token::OR, l);
  }

  ParaCL_Parser::symbol_type
  ParaCL_Parser::make_NOT_EQUAL (const location_type& l)
  {
    return symbol_type (token::NOT_EQUAL, l);
  }

  ParaCL_Parser::symbol_type
  ParaCL_Parser::make_EQUAL (const location_type& l)
  {
    return symbol_type (token::EQUAL, l);
  }

  ParaCL_Parser::symbol_type
  ParaCL_Parser::make_ERROR (const location_type& l)
  {
    return symbol_type (token::ERROR, l);
  }

  ParaCL_Parser::symbol_type
  ParaCL_Parser::make_NUMBER (const int& v, const location_type& l)
  {
    return symbol_type (token::NUMBER, v, l);
  }

  ParaCL_Parser::symbol_type
  ParaCL_Parser::make_ID (const std::string& v, const location_type& l)
  {
    return symbol_type (token::ID, v, l);
  }



  // by_state.
  inline
  ParaCL_Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  ParaCL_Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  ParaCL_Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  ParaCL_Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  ParaCL_Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  ParaCL_Parser::symbol_number_type
  ParaCL_Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  ParaCL_Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  ParaCL_Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 37: // EXPR
      case 38: // EXPR_L
      case 39: // EXPR1
      case 40: // EXPR2
      case 41: // TERM
      case 42: // VAL
      case 43: // ifexpr
        value.move< Expr_t* > (that.value);
        break;

      case 31: // PROGRAM
      case 32: // OPS
      case 33: // OP1
      case 34: // OP2
      case 35: // ifscope
      case 36: // OP
        value.move< Oper_t* > (that.value);
        break;

      case 14: // NUMBER
        value.move< int > (that.value);
        break;

      case 15: // ID
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  ParaCL_Parser::stack_symbol_type&
  ParaCL_Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 37: // EXPR
      case 38: // EXPR_L
      case 39: // EXPR1
      case 40: // EXPR2
      case 41: // TERM
      case 42: // VAL
      case 43: // ifexpr
        value.copy< Expr_t* > (that.value);
        break;

      case 31: // PROGRAM
      case 32: // OPS
      case 33: // OP1
      case 34: // OP2
      case 35: // ifscope
      case 36: // OP
        value.copy< Oper_t* > (that.value);
        break;

      case 14: // NUMBER
        value.copy< int > (that.value);
        break;

      case 15: // ID
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  ParaCL_Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  ParaCL_Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  ParaCL_Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  ParaCL_Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  ParaCL_Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  ParaCL_Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  ParaCL_Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  ParaCL_Parser::debug_level_type
  ParaCL_Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  ParaCL_Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline ParaCL_Parser::state_type
  ParaCL_Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  ParaCL_Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  ParaCL_Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  ParaCL_Parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location, driver));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 37: // EXPR
      case 38: // EXPR_L
      case 39: // EXPR1
      case 40: // EXPR2
      case 41: // TERM
      case 42: // VAL
      case 43: // ifexpr
        yylhs.value.build< Expr_t* > ();
        break;

      case 31: // PROGRAM
      case 32: // OPS
      case 33: // OP1
      case 34: // OP2
      case 35: // ifscope
      case 36: // OP
        yylhs.value.build< Oper_t* > ();
        break;

      case 14: // NUMBER
        yylhs.value.build< int > ();
        break;

      case 15: // ID
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 96 "pcl_parser.ypp" // lalr1.cc:859
    {
                                            yylhs.value.as< Oper_t* > () = yystack_[0].value.as< Oper_t* > ();
                                            yystack_[0].value.as< Oper_t* > ()->Evaluate();
                                            //$1->print();
                                            delete yystack_[0].value.as< Oper_t* > ();
                                        }
#line 934 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 3:
#line 104 "pcl_parser.ypp" // lalr1.cc:859
    { CBLOCK->append(yystack_[0].value.as< Oper_t* > ()); yylhs.value.as< Oper_t* > () = CBLOCK; }
#line 940 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 4:
#line 105 "pcl_parser.ypp" // lalr1.cc:859
    {/*$1->print(); std::cout << ($1 != nullptr) << "  ^^^  "; $2->print(); std::cout << "\n|";CBLOCK->append($1); */
                                          CBLOCK->append(yystack_[0].value.as< Oper_t* > ()); yylhs.value.as< Oper_t* > () = CBLOCK; }
#line 947 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 5:
#line 111 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Oper_t* > () = yystack_[1].value.as< Oper_t* > (); }
#line 953 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 6:
#line 112 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Oper_t* > () = new Exprop(yystack_[1].value.as< Expr_t* > ()); }
#line 959 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 7:
#line 114 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Oper_t* > () = new Printop(yystack_[1].value.as< Expr_t* > ()); }
#line 965 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 8:
#line 119 "pcl_parser.ypp" // lalr1.cc:859
    {
                                          yylhs.value.as< Oper_t* > () = yystack_[0].value.as< Oper_t* > ();
                                          CBLOCK = CBLOCK->prev_block;
                                        }
#line 974 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 9:
#line 125 "pcl_parser.ypp" // lalr1.cc:859
    {Block* bl = CBLOCK;
//                                           Block* b1 = new Block($2, SCOPES.front());
//                                           if (SCOPES.size() >= 2) {
//                                             Block*& bpr = SCOPES[1];
//                                             bpr->prev_block = b1;
//                                             SCOPES.insert(next(SCOPES.begin()), b1);
//                                           } else {
//                                             SCOPES.push_back(b1);
//                                           }
yystack_[1].location;//std::cout << "GGG:" << (bl != nullptr) << "\n"; bl->print();
                                           bl->append(yystack_[0].value.as< Oper_t* > ());
                                           yylhs.value.as< Oper_t* > () = new Ifop(yystack_[1].value.as< Expr_t* > (), bl, new Block(bl->prev_block));
                                        }
#line 992 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 10:
#line 142 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Oper_t* > () = yystack_[0].value.as< Oper_t* > (); }
#line 998 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 11:
#line 143 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Oper_t* > () = yystack_[0].value.as< Oper_t* > (); }
#line 1004 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 12:
#line 147 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Expr_t* > () = yystack_[0].value.as< Expr_t* > (); }
#line 1010 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 13:
#line 148 "pcl_parser.ypp" // lalr1.cc:859
    {
//                                          if(SCOPES.empty())
//                                            SCOPES.push_back(new Block());
//                                          $$ = new Assign($1, $3, SCOPES.back());
                                          //Block* cur = CBLOCK->find_block($1);
                                          yylhs.value.as< Expr_t* > () = new Assign(yystack_[2].value.as< std::string > (), yystack_[0].value.as< Expr_t* > (), CBLOCK);
                                        }
#line 1022 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 14:
#line 155 "pcl_parser.ypp" // lalr1.cc:859
    {
//                                          if(SCOPES.empty())
//                                            SCOPES.push_back(new Block());
//                                          $$ = new Scanfop($1, SCOPES.back());
                                          //Block* cur = CBLOCK->find_block($1);
                                          //std::cout << "GGG:" << @3 << "\n";
                                          yylhs.value.as< Expr_t* > () = new Scanfop(yystack_[2].value.as< std::string > (), CBLOCK);
                                        }
#line 1035 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 15:
#line 165 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Expr_t* > () = yystack_[0].value.as< Expr_t* > (); }
#line 1041 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 16:
#line 166 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Expr_t* > () = new Binary_expr("||", yystack_[2].value.as< Expr_t* > (), yystack_[0].value.as< Expr_t* > ()); }
#line 1047 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 17:
#line 167 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Expr_t* > () = new Binary_expr("&&", yystack_[2].value.as< Expr_t* > (), yystack_[0].value.as< Expr_t* > ()); }
#line 1053 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 18:
#line 170 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Expr_t* > () = yystack_[0].value.as< Expr_t* > (); }
#line 1059 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 19:
#line 171 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Expr_t* > () = new Binary_expr("==", yystack_[2].value.as< Expr_t* > (), yystack_[0].value.as< Expr_t* > ()); }
#line 1065 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 20:
#line 172 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Expr_t* > () = new Binary_expr("<=", yystack_[2].value.as< Expr_t* > (), yystack_[0].value.as< Expr_t* > ()); }
#line 1071 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 21:
#line 173 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Expr_t* > () = new Binary_expr(">=", yystack_[2].value.as< Expr_t* > (), yystack_[0].value.as< Expr_t* > ()); }
#line 1077 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 22:
#line 174 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Expr_t* > () = new Binary_expr("!=", yystack_[2].value.as< Expr_t* > (), yystack_[0].value.as< Expr_t* > ()); }
#line 1083 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 23:
#line 175 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Expr_t* > () = new Binary_expr(">", yystack_[2].value.as< Expr_t* > (), yystack_[0].value.as< Expr_t* > ()); }
#line 1089 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 24:
#line 176 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Expr_t* > () = new Binary_expr("<", yystack_[2].value.as< Expr_t* > (), yystack_[0].value.as< Expr_t* > ()); }
#line 1095 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 25:
#line 179 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Expr_t* > () = yystack_[0].value.as< Expr_t* > (); }
#line 1101 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 26:
#line 180 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Expr_t* > () = new Binary_expr("+", yystack_[2].value.as< Expr_t* > (), yystack_[0].value.as< Expr_t* > ()); }
#line 1107 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 27:
#line 181 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Expr_t* > () = new Binary_expr("-", yystack_[2].value.as< Expr_t* > (), yystack_[0].value.as< Expr_t* > ()); }
#line 1113 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 28:
#line 184 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Expr_t* > () = yystack_[0].value.as< Expr_t* > (); }
#line 1119 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 29:
#line 185 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Expr_t* > () = new Binary_expr("*", yystack_[2].value.as< Expr_t* > (), yystack_[0].value.as< Expr_t* > ()); }
#line 1125 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 30:
#line 186 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Expr_t* > () = new Binary_expr("/", yystack_[2].value.as< Expr_t* > (), yystack_[0].value.as< Expr_t* > ()); }
#line 1131 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 31:
#line 189 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Expr_t* > () = new Number(yystack_[0].value.as< int > ()); }
#line 1137 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 32:
#line 190 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Expr_t* > () = new Unary_expr("-", yystack_[0].value.as< Expr_t* > ()); }
#line 1143 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 33:
#line 191 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Expr_t* > () = new Unary_expr("!", yystack_[0].value.as< Expr_t* > ()); }
#line 1149 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 34:
#line 192 "pcl_parser.ypp" // lalr1.cc:859
    { yylhs.value.as< Expr_t* > () = yystack_[1].value.as< Expr_t* > (); }
#line 1155 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 35:
#line 193 "pcl_parser.ypp" // lalr1.cc:859
    {
//                                          if(SCOPES.empty())
//                                            SCOPES.push_back(new Block());
//                                          $$ = new Value($1, SCOPES.back());
                                          //Block* cur = CBLOCK->find_block($1);
                                          //std::cout << "NNN:" << @1 << "\n";
                                          yylhs.value.as< Expr_t* > () = new Value(yystack_[0].value.as< std::string > (), CBLOCK);
                                        }
#line 1168 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;

  case 36:
#line 203 "pcl_parser.ypp" // lalr1.cc:859
    {
                                          //std::cout << "NNN:" << @3 << "\n";
                                          CBLOCK = new Block(CBLOCK);
                                          yylhs.value.as< Expr_t* > () = yystack_[1].value.as< Expr_t* > ();
                                        }
#line 1178 "pcl_parser.tab.cpp" // lalr1.cc:859
    break;


#line 1182 "pcl_parser.tab.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  ParaCL_Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  ParaCL_Parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const signed char ParaCL_Parser::yypact_ninf_ = -21;

  const signed char ParaCL_Parser::yytable_ninf_ = -1;

  const signed char
  ParaCL_Parser::yypact_[] =
  {
      22,   -20,     3,   -21,    15,    53,    22,    53,     3,    42,
      22,   -21,   -21,   -21,   -21,    -1,    23,    -2,    16,    25,
     -21,    37,     3,    31,    43,   -21,   -21,    -3,   -21,    32,
     -21,   -21,   -21,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,   -21,    34,   -21,   -21,   -21,
     -21,   -21,    -2,    -2,    16,    16,    16,    16,    16,    16,
      25,    25,   -21,   -21,   -21
  };

  const unsigned char
  ParaCL_Parser::yydefact_[] =
  {
       0,     0,     0,    31,    35,     0,     0,     0,     0,     0,
       2,    10,    11,     8,     3,     0,    12,    15,    18,    25,
      28,     0,     0,     0,     0,    35,    32,     0,    33,     0,
       1,     4,     6,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     9,     0,     7,    14,    13,
       5,    34,    17,    16,    20,    21,    22,    19,    24,    23,
      26,    27,    29,    30,    36
  };

  const signed char
  ParaCL_Parser::yypgoto_[] =
  {
     -21,   -21,    54,    45,   -21,   -21,    -6,     5,   -21,    14,
      38,    12,    -5,   -21
  };

  const signed char
  ParaCL_Parser::yydefgoto_[] =
  {
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21
  };

  const unsigned char
  ParaCL_Parser::yytable_[] =
  {
      26,     1,    28,     2,    31,    35,    36,    23,    22,    37,
      38,     3,     4,    29,    39,    40,     5,     3,     4,     6,
      50,    31,     5,    32,     7,     8,     1,    46,     2,    49,
       7,     8,    33,    34,    41,    42,     3,     4,    62,    63,
      24,     5,    30,     2,     6,    43,    44,    52,    53,     7,
       8,     3,     4,    60,    61,    47,     5,     3,     4,     6,
      27,    51,     5,    64,     7,     8,    45,     3,    25,    48,
       7,     8,     5,    54,    55,    56,    57,    58,    59,     0,
       7,     8
  };

  const signed char
  ParaCL_Parser::yycheck_[] =
  {
       5,     4,     7,     6,    10,     7,     8,     2,    28,    11,
      12,    14,    15,     8,    16,    17,    19,    14,    15,    22,
      23,    27,    19,    24,    27,    28,     4,    22,     6,    24,
      27,    28,     9,    10,    18,    19,    14,    15,    43,    44,
      25,    19,     0,     6,    22,    20,    21,    33,    34,    27,
      28,    14,    15,    41,    42,    24,    19,    14,    15,    22,
       6,    29,    19,    29,    27,    28,    21,    14,    15,    26,
      27,    28,    19,    35,    36,    37,    38,    39,    40,    -1,
      27,    28
  };

  const unsigned char
  ParaCL_Parser::yystos_[] =
  {
       0,     4,     6,    14,    15,    19,    22,    27,    28,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    28,    37,    25,    15,    42,    32,    42,    37,
       0,    36,    24,     9,    10,     7,     8,    11,    12,    16,
      17,    18,    19,    20,    21,    33,    37,    24,    26,    37,
      23,    29,    39,    39,    40,    40,    40,    40,    40,    40,
      41,    41,    42,    42,    29
  };

  const unsigned char
  ParaCL_Parser::yyr1_[] =
  {
       0,    30,    31,    32,    32,    33,    33,    33,    34,    35,
      36,    36,    37,    37,    37,    38,    38,    38,    39,    39,
      39,    39,    39,    39,    39,    40,    40,    40,    41,    41,
      41,    42,    42,    42,    42,    42,    43
  };

  const unsigned char
  ParaCL_Parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     3,     2,     3,     1,     2,
       1,     1,     1,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     2,     2,     3,     1,     4
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const ParaCL_Parser::yytname_[] =
  {
  "$end", "error", "$undefined", "WHILE", "IF", "ELSE", "PRINT",
  "LESS_EQ", "GRT_EQ", "AND", "OR", "NOT_EQUAL", "EQUAL", "ERROR",
  "NUMBER", "ID", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'{'", "'}'",
  "';'", "'='", "'?'", "'!'", "'('", "')'", "$accept", "PROGRAM", "OPS",
  "OP1", "OP2", "ifscope", "OP", "EXPR", "EXPR_L", "EXPR1", "EXPR2",
  "TERM", "VAL", "ifexpr", YY_NULLPTR
  };


  const unsigned char
  ParaCL_Parser::yyrline_[] =
  {
       0,    96,    96,   104,   105,   111,   112,   114,   119,   125,
     142,   143,   147,   148,   155,   165,   166,   167,   170,   171,
     172,   173,   174,   175,   176,   179,   180,   181,   184,   185,
     186,   189,   190,   191,   192,   193,   203
  };

  // Print the state stack on the debug stream.
  void
  ParaCL_Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  ParaCL_Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  ParaCL_Parser::token_number_type
  ParaCL_Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    27,     2,     2,     2,     2,     2,     2,
      28,    29,    20,    18,     2,    19,     2,    21,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    24,
      16,    25,    17,    26,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    22,     2,    23,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15
    };
    const unsigned int user_token_number_max_ = 270;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 1553 "pcl_parser.tab.cpp" // lalr1.cc:1167
#line 210 "pcl_parser.ypp" // lalr1.cc:1168


namespace yy {

    ParaCL_Parser::token_type yylex(ParaCL_Parser::semantic_type* yylval, ParaCL_Parser::location_type* yylloc,
                             ParaCL_Driver* driver) {
      return driver->yylex(yylval, yylloc);
    }

    void ParaCL_Parser::error(const location_type&, const std::string&){}

}
