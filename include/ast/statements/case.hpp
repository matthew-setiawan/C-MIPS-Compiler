class case_s : public statement_c
{
	private:
		exprr* expression;
		exprr* left;
		exprr* right;
		statement_c* switch_statements;
		std::vector<declarator*>* param;

	public:

		static void cleft(std::ostream& file, root& context, std::vector<statement_c*>* right){
			auto temp = right->begin();
			while(1){
				if (temp==right->end()){
					break;
				}
				else{
					(*temp)->generateMIPS(file,context);
					temp=temp+1;
				}
			}
		}
		virtual void generateMIPS(std::ostream &file, root& context) const override{
			std::string case_label = makeName("case");
			context.newcase(expression, case_label);
			file << case_label << ":" << std::endl;
			switch_statements->generateMIPS(file, context);
		}
		case_s( exprr* _expression, statement_c* _switch_statements)
		: expression(_expression), switch_statements(_switch_statements),left(_expression),right(_expression){}

};
