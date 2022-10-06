class forloop : public statement_c
{
	private:
		int opt;
		exprr* condition;
		exprr* increment;
		statement_c*	statement;
		exprr* initial;
		
	public:
		forloop (exprr* _init_expr, exprr* _condition_expression, exprr* _update_expression, statement_c* _true_statement, int _opt)
		: initial(_init_expr),condition(_condition_expression), increment(_update_expression), statement(_true_statement), opt(_opt){}

		virtual void generateMIPS(std::ostream& file, root& context) const override{
			if(opt==0){
				std::string open = makeName("foropen");
				std::string exit = makeName("forclose");
				initialize(file,context,initial,0);
				file << open << ":" << std::endl;
				context.modify_stack('-');
				initialize(file,context,condition,1);
				file << "lw $4," << context.retSP() << "($30)" << std::endl;
				context.modify_stack('+');
				file << "beq $0,$4," << exit << std::endl;
				statement->generateMIPS(file, context);
				initialize(file,context,increment,0);
				file << "b "<< open << std::endl;
				file << exit << ":" << std::endl;
			}
			else{
				std::string open = makeName("whileopen");
				std::string exit = makeName("whileclose");

				file << open << ":\n" << "lw $4," << context.retSP() - 4 << "($30)" << std::endl; 

				initialize(file,context,condition,0);

				file << "beq $0, $2," << exit << std::endl; //branch to exit

				context.modify_stack('-');
				statement->generateMIPS(file, context); //run statement
				context.modify_stack('+');

				file << "b " << open << std::endl; //go back to start

				file << exit << ":" << std::endl; //exit loop
			}
		}

};

class Break_Statement : public statement_c{
	public:
		int breaktrue;
	public:
		Break_Statement(int _breaktrue) {breaktrue=_breaktrue;}
		virtual void generateMIPS(std::ostream& file, root& context) const override{
			if(breaktrue){
				file << "b " << context.getBreakFront() << std::endl;
			}
			else{
				file << "b "<< context.getContinueFront() << std::endl;
			}
		}
};
