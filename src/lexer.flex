%option noyywrap

%{
  #include "parser.tab.hpp"
%}

H			  [a-fA-F0-9]
E			  [Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*
D			  [0-9]
L			  [a-zA-Z_]



%%
"char"                              { return (DEF_LETTER); }
"double"                            { return (DEF_NUMBER); }
"float"                             { return (DEF_FLT); }
"unsigned"                          { return (DEF_UNS); }
"int"				                        { return (DEF_INT); }
 /*had a hunch about making operators with 2 equals before single equal to recognize longer tokens first*/
"+="				                      { return (DEF_PEQL); }
"++"				                      { return (DEF_PLUS_PLUS); }
"-="				                      { return (DEF_MEQL); }
"--"				                      { return (DEF_MIN_MIN); }
">>"                              { return (DEF_LSR); }
"<<"                              { return (DEF_LSL); }
"||"                              { return (DEF_TWO_OR); }
"=="                              { return (DEF_DOUB_EQ); }
">="				                      { return (DEF_GEQ); }
"&&"                              { return (DEF_TWO_AND); }
"!="				                      { return (DEF_NE);	}
"<="				                      { return (DEF_LEQ); }
 /*single length operator*/
"="                                 { return (DEF_EQ); }
"+"                                 { return (DEF_ADD); }
"*"                                 { return (DEF_TIMES); }
"-"                                 { return (DEF_SUB); }
">"                                 { return (DEF_LARGER); }
"<"                                { return (DEF_SMALLER); }
"/"                                 { return (DEF_FRACT); }
 /*control flow logic*/
"if"					                      { return (DEF_IF); }
"else"					                    { return (DEF_ELS); }
"while"					                    { return (DEF_WH_OP); }
"for"					                      { return (DEF_F_OP); }
"void"							                { return (DEF_EMPTY); }
"continue"				                  { return (DEF_CNT); }
"return"			  	                  { return (DEF_R_OP); }

 /* MISCELLANEOUS */
"switch"				                    { return (DEF_SWT); }
"case"                              { return (DEF_SEL_STATE); }
"enum"                              { return (DEF_ENUMERATOR); }
"break"					                    { return (DEF_B); }

"default"                           { return (DEF_NORM); }
"sizeof"                            { return (DEF_SZ); }
"("                                 { return (DEF_OP_PAREN); }
"["                                 { return (DEF_ARR_L); }
"{"                                 { return (DEF_OP_FUNC); }
":"                                 { return (DEF_COL); }
";"                                 { return (DEF_END_LINE); }
","                                 { return (DEF_COMM); }
"&"                                 { return (DEF_AND); }
"|"                                 { return (DEF_OR); }
"\^"                                { return (DEF_XOR); }
")"                                 { return (DEF_CLO_PAREN); }
"]"                                 { return (DEF_ARR_R); }
"}"                                 { return (DEF_CLO_FUNC); }

{L}({L}|{D})*                       { yylval.string  = new std::string(yytext); return DEF_IDENT; }
'[\x01-\x26\x28-\xff]'     { yylval.string= new std::string(yytext); return DEF_CH_EL; }
{D}+[.]{D}+{FS}           { yylval.fval = strtod(yytext, 0);     return DEF_F_VAL; }
{D}+"."{D}+[u|U]                { yylval.fval = strtod(yytext, 0);     return (DEF_U_EL); }
{D}+"."{D}+                     { yylval.fval = strtod(yytext, 0);     return DEF_D_EL; }
{D}+{IS}?							                  { yylval.intval   = (int)strtol(yytext, NULL, 0);     return DEF_I_EL; }
[ \t\r\n\f]+		                      { ; }
.                                   { fprintf(stderr, "Invalid token\n");       exit(1); }

%%

void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}

