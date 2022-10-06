class expression : public statement_c{
	private:
		exprr *expr;
		statement_c *sc;
		exprr *left;
		exprr *right;
	public:
		expression( exprr* _expression = NULL ) : expr (_expression) {

		}
		virtual void print(std::ostream &file){
            	file<<"##Implement Print"<<std::endl;
        	}
		virtual void generateMIPS(std::ostream& file, root& context) const override{
			initialize(file,context, expr, 0);
		}
		virtual void compileexpression(std::ostream& file, root& context) {
			left->generateMIPS(file,context);
			right->generateMIPS(file,context);
		}
};