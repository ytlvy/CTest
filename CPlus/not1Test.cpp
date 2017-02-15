#include <iostream>
#include <numeric>
#include <iterator>
#include <functional>
#include <iostream>
#include <vector>

struct LessThan7: std::unary_function<int, bool> {
    bool operator()(int i) const {return i<7;}
};

void test1() {
    std::vector<int> v(10);
    std::iota(begin(v), end(v), 0);
    std::cout << std::count_if(begin(v),  v.end(), std::not1(LessThan7())) << '\n';
    std::function<int(int)> less_than9 = [](int x){return x < 9;};
    std::cout << std::count_if(v.begin(), v.end(), std::not1(less_than9)) << '\n';
}

struct old_same : std::binary_function<int, int, bool>
{
    bool operator()(int a, int b) const { return a == b; }
};

struct new_same
{
    bool operator()(int a, int b) const { return a == b; }
};

bool same_fn(int a, int b)
{
    return a == b;
}

void test() {
    std::vector<int> v1{0, 1, 2};
    std::vector<int> v2{2, 1, 0};
    std::vector<bool> v3(v1.size());

    std::cout << "negating a binary_function:\n";
    std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(),
                   std::not2(old_same()));

    std::cout << "negating a standard functor:\n";
    std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(),
                   std::not2(std::equal_to<int>()));

    std::cout << "negating a std::function:\n";
    // std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(),
    //                std::not2(std::function<bool(int,int)>(new_same())));

    std::cout << "negating a std::reference_wrapper:\n";
    std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(),
                   std::not2(std::ref(same_fn)));

    for (std::size_t i = 0; i < v1.size(); ++i)
        std::cout << v1[i] << ' ' << v2[i] << ' ' << v3[i] << '\n';
}

int main(int argc, char const *argv[]) {
    test();

    return 0;
}
