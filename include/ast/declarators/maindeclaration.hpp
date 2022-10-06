class maindec : public Node {
	public:
            virtual void generateMIPSinitialize(std::ostream &a, root& b, type_def c, exprr* d, bool e) const {
                  throw std::runtime_error("Not Implemented");
            }
            virtual int getPointer(root *context) const {
                  return 0;
            }
            virtual long ReqSpace(root *context) const {
                  return 0;
            }
		virtual void generateMIPSdeclare(std::ostream &a, root& b, type_def c, bool d) const {
                  throw std::runtime_error("Not Implemented");
            }
		virtual void generateMIPSinitializearray(std::ostream &a, root& b, type_def c, std::vector<exprr*>* d) const {
                  throw std::runtime_error("Not Implemented");
            }
            virtual std::string getVarType(root *context) const  {
                  return "";
            }
            virtual void prettyPrint(std::ostream &file){};
};