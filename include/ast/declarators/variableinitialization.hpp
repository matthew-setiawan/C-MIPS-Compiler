class variable_initialization : public declare 
{
	protected: 
		declare* declarer;
		exprr* expression;
        datatype _dataType = INT;

	public: 
		virtual void generateMIPSdeclare(std::ostream &file, root& context, type_def declarator_type, bool isPointer) const override{
			declarer->generateMIPSinitialize(file, context, declarator_type, expression, isPointer);
		}
		variable_initialization(declare* _declarer, exprr* _expression){
			declarer = _declarer;
            _dataType = INT;
			expression = _expression;
		}
};