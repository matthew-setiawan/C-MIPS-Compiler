class comps : public statement_c
{
	private:
		std::vector<statement_c*>* 	left;
		std::vector<declarator*>* 	right;
		int ParamAdd[32] = {	0,0,0,0,
						0,0,0,0,
						0,0,0,0,
						0,0,0,0,
						0,0,0,0,
						0,0,0,0,
						0,0,0,0,
						0,0,0,0,};

	public:
		comps (std::vector<declarator*>* _left = NULL, std::vector<statement_c*>* _right = NULL){
			left=_right;
			right=_left;
		}

		virtual void generateMIPS(std::ostream& file, root& context) const override{
			context.globalize();
			if (right!=NULL){cright(file,context,right);}
			if (left!=NULL){cleft(file,context,left);}
			context.popfp("context");
			context.popfp("stack");
		}
		static void cright(std::ostream& file, root& context, std::vector<declarator*>* right){
			auto temp = right->begin();
			while(1){
				if (temp==right->end()){
					break;
				}
				else{
					(*temp)->generateMIPS(file,context);
					temp=temp+1;
				}
			}
		}
		static void cleft(std::ostream& file, root& context, std::vector<statement_c*>* right){
			auto temp = right->begin();
			while(1){
				if (temp==right->end()){
					break;
				}
				else{
					(*temp)->generateMIPS(file,context);
					temp=temp+1;
				}
			}
		}
};