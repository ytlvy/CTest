class IKlass {
public:
	virtual void destroy() = 0;
	virtual int do_stuff(int param) = 0;
	virtual void do_something_else(double f) = 0;
};