#ifndef main_expressions
#define main_expressions

#include <string>
#include <iostream>
#include <map>

#include "../declarators/declarators.hpp"

class exprr : public Node 
{
	private:
		exprr* left;
		exprr* right;
	public:
		virtual datatype _getVarType(root& context) const { 
			std::cout<<"Default"<<std::endl;
			return INT;
		};
		virtual bool getIsPointer(root& context) const { 
			std::cout<<"Default"<<std::endl;
			return 0; 
		};
		virtual long calcS(root *context, exprr* node) const{
			long tmp=4;
			if(left!=nullptr)   {
				tmp+=calcS(context,left);
			}
			if(right!=nullptr)  {
				tmp+=calcS(context,right);
			}	
            	return tmp;	
        	}
		virtual void loadWordVar(std::ostream &file, root& context) const {
			std::cout<<"Default"<<std::endl;
		};
		virtual type_def _getTypeDef(root& context) const {
			std::cout<<"Default"<<std::endl;
		};
		virtual std::string getVarName() const {
			std::cout<<"Default"<<std::endl;
			return 0; 
		};
		virtual double evaluate() const { 
			std::cout<<"Default"<<std::endl;
		};
};

typedef const exprr* exprr_;

#include "unary.hpp"
#include "sizeof.hpp"
#include "preneg.hpp"
#include "return.hpp"
#include "array.hpp"
#include "reference.hpp"
#include "assignment.hpp"
#include "operations.hpp"
#endif