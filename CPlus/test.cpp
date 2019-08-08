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


int main(int argc, char const *argv[]) {

	// int x =1, y=0;
	// int i = --x>(y+x) ? 10:12.5>y++?'A':'Z'; 
	// std::cout << i << '\n';
	// 
	// int xx = 0b1001;
	// std::cout << (xx&xx-1) << '\n';
	// std::cout << (xx&(xx-1)) << '\n';
	// 
	// int yyy = 1, y1, y3;
	
	long k = 11;
	int n = 10;
	long p1[n];
	long *p[n];
	for(int i=0; i<n;i++){
		p[i] = &k;
	}
	
	printf("p[0]  %p\n", p[0]);
	printf("p[0]  %p\n", p[0]);
	
    return 0;
}
