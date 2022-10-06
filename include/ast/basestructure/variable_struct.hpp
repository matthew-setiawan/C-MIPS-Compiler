class vars
{
	private: 
		type_def typeVar;
		bool isPointer=0;
		staticrootclassification scopeVar = LOCAL;
		int Reg[32] = {	0,0,0,0,
					0,0,0,0,
					0,0,0,0,
					0,0,0,0,
					0,0,0,0,
					0,0,0,0,
					0,0,0,0,
					0,0,0,0	};
		datastructure decVar = NONE;
		int regpointer = 4;


	public:

		virtual void incrementRegPointer(){regpointer++;}			
		datastructure getDecType() { return decVar; }
		bool _isPointer() { return isPointer; }
		bool isGlobal(){ return (scopeVar==GLOBAL);}
		bool isLocal(){ return (scopeVar==LOCAL);}	
		datatype getTypeVar() { return typeVar.getVarType(); }	
		int getVarAdd() { return Reg[regpointer]; } 	
		type_def getTypeDef() { return typeVar; }					
	
		vars (int _address, type_def _typeVar , datastructure _decVar, staticrootclassification _scopeVar, bool _isPointer)
		:scopeVar(_scopeVar), decVar(_decVar), typeVar(_typeVar), isPointer(_isPointer) {
			Reg[regpointer]=_address;
		}	
};