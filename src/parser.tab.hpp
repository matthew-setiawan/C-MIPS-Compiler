/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_SRC_PARSER_TAB_HPP_INCLUDED
# define YY_YY_SRC_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 4 "src/parser.y" /* yacc.c:1909  */

	#include "ast.hpp"
	extern const Node *basis; 
	int yylex(void);
	void yyerror(const char *);


#line 52 "src/parser.tab.hpp" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    DEF_OP_PAREN = 258,
    DEF_CLO_PAREN = 259,
    DEF_SWT = 260,
    DEF_F_VAL = 261,
    DEF_F_OP = 262,
    DEF_ARR_L = 263,
    DEF_ARR_R = 264,
    DEF_COL = 265,
    DEF_END_LINE = 266,
    DEF_COMM = 267,
    DEF_FLT = 268,
    DEF_INT = 269,
    DEF_TWO_AND = 270,
    DEF_TWO_OR = 271,
    DEF_LSR = 272,
    DEF_LSL = 273,
    DEF_TIMES = 274,
    DEF_ADD = 275,
    DEF_FRACT = 276,
    DEF_SUB = 277,
    DEF_EQ = 278,
    DEF_NUMBER = 279,
    DEF_LETTER = 280,
    DEF_UNS = 281,
    DEF_PEQL = 282,
    DEF_PLUS_PLUS = 283,
    DEF_MEQL = 284,
    DEF_AND = 285,
    DEF_ENUMERATOR = 286,
    DEF_OR = 287,
    DEF_XOR = 288,
    DEF_I_EL = 289,
    DEF_D_EL = 290,
    DEF_U_EL = 291,
    DEF_CH_EL = 292,
    DEF_OP_FUNC = 293,
    DEF_IF = 294,
    DEF_ELS = 295,
    DEF_WH_OP = 296,
    DEF_CNT = 297,
    DEF_B = 298,
    DEF_R_OP = 299,
    DEF_NORM = 300,
    DEF_SEL_STATE = 301,
    DEF_CLO_FUNC = 302,
    DEF_LARGER = 303,
    DEF_GEQ = 304,
    DEF_SMALLER = 305,
    DEF_IDENT = 306,
    DEF_SZ = 307,
    DEF_EMPTY = 308,
    DEF_LEQ = 309,
    DEF_DOUB_EQ = 310,
    DEF_NE = 311,
    DEF_MIN_MIN = 312
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 12 "src/parser.y" /* yacc.c:1909  */

	double intval;
	std::vector<exprr*>* alv;
	std::vector<statement_c*>* slv;
	std::vector<exprr*>* ilst;
	std::vector<declarator*>* vld;
	std::vector<declare*>* dlv;
	std::string *string;
	declarator 	*idecn;
	statement_c *sn;
	exprr *exprn;
	const Node *node;
	declare *decn;
	type_def *tnode;
	double fval;
	double uval;
	double dubval;


#line 142 "src/parser.tab.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PARSER_TAB_HPP_INCLUDED  */
