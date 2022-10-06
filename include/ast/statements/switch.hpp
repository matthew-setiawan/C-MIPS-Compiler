class switch_s : public statement_c
{
	private:
		exprr* expression;
		exprr* left;
		exprr* right;
		statement_c* my_switch;

	public:
		virtual void prettyPrint(std::ostream& file, root& context){
			left->generateMIPS(file,context);
			right->generateMIPS(file,context);
		}
		virtual void generateMIPS(std::ostream& file, root& context) const override{			
			std::string open = makeName("open");
			std::string exit = makeName("exit");
			context.addBreak(exit);
			std::stringstream flow; 
			my_switch->generateMIPS(flow, context);
			initialize(file,context,expression,2);
			int case_stack_pointer = context.retSP();
			for(int i=0; context.getCaseSize()!=0; i++){
				exprr* case_statement = context.getCaseTracker();
				case_statement->generateMIPS(file, context);
				std::string case_label = context.getCaseLabel();
				context.switchmain(file,context.retSP(), case_stack_pointer,case_label);
				context.popSwithRet(1);
				context.popLabelRet(1);
			}
			switch(context.isDefault()){
				case true:
					file << "li $0,0"<<std::endl;
					file << "beq $0,$0,"<< context.getCaseLabel() << std::endl;
					context.popLabelRet(1);
					break;
			}
			context.closeswitch(file,flow.str(),exit);
		}
		switch_s (exprr* _expression = NULL, statement_c* _my_switch = NULL)
		: expression(_expression), my_switch(_my_switch),left(_expression),right(_expression){}

};