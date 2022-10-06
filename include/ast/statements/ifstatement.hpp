class if_s : public statement_c
{
	private:
		exprr* condition_expression;
		statement_c* true_statement;
		statement_c* false_statement;
		int opt;
		
	public:
		if_s (exprr* _condition_expression, statement_c* _true_statement,statement_c* _false_statement,int _opt)
		: condition_expression (_condition_expression), true_statement (_true_statement),false_statement(_false_statement),opt(_opt){}

		virtual void generateMIPS(std::ostream& file, root& context) const override{
			if(opt==0){
				initialize(file, context, condition_expression, 0);
				std::string exit = makeName("exit");
				file << "beq $0,$2," << exit << std::endl;
				true_statement->generateMIPS(file, context);
				file << exit << ":" << std::endl;
			}
			else{
				context.modify_stack('-');
				file << "##Here 1" << std::endl;
				condition_expression->generateMIPS(file, context);
				std::string branch_targ2 = makeName("jump_cond2");
				file << "lw $2,"<<context.retSP()<<"($30)"<<std::endl;
				context.modify_stack('3');//force override SP.
				file << "bne $0,$2," << branch_targ2 <<std::endl;
				file <<"##if_true->generateMIPS(dst,context)"<<std::endl;
				file <<"addu "<<"$t0"<<","<<"$2"<<","<<"$2"<<std::endl;//coding a no-op
				false_statement->generateMIPS(file,context);
				std::string branch_targ1 = makeName("jump_cond1");
				file <<"beq "<<"$0,$0,"<<branch_targ1<<std::endl;
				file <<"addu "<<"$t0"<<","<<"$2"<<","<<"$2"<<std::endl;//coding a no-op
				file <<branch_targ2<<":"<<std::endl;
				true_statement->generateMIPS(file ,context);
				file<<branch_targ1<<":"<<std::endl;	
			}
		}
};