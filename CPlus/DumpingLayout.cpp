/**
 *
 * clang -cc1 -fdump-record-layouts myfile.cpp
 */
#include <iostream>


class Base {
protected:
	int foo;
public:
	int method(int p) {
		return foo + p;
	}
};

struct Point {
	double cx, cy;
};

class Derived : public Base {
public:
	int method(int p) {
		return foo + bar + p;
	}
protected:
	int bar, baz;
	Point a_point;
	char c;
};

int main(int argc, char** argv) {
	return sizeof(Derived);
}