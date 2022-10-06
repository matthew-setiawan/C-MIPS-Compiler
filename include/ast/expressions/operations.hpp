class Operator : public exprr
{
	protected:
		exprr_ right=nullptr;
		exprr_ left=nullptr;

	public:
		static bool non_int (datatype type,std::ostream &file, int fp1){
			switch (type){
				case FLOAT:
					file << "lwc1 $f0," << fp1 << "($30)" << std::endl;
					return true;
					break;
				case DOUBLE:
					file << "lwc1 $f0," << fp1 << "($30)" << std::endl;
					return true;
					break;
			}
			return false;

		}

		virtual void generateMIPS(std::ostream &file, root& context) const override{
			int fp1 = context.retSP();
			left->generateMIPS(file, context);
			context.modify_stack('-'); 
			int fp2 = context.retSP();
			right->generateMIPS(file, context);
			context.modify_stack('+');
			file << "lw $2," << fp1 << "($30)" << std::endl;
			file << "lw $8," << fp2 << "($30)" << std::endl;
			execute(file, context, left->_getVarType(context), "$2", "$8");
			file << "sw $2," << fp1 << "($30)" << std::endl;
			non_int(left->_getVarType(context),file,fp1);
		}

		virtual void execute(std::ostream &file, root& context, datatype type, std::string destination_register, std::string temprorary_register) const {}

		virtual datatype _getVarType(root& context) const override { return datatype(left->_getVarType(context)); };

		virtual bool getIsPointer(root& context) const { return left->getIsPointer(context); };
		Operator (exprr_ _left, exprr_ _right) : left (_left), right (_right) {}

};

class Arithmetic_Operation_Expressions:
public Operator
{
	std::string operation;

	public:
		virtual void execute(std::ostream &file, root& context, datatype type, std::string dest_reg, std::string tmp_out) const override{
			if (operation == "add"){
				if (type==FLOAT){
					file << "mtc1 "  << dest_reg << ",$f0" << std::endl;
					file << "mtc1 "  << tmp_out << ",$f1" << std::endl;
					file << "add.s $f0,$f0,$f1" << std::endl;
					file << "mfc1 "  << dest_reg << ",$f0" << std::endl;
				}
				else if (type==DOUBLE){
					file << "mtc1 "  << dest_reg << ",$f2" << std::endl;
					file << "mtc1 "  << tmp_out << ",$f0" << std::endl;
					file << "add.d $f0,$f2,$f0" << std::endl;
					file << "mfc1 "  << dest_reg << ",$f0" << std::endl;
				}else{
					file << "addu " << dest_reg << "," << dest_reg << "," << tmp_out << std::endl;
				}
			}
			else if (operation=="sub"){
				if (type==INT){
					file << "subu " << dest_reg << "," << dest_reg << "," << tmp_out << std::endl;
				}else if (type == DOUBLE){
					file << "mtc1 "  << dest_reg << ",$f2" << std::endl;
					file << "mtc1 "  << tmp_out << ",$f0" << std::endl;
					file << "sub.d $f0,$f2,$f0" << std::endl;
					file << "mfc1 "  << dest_reg << ",$f0" << std::endl;


				}
				else if (type==FLOAT){
					file << "mtc1 " << dest_reg << ",$f0" << std::endl;
					file << "mtc1 " << tmp_out << ",$f1" << std::endl;
					file << "sub.s $f0,$f0,$f1" << std::endl;
					file << "mfc1 " << dest_reg << ",$f0" << std::endl;
				}
			}
			else if (operation == "mul"){

				if (type==FLOAT){
					file << "mtc1 " << dest_reg << ",$f0" << std::endl;
					file << "mtc1 " << tmp_out << ",$f1" << std::endl;
					file << "mul.s $f0,$f0,$f1" << std::endl;
					file << "mfc1 " << dest_reg << ",$f0" << std::endl;
				}
				else if (type==DOUBLE){
					file << "mtc1 "  << dest_reg << ",$f2" << std::endl;
					file << "mtc1 "  << tmp_out << ",$f0" << std::endl;
					file << "mul.d $f0,$f2,$f0" << std::endl;
					file << "mfc1 "  << dest_reg << ",$f0" << std::endl;
				}else{
					file << "multu "  << dest_reg << "," << tmp_out << std::endl;
					file << "mflo "  << dest_reg << std::endl;
				}
			}
			else if (operation == "div"){
				if (type==INT){
					file << "divu " << dest_reg << "," << dest_reg << "," << tmp_out << std::endl;
					file << "mfhi " << dest_reg << std::endl;
					file << "mflo " << dest_reg << std::endl;
				}
				else if (type==FLOAT){
					file << "mtc1 " << dest_reg << ",$f0" << std::endl;
					file << "mtc1 " << tmp_out << ",$f1" << std::endl;
					file << "div.s $f0,$f0,$f1" << std::endl;
					file << "mfc1 " << dest_reg << ",$f0" << std::endl;
				}else if (type == DOUBLE){
					file << "mtc1 "  << dest_reg << ",$f2" << std::endl;
					file << "mtc1 "  << tmp_out << ",$f0" << std::endl;
					file << "div.d $f0,$f2,$f0" << std::endl;
					file << "mfc1 "  << dest_reg << ",$f0" << std::endl;
				}
			}
		}
		virtual double evaluate() const override {
			if (operation=="add"){
				return left->evaluate() + right->evaluate(); 
			}
			else if(operation=="sub"){
				return left->evaluate() - right->evaluate(); 
			}
			else if(operation=="mul"){
				return left->evaluate() * right->evaluate(); 
			}
			else if(operation=="div"){
				return left->evaluate() / right->evaluate(); 
			}
		};
		Arithmetic_Operation_Expressions (exprr_ _left, exprr_ _right, std::string _operation) : 
		Operator (_left, _right) 
		{
			operation = _operation;
		}

};

