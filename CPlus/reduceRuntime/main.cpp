#include <ostream>

class A;
#include "classA.h"

class B {
public:
    B() {printf("B construct\n");};
    ~B(){};
    A test();
    A test1(A a){a.test()};
private:
    A a_;
};


int main(int argc, char const *argv[]) {
    
    B b;
    return 0;
}