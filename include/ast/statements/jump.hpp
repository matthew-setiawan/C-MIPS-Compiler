class jump : public statement_c
{
	private:
		exprr* jumploc;

	public:
		jump (exprr* _expr=NULL){
			jumploc=_expr;
		}
		virtual void prettyPrint(std::ostream& file, root& context){
			file << "##Implement Jump pretty print" << std::endl;
		}
		virtual void generateMIPS(std::ostream& file, root& context) const override{
			initialize(file,context,jumploc,0);
			file << "b " << context.getMainReturn() << std::endl;
		}
};