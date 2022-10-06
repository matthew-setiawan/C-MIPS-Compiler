class unsignedint : public types
{
	private:
		unsigned int value;
		datatype _datatype;

	public:
		unsignedint (int _value){
			value = _value;
			_datatype = UNSIGNED_INT;
		}
		virtual double evaluate() const override { return value; };

		virtual datatype _getVarType(root& context) const override { return _datatype; };

		virtual void generateMIPS(std::ostream &file, root& context) const override
		{
			file << "##UNSIGNED DECLARED" << std::endl;
			file << "li $2, 0"<<std::endl;
			file << "nop" <<std::endl;
			file << "li $2, " << value << std::endl;
			file << "sw $2," << context.retSP() << "($30)" << std::endl;
		}
};