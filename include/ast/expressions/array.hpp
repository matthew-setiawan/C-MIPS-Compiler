class array_indexing : public unary
{
	private:
		exprr* arrayval;
		virtual void generateMIPS(std::ostream &file, root& context) const override{
			loadWordVar(file, context);
			loadarrayval(file, context.retSP(),0,0,2);
		}
	public:


		virtual void loadWordVar(std::ostream &file, root& context) const{
			int sp1 = context.retSP();
			expression->generateMIPS(file, context);
			context.modify_stack('-');
			int sp2 = context.retSP();
			arrayval->generateMIPS(file, context);
			context.modify_stack('+');
			loadarrayval(file,sp1,sp2,2,1);
		};
		array_indexing(exprr* _expression, exprr* _arrayval)
		: unary(_expression), arrayval(_arrayval) {}


};