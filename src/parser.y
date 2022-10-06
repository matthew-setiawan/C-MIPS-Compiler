%define parse.error verbose 

%code requires
{
	#include "ast.hpp"
	extern const Node *basis; 
	int yylex(void);
	void yyerror(const char *);

}
%union
{
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

}
%token DEF_OP_PAREN DEF_CLO_PAREN DEF_SWT DEF_F_VAL DEF_F_OP DEF_ARR_L DEF_ARR_R  DEF_COL DEF_END_LINE DEF_COMM DEF_FLT DEF_INT DEF_TWO_AND DEF_TWO_OR DEF_LSR DEF_LSL DEF_TIMES DEF_ADD DEF_FRACT DEF_SUB DEF_EQ DEF_NUMBER DEF_LETTER DEF_UNS DEF_PEQL DEF_PLUS_PLUS DEF_MEQL
%token DEF_AND DEF_ENUMERATOR DEF_OR DEF_XOR DEF_I_EL DEF_D_EL DEF_U_EL DEF_CH_EL DEF_OP_FUNC DEF_IF DEF_ELS DEF_WH_OP DEF_CNT DEF_B DEF_R_OP DEF_NORM DEF_SEL_STATE DEF_CLO_FUNC DEF_LARGER DEF_GEQ DEF_SMALLER DEF_IDENT DEF_SZ DEF_EMPTY DEF_LEQ DEF_DOUB_EQ DEF_NE DEF_MIN_MIN 

%type <dlv> start_dec_list enumerator_list
%type <idecn> declaration parameter_declaration 
%type <intval> 	 DEF_I_EL
%type <dubval> 	 DEF_D_EL 
%type <uval> DEF_U_EL
%type <vld> declaration_list parameter_list
%type <ilst> initialisation_list
%type <node> begin_comp function_definition global_declaration enum_definition
%type <decn> declarator enumerator_declarator enumerator_initialisation specify_decl 
%type <alv> argument_list
%type <tnode> TYPE 
%type <idecn> enumerator
%type <slv> statement_list
%type <fval> 	 DEF_F_VAL
%type <sn> jump_statement compound_statement expression_statement statement control_flow_logic  labeled_statement
%type <exprn> logical_expression  primary_expression unary_expression postfix_expression  assignment_expression log_bitwise parse_l_ANDOR multiply_expression bitwise_shift_expression compare_expression equal_expression add_expression 
%type <string> DEF_IDENT DEF_INT DEF_R_OP DEF_FLT DEF_UNS DEF_CH_EL

%start ROOT
%%
ROOT 	: begin_comp {basis = $1;}

global_declaration:enumerator	{$$ = $1;}
			|function_definition{$$ = $1;}
			|declaration {$$ = $1;}

postfix_expression:primary_expression	
			|postfix_expression DEF_PLUS_PLUS{ $$ = new directa($1, new Arithmetic_Operation_Expressions($1, new integer(1),"add"));}
			|postfix_expression DEF_MIN_MIN{ $$ = new directa($1, new Arithmetic_Operation_Expressions($1, new integer(1),"sub"));}
			|postfix_expression DEF_OP_PAREN argument_list DEF_CLO_PAREN{ $$ = new returnfuncval($1, $3);}
			|postfix_expression DEF_ARR_L assignment_expression DEF_ARR_R{ $$ = new array_indexing($1, $3);}
			|postfix_expression DEF_OP_PAREN DEF_CLO_PAREN{ $$ = new returnfuncval($1);}

function_definition:TYPE DEF_IDENT DEF_OP_PAREN parameter_list DEF_CLO_PAREN compound_statement { $$ = new definefunction($1, *$2, $4, $6);delete $2;} 

declaration :TYPE DEF_END_LINE{ $$ = new declarator(*$1); delete $1; }
		| TYPE start_dec_list DEF_END_LINE { $$ = new declarator(*$1, $2); delete $1; }

declaration_list:declaration{ $$ = new std::vector<declarator*>(1, $1);} 
		| declaration_list declaration  { $1->push_back($2); $$ = $1; }

initialisation_list:assignment_expression { $$ = new std::vector<exprr*>(1, $1);	}
			|initialisation_list DEF_COMM assignment_expression { $1->push_back($3); $$=$1; }
								
parameter_declaration:TYPE declarator { $$ = new declarator(*$1, new std::vector<declare*>(1, $2)); delete $1;}	
								
parameter_list:parameter_declaration { $$ = new std::vector<declarator*>(1, $1); }
		|parameter_list DEF_COMM parameter_declaration 	{ $1->push_back($3); $$ = $1; }
		| { $$ = nullptr; }

declarator	: DEF_IDENT { $$ = new decvar(*$1, 0); delete $1;}
		| DEF_IDENT DEF_ARR_L DEF_ARR_R { $$ = new decarray(*$1, nullptr); delete $1; }
		| DEF_IDENT DEF_ARR_L assignment_expression DEF_ARR_R	{ $$ = new decarray(*$1, $3);delete $1; }
		|DEF_IDENT DEF_OP_PAREN parameter_list DEF_CLO_PAREN{ $$ = new declarefunction(*$1, $3);delete $1; }

