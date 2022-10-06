#ifndef startif

#include <cassert>
#include <deque>
#include <memory>
#include <fstream>
#include <stdexcept>
#include <initializer_list>
#include <iomanip>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <regex>
#include <stack>

static int makeNameUnq = 0;
static std::map<std::string, std::string> label_declarations;
static std::map<std::string, std::string> label_variables;

static std::string makeName(std::string base){
    return ""+base+"_"+std::to_string(makeNameUnq++);
}


#include "enums.hpp"
#include "type_struct.hpp"
#include "variable_struct.hpp"
#include "root.hpp"

static void loadarrayval(std::ostream& file,int sp1, int sp2, int count, int opt){
	if(opt == 1){
		file << "lw $8," << sp2 << "($30)" << std::endl;
		file << "lw $4," << sp1 << "($30)" << std::endl;
		for(int i=0;i<count;i++){
			file << "sll $8,$8,1" << std::endl;
		}
		file << "addu $4,$4,$8" << std::endl;
		file << "sw $4," << sp1 << "($30)" << std::endl;
	}
	else if(opt==2){
		file << "lw $2," << sp1 << "($30)" << std::endl;
		file << "lw $2,0($2)" << std::endl;
		file << "sw $2," << sp1 << "($30)" << std::endl;
	}
	else if(opt==3){
		file << "lw $8," << sp2 << "($30)" << std::endl;
		file << "lw $2," << sp1 << "($30)" << std::endl;
		file << "sw $8,0($2)" << std::endl;
		file << "sw $8," << sp1 << "($30)" << std::endl;
	}
	else if(opt==4){
		file << "lw $2," << sp1 << "($30)" << std::endl;
		if (sp2 == 0){
			file << "sub $2,$0,$2" << std::endl; 
		}
		else if (sp2 == 1){
			file << "mtc1 $0,$f2" << std::endl;
			file << "mtc1 $2,$f0" << std::endl;
			file << "nop" << std::endl;
			file << "sub.s $f0,$f2,$f0" << std::endl; 
			file << "mfc1 $2,$f0" << std::endl;
		}
		file << "sw $2," << sp1 << "($30)" << std::endl;
	}
	else if(opt==5){
		file << "lw $2," << sp1 << "($30)" << std::endl;
		file << "lw $2,0($2)" << std::endl;
		file << "sw $2," << sp1 << "($30)" << std::endl;
	}
}

class Node{
	public:
		virtual void generateMIPS(std::ostream& file, root& context) const {}
};

typedef const Node* ptr;

#endif
