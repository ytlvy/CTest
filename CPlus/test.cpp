#include <iostream>
#include <cstdio>

const int N = 1000;

void testConst() {

	printf("%d\n", N);
	// *const_cast<int*>(&N) = 102;
	printf("%d\n", N);
	printf("%d\n", *const_cast<int*>(&N));
}

int get_foo() {
    return 42;
}

void testConst1() {
    const int ci = get_foo();//初始值
    printf("%d\n", ci);
}

class Engine
{
public:
    virtual void SetState( int var, bool val ) {/*some implementation*/}
    virtual void SetState( int var, int val )  {/*some implementation*/}
};

class MyTurbochargedV8 : public Engine
{
public:
    // To prevent SetState( int var, bool val ) from the base class,
    // from being hidden by the new implementation of the other overload (below),
    // you have to put using declaration in the derived class
    // using Engine::SetState;

    void SetState( int var, int val )  {/*new implementation*/}
};


typedef 

int main(int argc, char const *argv[]) {

    

    return 0;
}
