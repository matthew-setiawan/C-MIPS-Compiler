class decvar : public declare
{
	protected:
		std::string varName;
		bool isPointer;
	public:
		virtual std::string getVarName() {
			return varName;
		}

		virtual void generateMIPSdeclare(std::ostream &file, root& context, type_def decType, bool isPointer) const override{
			file << "sw $0," << context.newVar(varName, decType, DEFAULT, isPointer).getVarAdd() << "($30)" << std::endl;
		}
		virtual void generateMIPSinitialize(std::ostream &file, root& context, type_def decType, exprr* expressions, bool isPointer) const override{
			vars declared_variable = context.newVar(varName, decType, DEFAULT, isPointer);
			if(context.get_context_scope() == GLOBAL){
				file << ".globl " << varName << std::endl;
				file << ".data" << std::endl;
				file <<  varName  << ":" << std::endl;
				if (expressions != NULL){
					file << ".word " << expressions->evaluate() << std::endl;
				}
				else{
					file << ".word 0" << std::endl;
				}
			}
			else{
				initializedec(file,context,expressions,0);
                file << "li $8,0"<<std::endl;//reset location
				file << "lw $8," << context.retSP()-4 << "($30)" << std::endl;
				file << "sw $8," << declared_variable.getVarAdd() << "($30)" << std::endl;
			}
		}
		decvar(std::string _varName, bool _isPointer){
			varName = _varName;
			isPointer = _isPointer;
		}

};