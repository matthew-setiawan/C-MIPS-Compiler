class declareenum : public declare {
	protected: 
		declare* initialization;
		virtual void generateMIPSdeclare(std::ostream &file, root& context, type_def type, bool isPointer) const override
		{ initialization->generateMIPSinitialize(file, context, type, expression, false); }
		exprr* expression;

	public: 
		declareenum(declare* _initialization, exprr* _expression = NULL)
		: initialization(_initialization), expression(_expression) {}

};