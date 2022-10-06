class character : public types
{
	private:
		std::string value;
		datatype _type;
	public:
		character (std::string _value){
			value = _value;
			_type = CHAR;
		}
		virtual void generateMIPS(std::ostream &file, root& context) const override{
			file<<"##SHOULDN'T BE"<<std::endl;
			std::cout<<value<<std::endl;
			file << "nop" <<std::endl;
			file << "li $v0, " << value << std::endl;
		}
};