#include "generic_interface.h"
#include <iostream>
#include <windows.h>

using namespace std;


class MyKlass : public IKlass {
public:
	MyKlass()
		: m_data(0)
	{
		cerr << "MyKlass constructor\n";
	}

	~MyKlass()
	{
		cerr << "MyKlass destructor\n";
	}

	void destroy()
	{
		delete this;
	}

	int do_stuff(int param)
	{
		m_data += param;
		return m_data;
	}

	void do_something_else(double f)
	{
		int intpart = static_cast<int>(f);
		m_data += intpart;
	}
private:
	int m_data;
};

extern "C" __declspec(dllexport) IKlass* __cdecl create_klass()
{
	return new MyKlass;
}