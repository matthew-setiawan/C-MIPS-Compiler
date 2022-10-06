class unref : public unary
{
	public:
		unref(exprr* _expression) : unary(_expression) {} 
		virtual void generateMIPS(std::ostream &file, root& context) const override{
			expression->generateMIPS(file, context);
			loadarrayval(file,context.retSP(),0,0,5);
		}
};
class ref : public unary
{
	public:
		ref(exprr* _expression) : unary(_expression) {} 
		virtual void generateMIPS(std::ostream &file, root& context) const override{
			expression->loadWordVar(file, context);
		}
};
