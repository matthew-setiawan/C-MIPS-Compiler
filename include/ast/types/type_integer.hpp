class integer : public types
{
	private:
		datatype _datatype;
		int value;

	public:
		integer (int _value){
			value=_value;
			_datatype = INT;
		}
		virtual double evaluate() const override {
			return value; 
		};
		virtual void generateMIPS(std::ostream &file, root& context) const override{
			file <<"#SP"<<context.retSP()<<std::endl;
			file << "nop" <<std::endl;
			file << "li $2, 0" << std::endl;
			file << "li $2, " << value << std::endl;
			file << "sw $2," << context.retSP() << "($30)" << std::endl;
			std::cout<<context.retSP()<<std::endl;
		}

};
