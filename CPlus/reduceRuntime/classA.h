#include <ostream>

class A {
public:
    A(){ printf("A construct\n"); };
    ~A(){};
    void test(){};
    virtual void test1(){};
};