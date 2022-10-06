class type_def
{
	private:
		std::string varName = "";
		int label_tracker = 0;
		int pointer = 0;
		int array = 0;
		int isPointerTracker = 0;
		datatype varType = INT;
		bool isPointer[100];

	public:
		type_def(std::string a, type_def _isPointer) {
			for(int i=0;i<100;i++){
				isPointer[i]=0;
			}
			isPointer[isPointerTracker] = 1;
			varType = _isPointer.getVarType();
			modify_array('+');
		}
		type_def(datatype _varType){
			for(int i=0;i<100;i++){
				isPointer[i]=0;
			}
			varType = _varType;
		}
		void modify_isPointerTracker(char c){
			if(c=='+'){
				isPointerTracker++;
			}
			else if(c=='-'){
				isPointerTracker--;
			}
		}
		bool getIsPointer(){ 
			return isPointer[isPointerTracker]; 
		}
		datatype getVarType(){
			return varType; 
		}
		void modify_array(char c){
			if(c=='+'){
				array++;
			}
			else if(c=='-'){
				array--;
			}
		};
};
