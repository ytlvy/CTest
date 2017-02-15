#include <iostream>
#include <vector>


int main(int argc, char const *argv[]) {

    // std::vector<int> v;
    // v.reserve(5);
    //
    // for (size_t i = 0; i < 5; i++) {
    //     v.push_back(i);
    // }

    std::vector<int> v = { 0, 1, 2, 3, 4, 5 };

    auto riter = std::find(v.rbegin(), v.rend(), 3);
    // auto iter((++riter).base()); //ok 推荐
    // auto iter((riter).base()); //error
    auto iter(--riter.base());      //ok 可能不能编译
    v.erase(iter);

    std::for_each(v.begin(), v.end(), [](int x){std::cout <<x<< '\n';});

    return 0;
}
