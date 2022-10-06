class assignment : public exprr
{
	protected:
		exprr_ left;
		exprr_ right;
			
	public:
		assignment (exprr_ _left, exprr_ _right){
			left = _left;
			right = _right;
		}
};

class directa : public assignment
{
	public:
		directa (exprr_ _left, exprr_ _right) : assignment (_left, _right) {}

		virtual void generateMIPS(std::ostream &file, root& context) const override{
			returnsp(file,context,left,0);
			context.modify_stack('-');
			int sp = returnsp(file,context,right,1);
			context.modify_stack('+');
			loadarrayval(file,sp+4,sp,0,3);
		}
		static int returnsp(std::ostream &file, root& context, exprr_ _left, int opt1){
			if(context.retSP()!=0){
				if(opt1==0){
					_left->loadWordVar(file, context);
				}
				else{
					_left->generateMIPS(file, context);
				}
				return context.retSP();
			}
			else{
				if(opt1==0){
					_left->loadWordVar(file, context);
				}
				else{
					_left->generateMIPS(file, context);
				}
				return 0;
			}
		}
};
