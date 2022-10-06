class negexpr : public unary{
	public:
		virtual void generateMIPS(std::ostream &file, root& context) const override{
			expression->generateMIPS(file, context);
			loadarrayval(file,context.retSP(),(expression->_getVarType(context) == FLOAT),0,4);
		}
		negexpr (exprr* _expression) : unary(_expression) {}

};