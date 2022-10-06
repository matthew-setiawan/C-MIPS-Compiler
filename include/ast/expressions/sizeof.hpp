class typesize : public exprr
{
	private:
		datatype sizeof_type;
		
	public:

		virtual void generateMIPS(std::ostream &file, root& context) const override{
			context.type(file,sizeof_type);
		}
		typesize(type_def _sizeof_type) 
		: sizeof_type(_sizeof_type.getVarType()) {}

};

class varsize : public exprr
{
	private:
		std::string variable_name;

	public:
		virtual void generateMIPS(std::ostream &file, root& context) const override{
			context.type(file, context.getVar(variable_name).getTypeVar());
		}
		varsize(std::string _variable_name) 
		: variable_name(_variable_name) {}

};