#ifndef main_statements
#define main_statements

static int initialize(std::ostream& file, root& context, exprr* i, int opt){
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
			return 0;
		}

typedef const statement_c* state_;

#include <iomanip>
#include "expressionstatement.hpp"
#include "compoundstatement.hpp"
#include "ifstatement.hpp"
#include "controlflow.hpp"
#include "jump.hpp"
#include "switch.hpp"
#include "case.hpp"
#include "default.hpp"

#endif