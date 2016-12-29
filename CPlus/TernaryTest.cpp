#include <iostream>
using namespace std;


void test1() {
	int test = 0;
	cout << "First  character " << '1' << endl;
	cout << "Second character " << (test ? 3 : '1') << endl;

}

void test2() {
	int test = 0;
	float fvalue = 3.111f;
	cout << (test ? fvalue : 0) << endl;
}

//compile error
//void test3 () {
//	int test = 0;
//	cout << test ? "A String" : 0 << endl;
//}

void test4 () {
	int test = 0;
	cout << (test ? "A String" : 0) << endl;
}

int main()
{
	 test4();
	return 0;
}
