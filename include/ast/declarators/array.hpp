class decarray: public declare
{
	private: 
		int size;
		std::string varName;


	public:
		decarray(std::string _varName, exprr *sizeExpr) {
			varName = _varName;
			size = evaluatedec(sizeExpr,0);
		}
		virtual void generateMIPSdeclare(std::ostream &file, root& context, type_def _type, bool a) const override {
			_type.modify_array('+');
			if(context.get_context_scope() == GLOBAL){
				vars newarray = context.newVar(varName, _type, ARRAY, 0, size);
				file << ".comm " << varName << " " << size*4 << std::endl;
				file << "nop" << std::endl;
			}
			else{
				vars newarray = context.newVar(varName, _type, ARRAY, 0, size);
				file << "sw $0," << newarray.getVarAdd()*4 << "($30)" << std::endl;
				file << "nop" << std::endl;
			}
			file << "nop" << std::endl;
		}
		virtual std::string getVarName() { return varName; }
		virtual int getVarSize() { return size; }
		virtual void generateMIPS(std::ostream &file, root& context) const override{
			vars array_variable = context.getVar(varName);
			switch (context.get_context_scope() == GLOBAL){
				case true:
				file << ".global" << varName <<"\n.data"  << std::endl;
				file << "nop" << std::endl;
				file <<  varName 	<< ":" << std::endl;
				file << "nop\n .space" << size*4 << std::endl;
				break;
			}
			file << "nop" << std::endl;
		}	
};

class array_declaration : public declare 
{
	protected:
		std::vector<exprr*>* expression;
		declare* declarer;

	public: 		

		virtual void generateMIPSdeclare(std::ostream &file, root& context, type_def _type, bool a) const override
		{
			declarer->generateMIPSinitializearray(file, context, _type, expression);
		}
		array_declaration(declare* _declarer, std::vector<exprr*>* _expression){
			declarer=_declarer;
			expression=_expression;
		}

};
