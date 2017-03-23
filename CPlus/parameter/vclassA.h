#include <ostream>

class A {
public:
    explicit A(int a):aa(a){};
    ~A(){};
    virtual void test (){};
    void print(){printf("A.aa=%d\n", aa);};
private:
    int aa;
    int bb;
};