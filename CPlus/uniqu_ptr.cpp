#include <iostream>
#include <cstdlib>
#include <memory>
using namespace std;

struct Foo {
	Foo() {cerr << "Foo [" << this << "] constructed\n";}
	virtual ~Foo() {cerr << "Foo [" << this << "] destructed\n";}
};

void sink(unique_ptr<Foo> p) {
	cerr << "Sink owns Foo [" << p.get() << "]\n";
}

unique_ptr<Foo> source() {
	cerr << "Creating Foo in source\n";
	return unique_ptr<Foo>(new Foo);
}

int main(int argc, char** argv) {
	cerr << "Calling source\n";
	unique_ptr<Foo> pmain = source();  // Can also be written as
									   // auto pmain = source();

	cerr << "Now pmain owns Foo [" << pmain.get() << "]\n";
	cerr << "Passing it to sink\n";
//	sink(pmain);                    // ERROR! can't copy unique_ptr
	sink(move(pmain));              // OK: can move it!

	cerr << "Main done\n";
	return 0;
}