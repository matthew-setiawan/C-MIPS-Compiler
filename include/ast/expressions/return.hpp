class returnfuncval : public unary
{
   private:
	std::vector<exprr*>* param;
	public:
		returnfuncval(exprr *_expression, std::vector<exprr*>* _argument_list = NULL)
		: unary(_expression), param(_argument_list) {}

		virtual void generateMIPS(std::ostream &file, root& context) const override{
			if(param == NULL){
				int temp = context.retSP();
				decnewvar(context,expression);
				context.closeretfunc(file, context.retSP(), 0, temp, expression->getVarName());
			}
			else{
				int temp = context.retSP();
				decnewvar(context,expression);
				int i = 0;
				while(i < param->size()){
					i+=1;
					context.modify_stack('-'); 
				}
				int tempsp1 = context.retSP();
				for (int i = 0; i < param->size(); i++){
					context.modify_stack('-');
					(*param).at(i)->generateMIPS(file, context);
					context.modify_stack('+');
					file << "lw $8," << context.retSP() - 4 << "($30)" << std::endl;
					file << "sw $8," << tempsp1 + 4 + i*4 << "($30)" <<  std::endl; 
				}
				for(int i = 0; i < param->size();i++){
					if(i>=4){
						file<<"sw $";
					}
					else{
						file<<"lw $";
					}
					file<<4+i<<','<<tempsp1 + i*4 + 4*(i<4) << "($30)" <<std::endl;
				}
				context.closeretfunc(file, context.retSP(), param->size(), temp, expression->getVarName());
			}
		}
		static void decnewvar(root& context, exprr *_expression){
			context.set_scope(GLOBAL);
			context.newVar(_expression->getVarName(), INT, FUNCTION);
			context.set_scope(LOCAL);
		}
};
