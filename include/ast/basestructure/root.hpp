class root
{
	private:
		std::map<std::string, vars*>* rootmap = new std::map<std::string, vars*>();
		std::map<int, vars*>* address = new std::map<int, vars*>();
		std::string returnToMain;
		std::deque<std::map<std::string, vars*>*> scopemap;
		std::deque<int> framepointer;
		std::deque<std::string> breakRet;
		std::deque<std::string> continueRet;
		std::deque<exprr*> switchRet;
		std::deque<std::string> labelRet;
		int stack_reference = 0;

	public:
		void addiu(std::ostream& file,std::string reg){
			file << "addiu " <<reg<<","<<reg<<",1" << std::endl;
		}
		void subiu(std::ostream& file,std::string reg){
			file << "addiu " <<reg<<","<<reg<<",-1" << std::endl;
		}
            void openfunction(std::ostream& file,std::string id){
			scope_tracker = LOCAL;
			returnToMain = "RETURN_"+std::to_string(makeNameUnq+1);
			makeNameUnq = makeNameUnq + 1;
			file <<".text " << std::endl;
			file << ".globl " <<  id << std::endl;
			file << ".ent "   << id << std::endl;

			file <<  id  << ":" << std::endl;
			file << "sw $31, -4($29)" << std::endl;
			file << "sw $30, -8($29)" << std::endl;
			for(int i=0;i<8;i++){
				subiu(file,"$29");
			}
			file << "move $30,$29" << std::endl;

		}
		bool isDefault(){
			if(labelRet.size()!=0){
				return true;
			}
			return false;
		}
		void closeswitch(std::ostream& file,std::string ss,std::string exit_string){
			file << "b "<< exit_string << std::endl;
			file << ss << std::endl;
			file << exit_string << ":" << std::endl;
			stack_reference = stack_reference + 2;
			breakRet.pop_front();
		}
		void switchmain(std::ostream& file,int sp, int csp,std::string label){
			file << "li $2,0"<< std::endl;
			file << "lw $2," << sp + 4 << "($30)" << std::endl;
                  file << "lw $4," << csp << "($30)" << std::endl;
			file << "beq $2,$4," << label << std::endl;
		}
            void closefunction(std::ostream& file,std::string id){
			file << returnToMain << ":" << std::endl;
			file << "move $29, $30"  << std::endl; 
			for(int i=0;i<8;i++){
				addiu(file,"$29");
			}
			file << "li $30,0"<<std::endl;
			file << "lw $30,-8($29)" << std::endl;
			file << "lw $31,-4($29)" << std::endl;
			file << "jr $31"  << std::endl;
			file << "nop" << std::endl;
			file << "nop" << std::endl;
			file << "nop" << std::endl;
			file << ".end " << id << std::endl;
		}
		void closeretfunc(std::ostream& file, int sp, int count, int tempsp, std::string name){
			file << "addiu $sp, $sp," << sp << std::endl; 
			file << "la $2," << name << std::endl;
			file << "jalr $2" << std::endl;
			file << "addiu $sp, $sp," << -sp << std::endl; 
			stack_reference = stack_reference + count;
			file <<"sw $2," << tempsp << "($30)" << std::endl;
		}
		void type(std::ostream& file, datatype _type){
			file << "li $2," << 3*(_type == INT || _type == FLOAT)+1 << std::endl;
			file << "sw $2," << stack_reference*4 << "($30)" << std::endl;
		}
            void setscope(staticrootclassification _scope){scope_tracker = _scope;}
            void newcase(exprr* case_statement, std::string case_label) { 
			switchRet.push_back(case_statement);
			labelRet.push_back(case_label);
		}
		void newlabelc(std::string case_label){labelRet.push_back(case_label);}
		std::string getCaseLabel(){return labelRet[0];}
		exprr* getCaseTracker(){return switchRet[0];}
		int getCaseSize(){
			int i = 0;
			while(switchRet[i]!=NULL){
				i=i+1;
			}
			return i;
		}
		void popSwithRet(int n){
			for(int i=0;i<n;i++){
				switchRet.pop_front();
			}
		}
		void popLabelRet(int n){
			for(int i=0;i<n;i++){
				labelRet.pop_front();
			}
		}
		vars getVar(std::string varName){return *((*rootmap)[varName]);}
		void makeArg(std::string argName, type_def argType, datastructure argDec, int argAdd, bool isPointer){ 
			(*rootmap)[argName] = new vars(argAdd, argType, argDec, LOCAL, isPointer);
		}
		void addBreak(std::string n){ breakRet.push_back(n);}
		std::string getBreakFront() {return breakRet.front(); }
		std::string getContinueFront() {return continueRet.front();}
		std::string getMainReturn() {return returnToMain;}
		staticrootclassification get_context_scope(){return scope_tracker;}
            void set_scope(staticrootclassification scope){scope_tracker = scope;};
		void globalize(){
			framepointer.push_back(stack_reference*4);
			scopemap.push_back(rootmap);
			rootmap = new std::map<std::string, vars*>(*rootmap);
		}
		void popfp(std::string opt){
			if(opt=="context"){
				stack_reference = framepointer.back();
				framepointer.pop_back();
			}
			else if(opt=="stack"){
				rootmap = scopemap.back();
				scopemap.pop_back();
			}
		}
		int retSP() { return stack_reference*4; }
		int callfunction1(std::ostream& file, int size){
			stack_reference = stack_reference - size + 1;
			return stack_reference*4;
		}
		void modify_stack(char val){
			if (val=='-'){stack_reference--;}
			else if(val=='+'){stack_reference++;
			}else if (val=='3'){stack_reference ++;}
		}
		void handlearg(std::ostream& file, int tempsp, int fsp, int asp){
			stack_reference++;
			file << "##Here" << std::endl;
			file << "lw $8," << tempsp << "($30)" << std::endl;
			file << "sw $8," << fsp + asp << "($30)" <<  std::endl; 
		}
		void callfunction2(std::ostream& file, int rega, std::string ID){
			//implement
		}
		int addlabel(){
			makeNameUnq = makeNameUnq + 1;
			return makeNameUnq - 1;
		}
		vars newVar(std::string varName, type_def varType, datastructure DecVarType, bool isPointer = false, int sizeVar = 1){
			stack_reference = stack_reference - sizeVar*(scope_tracker==LOCAL) - ((DecVarType == ARRAY)&&(scope_tracker == LOCAL));
			(*address)[stack_reference*4] = new vars(stack_reference*4, varType, DecVarType, scope_tracker, isPointer);
			(*rootmap)[varName] = new vars(stack_reference*4, varType, DecVarType, scope_tracker, isPointer);
			return *((*rootmap)[varName]);
		}
};