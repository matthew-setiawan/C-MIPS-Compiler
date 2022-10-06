class misc : public Node{
	private:
		ptr l;
		ptr r;
	public:

		virtual void generateMIPS(std::ostream& file, root& context) const override{
			l ->generateMIPS(file, context);
			r->generateMIPS(file, context);
		}
		misc(ptr _l, ptr _r){
			l = _l;
			r = _r;
		}
};
class statement_c: public Node {};
