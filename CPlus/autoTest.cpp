#include <iostream>
#include <vector>

struct A {
    A(int a=0):x(a){};
    int x;
};


int main(int argc, char const *argv[]) {
    size_t size = 6;
    std::vector<A> v;
    for (size_t i = 0; i < size; i++) {
        v.emplace_back(i);
    }

    std::for_each(v.begin(), v.end(), [](A a){printf("A:%d\n", a.x);});

    auto & val = v[0];   // &
    val.x = 100;
    std::for_each(v.begin(), v.end(), [](A a){printf("A:%d\n", a.x);});


    return 0;
}
