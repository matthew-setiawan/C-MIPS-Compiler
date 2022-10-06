class doublev : public types{
	protected:
		double value;
		datatype _datatype;
	public: 

		virtual void generateMIPS(std::ostream &file, root& context) const override{typedec(file, context, value, 0, 0);}
		virtual double evaluate() const override { return value; };
		doublev (double _value){
			value = _value;
			_datatype = DOUBLE;
		}
};