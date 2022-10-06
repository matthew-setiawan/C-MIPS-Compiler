class floatv : public types{
	private:
		float value;
		datatype _datatype;
	public: 
		floatv (float _value){
			value = _value;
			_datatype=FLOAT;
		}
		virtual double evaluate() const override { return value; };
		virtual void generateMIPS(std::ostream &file, root& context) const override{typedec(file,context,0,value,1);}
};