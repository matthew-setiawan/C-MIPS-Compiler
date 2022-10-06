class default_s : public statement_c
{
	private:
		exprr* expression;
		statement_c* statement;

	public:
		default_s(statement_c* _statement){
			statement = _statement;
			expression = NULL;
		}
		virtual void printdef(std::ostream &file, root& context) const{
			file<<"##statement:"<<std::endl;
			if(expression!=NULL) {
				expression->generateMIPS(file,context);
			}
			else{
				file<<";"<<std::endl;
			}
       	 }
		virtual void generateMIPS(std::ostream &file, root& context) const override{
			std::string n = makeName("default");
			context.newlabelc(n);
			file << n << ":" << std::endl;
			statement->generateMIPS(file, context);
		}
};