class Comparison_Operators:
public Operator
{
	std::string operation;
	public:
		Comparison_Operators(exprr_ _left, exprr_ _right, std::string _operation):
			Operator (_left,_right)
		{
			operation = _operation;
		}
		virtual void execute(std::ostream &file, root& context, datatype type, std::string dest_reg, std::string tmp_out) const override{
			if (operation == "equal"){
				file<<"xor "<<dest_reg<<","<<dest_reg<<","<<tmp_out<<std::endl;
				file<<"sltu "<<dest_reg<<","<<dest_reg<<","<<1<<std::endl;
			}
			else if (operation == "not_equal"){
				file<<"xor "<<dest_reg<<","<<dest_reg<<","<<tmp_out<<std::endl;
				file<<"sltiu "<<dest_reg<<","<<0<<","<<dest_reg<<std::endl;
			}
			else if (operation == "less_than"){
				file<<"slt "<<dest_reg<<","<<dest_reg<<","<<tmp_out<<std::endl;
			}
			else if (operation == "less_than_equal"){
				file<<"slt "<<dest_reg<<","<<tmp_out<<","<<dest_reg<<std::endl;
				file<<"xori "<<dest_reg<<","<<dest_reg<<",1"<<std::endl;
				file<<"andi "<<dest_reg<<","<<dest_reg<<",255"<<std::endl;
			}
			else if (operation == "more_than_equal"){
				file<<"slt "<<dest_reg<<","<<dest_reg<<","<<tmp_out<<std::endl;
				file<<"xori "<<dest_reg<<","<<dest_reg<<",1"<<std::endl;
				file<<"andi "<<dest_reg<<","<<dest_reg<<",255"<<std::endl;
			}
			else if (operation == "more_than"){
				file<<"slt "<<dest_reg<<","<<tmp_out<<","<<dest_reg<<std::endl;
			}
		}
	
};

class Bitwise_Operation_Expressions:
public Operator
{
	std::string operation;
	public:
		Bitwise_Operation_Expressions(exprr_ _left, exprr_ _right,std::string _operation): 
			Operator (_left, _right) 
		{
			operation = _operation;

		}
		virtual void execute(std::ostream &file, root& context, datatype type, std::string dest_reg, std::string temprorary_register) const override{
			if (operation == "bit_and"){
				file<<"and "<<dest_reg<<","<<dest_reg<<","<<temprorary_register<<std::endl;
			}else if (operation == "b_or"){
				file<<"or "<<dest_reg<<","<<dest_reg<<","<<temprorary_register<<std::endl;
			}else if (operation == "bit_xor"){
				file<<"xor "<<dest_reg<<","<<dest_reg<<","<<temprorary_register<<std::endl;
			}
		}

};

class Logical_Operation_Expressions:
public Operator
{
	std::string operation;
	public:
		Logical_Operation_Expressions(exprr_ _left, exprr_ _right,std::string _operation): 
			Operator (_left, _right) 
		{
			operation = _operation;

		}
		virtual void execute(std::ostream &file, root& context, datatype type, std::string dest_reg, std::string temprorary_register) const override{
			if (operation == "log_and"){
				std::string label = "RETURN_" + std::to_string(context.addlabel());
				int tempsp = context.retSP();
				left->generateMIPS(file, context);
				file << "lw $2," << tempsp << "($30)" << std::endl;
				file << "beq " << dest_reg << ",$0," << label << std::endl;
				context.modify_stack('-');
				tempsp = context.retSP();
				right->generateMIPS(file,context);
				file << "lw $8," << tempsp << "($30)" << std::endl;
				context.modify_stack('+');
				file << "move " << dest_reg << "," << "$0" << std::endl;
				file << "beq $8,$0," << label << std::endl;
				file << "addiu "<< dest_reg << ",$0,1" << std::endl;
				file << "sw $2," << context.retSP() << "($30)" << std::endl;
			}
			else if (operation == "log_or"){
				context.addlabel();
				int tempsp1 = context.retSP();
				left->generateMIPS(file, context);
				file << "lw $2," << tempsp1 << "($30)" << std::endl;
				std::string label1 = "RETURN_" + std::to_string(context.addlabel());

				file << "bne " << dest_reg << ",$0," << label1 << std::endl;
				context.modify_stack('-');
				int tempsp2 = context.retSP();
				right->generateMIPS(file,context);
				file << "lw $8," << tempsp2 << "($30)" << std::endl;
				context.modify_stack('+');
				file << "move " << dest_reg << ",$0" << std::endl;				
				std::string label2 = "RETURN_" + std::to_string(context.addlabel());

				file << "beq $8,$0," << label2 << std::endl;
				file << "addiu "<< dest_reg << ",$0,1" << std::endl;
				file << label1 << ":" << std::endl; 
				file << "addiu " << dest_reg << ",$0,1" << std::endl;
				file << label2 << ":" << std::endl; 
				file << "sw $2," << tempsp1 << "($30)" << std::endl;

			}else if (operation == "xor"){
				//finish xor
			}
		}
};

class Shift_Expressions : public Operator
{
	std::string operation;
	public:
		Shift_Expressions(exprr_ _left, exprr_ _right, std::string _operation):
		Operator(_left,_right) {}
		virtual void execute(std::ostream &file, root& context, datatype type, std::string destination_register, std::string temprorary_register) const override{
			if (operation == "left"){
				file << "sllv "<< destination_register << "," << destination_register << "," << temprorary_register << std::endl;
			}
			else{
				char opt = 'l';
				if(type==INT){
					opt = 'v';
				}
				file << "sra" << opt << " " <<destination_register << "," << destination_register << "," << temprorary_register << std::endl;
			}
		}
};