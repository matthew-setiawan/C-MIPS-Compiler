class definefunction : public maindec
{
	protected:
		std::string funcid;
		exprr* funcexpr;
		std::vector<declarator*>* param;
		type_def* functype;
		statement_c* statements;
		std::string funcname;
        std::string paramAdd[10]={"","","","","","","","","",""};

	public:
		definefunction (type_def* _functype, std::string _funcid, std::vector<declarator*>* _param, statement_c* _statements) 
		: functype(_functype), funcid(_funcid), param(_param), statements(_statements) {
			paramAdd[0] = funcid;
		}


		virtual void generateMIPS(std::ostream& file, root& context) const override
		{
			context.openfunction(file,paramAdd[0]);
			int count = 0;
			int p = 8;
			while(param!=NULL){
				if (count>=param->size()){
					break;
				}
				else{
					file << "##"<<"Type: "<<(*param)[count]->get_type()<<std::endl;
					if ((*param)[count]->get_type()==INT || count>1){
						file << "sw $" << count + 4 << "," << p << "($30)" << std::endl;
					}
					else if(count < 2){
						if((*param)[count]->get_type()==FLOAT||(*param)[count]->get_type()==DOUBLE){
							file << "swc1 $" << count*2 + 12 << "," << p + 4*((*param)[count]->get_type()==DOUBLE)<< "($30)" << std::endl;
						}
						if((*param)[count]->get_type()==DOUBLE){
							file << "##DOUBLE HERE" << std::endl;
							file << "swc1 $" << 2*count + 13 << "," << p << "($30)" << std::endl;
							p = p + 4;
						}
					}
					context.makeArg((*param)[count]->get_parameter(), (*param)[count]->get_type(), DEFAULT, (count+2)*4, (*param)[count]->isPointerC());
					count = count + 1;
					p = p + 4;
				}
			}


			if(statements != NULL){ 
				statements->generateMIPS(file, context);
			}
			if (paramAdd[0] == "main"){
            		file << "move $2, $0" << std::endl; 
        		}
			context.closefunction(file,paramAdd[0]);
		}


};

class declarefunction : public declare{
	private:
		std::string funcid;
		std::vector<declarator*>* param;
            exprr* expression;
            datatype type1;
	public:
		declarefunction(std::string _funcid, std::vector<declarator*>* _param)
		: funcid(_funcid), param(_param) {}
            virtual long spaceRequired(root *context) const{
                  int ptr  = 0;
                  long spacereq=0;
                  if(ptr==1)  {
                        spacereq=4;
                  }
                  else if(type1==INT)  {
                        spacereq=4;
                  }
                  else if(type1==DOUBLE){
                        spacereq=8;
                  }
                  return spacereq;
            }
		virtual void generateMIPSdeclare(std::ostream &file, root& context, type_def type, bool pointer_capable) const override
		{ context.newVar(funcid, type, FUNCTION); }
};