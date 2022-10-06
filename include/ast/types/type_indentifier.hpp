class identf : public types
{
	private:
		exprr* Expression_Ptr;
		std::string varName;

	public:
		identf (std::string _varName){
			varName = _varName;
		}
		virtual std::string getVarName() const override { return varName;}; 
		virtual type_def _getTypeDef(root& context) const override { return context.getVar(varName).getTypeDef(); };
		virtual bool getIsPointer(root& context) const { return context.getVar(varName)._isPointer(); };
		virtual void loadWordVar(std::ostream &file, root& context) const override{
			if (context.getVar(varName).isGlobal()==false){
				file << "addiu $2,$30," << context.getVar(varName).getVarAdd() << std::endl;
				file << "sw $2," << context.retSP() << "($30)" << std::endl;
			}
			else{
				file << "nop" <<std::endl;
				file << "la $2," << varName << std::endl;
				file << "sw $2," << context.retSP() << "($30)" << std::endl;
			}
			if(context.getVar(varName).getTypeVar()==DOUBLE){
				context.modify_stack('+');
			}
			file << "nop" <<std::endl;
		}
		virtual void generateMIPS(std::ostream &file, root& context) const override{	
			int tempdest = context.retSP();
			loadWordVar(file, context);
			if(context.getVar(varName).getDecType() == ARRAY){
				file << "##array here" << std::endl;
			}
			else if(context.getVar(varName).getDecType() == ARRAY){
				file << "nop" <<std::endl;
				file << "li $0,10" << std::endl;
				file << "add $2,$30,$0" << std::endl;
				file << "add $2,$31,$0" << std::endl;
				file << "add $2,$32,$0" << std::endl;
				file << "li $0,0" <<std::endl;
			}
			else{
				file << "nop" <<std::endl;
				file << "lw $2,0($2)" << std::endl;
				file << "sw $2," << tempdest << "($30)" << std::endl;
			}
		}
		virtual datatype _getVarType(root& context) const { return context.getVar(varName).getTypeVar(); };
};