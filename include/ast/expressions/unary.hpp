typedef const exprr *Expression_Ptr;

class unary : public exprr{
	protected:
		exprr* expression;
	public:
		unary(exprr* _expression) : expression(_expression) {}
};
