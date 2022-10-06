#include "../include/ast.hpp"

int main (int argc, char* argv[]){
	extern const Node* parseAST();
	extern FILE* yyin;
	if(argc >= 5){	
		yyin = fopen(argv[2], "r");
		std::ofstream yyout(argv[4], std::ofstream::out);
		root context;
		const Node* root = parseAST();
		root->generateMIPS(yyout, context);
		return 0;
	}
	else{
		std::cerr<<"Error Usage"<<std::endl;
		return 1;
	}
}