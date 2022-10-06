class declare : public maindec 
{
	public:
		virtual int getVarAddress() {return 0; }
		virtual std::string getVarName() { return ""; }
		virtual int getVarSize() { return 0; }
      
};

class declarator : public maindec
{
	private:
		std::vector<declare*>* param;
		type_def varType;
		bool isPointer = 0;
		datatype varTypeT = INT;

	public:
		declarator(type_def _varType, std::vector<declare*>* _param = NULL)
		: varType(_varType), isPointer(_varType.getIsPointer()), param(_param), varTypeT(_varType.getVarType()){}
            datatype get_type() { return varTypeT; }
		virtual void generateMIPS(std::ostream &file, root& context) const override{
			for (int i = 0; i < param->size(); i++){		
				(*param->at(i)).generateMIPSdeclare(file, context, varType, isPointer);					
			}
		}
		bool isPointerC() {return isPointer; }
		virtual std::string get_parameter() { return ((*param).at(0))->getVarName(); }
};