specify_decl: declarator { $$ = $1; }
		|declarator DEF_EQ DEF_OP_FUNC DEF_CLO_FUNC{ $$ = new array_declaration($1, new std::vector<exprr*>); }
		| declarator DEF_EQ DEF_OP_FUNC initialisation_list DEF_CLO_FUNC { $$ = new array_declaration($1, $4); }
		| declarator DEF_EQ assignment_expression { $$ = new variable_initialization($1, $3); }

start_dec_list: specify_decl 	{ $$ = new std::vector<declare*>(1, $1);	}
		|start_dec_list DEF_COMM specify_decl{ $1->push_back($3); $$ = $1; }

enumerator:	TYPE DEF_IDENT DEF_OP_FUNC enumerator_list DEF_CLO_FUNC DEF_END_LINE { $$ = new declarator(*$1, $4);delete $1; } 
		
primary_expression: DEF_I_EL{ $$ = new integer($1); }
			|DEF_F_VAL{ $$ = new floatv($1); }
			|DEF_CH_EL{ $$ = new character(*$1); delete $1;}
			|DEF_D_EL { $$ = new doublev($1); }	
			|DEF_U_EL { $$ = new unsignedint($1); }
			| DEF_IDENT	{ $$ = new identf(*$1);	delete $1;}	
			| DEF_OP_PAREN assignment_expression DEF_CLO_PAREN{ $$ = $2; }						
			|DEF_SZ DEF_OP_PAREN TYPE DEF_CLO_PAREN{ $$ = new typesize(*$3); delete $3;}	
			|DEF_SZ DEF_OP_PAREN DEF_IDENT DEF_CLO_PAREN{ $$ = new varsize(*$3); delete $3;}

enumerator_list: 	enumerator_initialisation{ $$ = new std::vector<declare*>(1, $1); }
			| enumerator_list DEF_COMM enumerator_initialisation{ $1->push_back($3); $$ = $1; }

enumerator_initialisation: 	enumerator_declarator DEF_EQ assignment_expression{ $$ = new declareenum($1, $3); }		
					|enumerator_declarator{ $$ = new declareenum($1); }

enumerator_declarator: 	DEF_IDENT{ $$ = new decvar(*$1, 0); delete $1;}
									
unary_expression: postfix_expression			
			|	DEF_TIMES unary_expression { $$ = new unref($2); }
			|	DEF_SUB unary_expression { $$ = new negexpr($2); }
			|   DEF_AND unary_expression { $$ = new ref($2); }
			|	DEF_PLUS_PLUS unary_expression { $$ = new directa($2, new Arithmetic_Operation_Expressions($2, new integer(1),"add")); }
			|	DEF_MIN_MIN unary_expression { $$ = new directa($2, new Arithmetic_Operation_Expressions($2, new integer(1),"sub")); }

multiply_expression:	unary_expression	{ $$ = $1; }
			| 	multiply_expression DEF_TIMES unary_expression { $$ = new Arithmetic_Operation_Expressions($1, $3,"mul"); }
			| 	multiply_expression DEF_FRACT postfix_expression { $$ = new Arithmetic_Operation_Expressions($1, $3,"div"); }

add_expression	: 	multiply_expression{ $$ = $1; }
			| 	add_expression DEF_ADD multiply_expression{ $$ = new Arithmetic_Operation_Expressions($1, $3, "add"); }
			| 	add_expression DEF_SUB multiply_expression { $$ = new Arithmetic_Operation_Expressions($1, $3, "sub"); }

bitwise_shift_expression:add_expression
			|	bitwise_shift_expression DEF_LSL add_expression { $$ = new Shift_Expressions($1, $3, "left"); }
			|	bitwise_shift_expression DEF_LSR add_expression{ $$ = new Shift_Expressions($1, $3, "right"); }

compare_expression: 	bitwise_shift_expression
			|	compare_expression DEF_SMALLER bitwise_shift_expression{ $$ = new Comparison_Operators($1, $3, "less_than"); }
			|	compare_expression DEF_LEQ bitwise_shift_expression{ $$ = new Comparison_Operators($1, $3, "less_than_equal"); }
			|	compare_expression DEF_LARGER bitwise_shift_expression{ $$ = new Comparison_Operators($1, $3, "more_than"); }
			|	compare_expression DEF_GEQ bitwise_shift_expression{ $$ = new Comparison_Operators($1, $3, "more_than_equal"); }

equal_expression: 	compare_expression 
			|	equal_expression DEF_DOUB_EQ compare_expression	{ $$ = new Comparison_Operators($1, $3, "equal"); }
			|	equal_expression DEF_NE compare_expression{ $$ = new Comparison_Operators($1, $3, "not_equal"); }

