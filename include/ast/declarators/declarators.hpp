#ifndef main_declarators
#define main_declarators
#include <iomanip>
#include "../expressions/expressions.hpp"

static int initializedec(std::ostream& file, root& context, exprr* i, int opt){
			if (i==NULL){
				return -1;
			}
			else if(opt==0){
				context.modify_stack('-');
				i->generateMIPS(file, context);
				context.modify_stack('+');
			}
			else if(opt==1){
				i->generateMIPS(file, context);
			}
                  else if(opt==2){
                        context.modify_stack('-');
				i->generateMIPS(file, context);
				context.modify_stack('-');
                  }
			else if(opt==3){
				return i->evaluate();
			}
			return 0;
}

static int evaluatedec(exprr* i, int opt){
			if (i==NULL){
				return -1;
			}
			else if(opt==0){
				return i->evaluate();
			}
			return 0;
}

#include "programdec.hpp"
#include "maindeclaration.hpp"
#include "declaration.hpp"
#include "declarevariable.hpp"
#include "array.hpp"
#include "variableinitialization.hpp"
#include "function.hpp"
#include "enum.hpp"

#endif