log_bitwise	: 	equal_expression {$$ = $1; }
			| log_bitwise DEF_AND equal_expression{ $$ = new Bitwise_Operation_Expressions($1, $3, "bit_and"); }
			| log_bitwise DEF_XOR equal_expression{ $$ = new Bitwise_Operation_Expressions($1, $3, "bit_xor"); }
			| log_bitwise DEF_OR equal_expression{ $$ = new Bitwise_Operation_Expressions($1, $3, "b_or"); }

parse_l_ANDOR:	log_bitwise {$$ = $1; }
			|parse_l_ANDOR DEF_TWO_AND log_bitwise { $$ = new Logical_Operation_Expressions($1, $3, "log_and"); }
			|parse_l_ANDOR DEF_TWO_OR log_bitwise{ $$ = new Logical_Operation_Expressions($1, $3, "log_or"); }

assignment_expression: 	parse_l_ANDOR 
			|	unary_expression DEF_EQ assignment_expression { $$ = new directa($1, $3); }	
			|	unary_expression DEF_PEQL assignment_expression{ $$ = new directa($1, new Arithmetic_Operation_Expressions($1, $3, "add")); }	
			|	unary_expression DEF_MEQL assignment_expression { $$ = new directa($1, new Arithmetic_Operation_Expressions($1, $3, "sub")); }	

statement_list : 	statement { $$ = new std::vector<statement_c*>(1, $1); }
		| 	statement_list statement{ $1->push_back($2); $$ = $1; }

argument_list: 	assignment_expression{ $$ = new std::vector<exprr*>(1, $1); }
		| 	argument_list DEF_COMM assignment_expression { $1->push_back($3); $$ = $1; }

statement: 	jump_statement{ $$ = $1; }
	| 	compound_statement{ $$ = $1; }
	| 	expression_statement{ $$ = $1; }
	| 	control_flow_logic{ $$ = $1; }
	|	labeled_statement{ $$ = $1; }

jump_statement: DEF_R_OP DEF_END_LINE{ $$ = new jump(); }
		|	DEF_B DEF_END_LINE { $$ = new Break_Statement(1); }
		|	DEF_CNT DEF_END_LINE{ $$ = new Break_Statement(0); }
		| 	DEF_R_OP assignment_expression DEF_END_LINE{ $$ = new jump($2); }

compound_statement : DEF_OP_FUNC DEF_CLO_FUNC{ $$ = new comps(); }
			| DEF_OP_FUNC statement_list DEF_CLO_FUNC	{ $$ = new comps(NULL, $2); }
			| DEF_OP_FUNC declaration_list DEF_CLO_FUNC{ $$ = new comps($2, NULL); }
			| DEF_OP_FUNC declaration_list statement_list DEF_CLO_FUNC{ $$ = new comps($2, $3); }		

begin_comp : 	global_declaration{ $$ = $1; }
		| 	begin_comp global_declaration  { $$ = new misc($1,$2); }

expression_statement: assignment_expression DEF_END_LINE{ $$ = new expression($1); }
			|DEF_END_LINE{ $$ = new expression(); }

control_flow_logic :DEF_IF DEF_OP_PAREN assignment_expression DEF_CLO_PAREN statement{ $$ = new if_s($3,$5,$5,0); }	
			|DEF_IF DEF_OP_PAREN assignment_expression DEF_CLO_PAREN statement DEF_ELS statement { $$ = new if_s($3,$5,$7,1); }
			|DEF_SWT DEF_OP_PAREN assignment_expression DEF_CLO_PAREN statement{ $$ = new switch_s($3,$5); }	
			|DEF_WH_OP DEF_OP_PAREN assignment_expression DEF_CLO_PAREN statement { $$ = new forloop($3,$3,$3,$5,1); }
			|DEF_F_OP DEF_OP_PAREN assignment_expression DEF_END_LINE assignment_expression DEF_END_LINE assignment_expression DEF_CLO_PAREN statement { $$ = new forloop($3,$5,$7,$9,0); }

labeled_statement	:DEF_SEL_STATE assignment_expression DEF_COL statement{ $$ = new case_s($2, $4); }
			| DEF_NORM DEF_COL statement{ $$ = new default_s($3); } 
	
TYPE	:DEF_INT { $$ = new type_def(INT); }
		|DEF_EMPTY{ $$ = new type_def(VOID); } 
		|DEF_UNS DEF_INT{ $$ = new type_def(UNSIGNED_INT); } 	
		|DEF_ENUMERATOR{ $$ = new type_def(INT); } 	
		|DEF_LETTER	{ $$ = new type_def(CHAR); } 		
		|DEF_NUMBER	{ $$ = new type_def(DOUBLE); } 	
		| TYPE DEF_TIMES { $$ = new type_def("POINTER", *$1); delete $1;}	
		|DEF_FLT{ $$ = new type_def(FLOAT); } 	
		|DEF_UNS{ $$ = new type_def(UNSIGNED_INT); } 		
								
%%

const Node *basis; 

const Node* parseAST()
{
	basis = 0;
	yyparse ();
	return basis;
}