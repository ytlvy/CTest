#include <iostream>
#include <vector>

template<typename T>
void printVec(const std::vector<T>& v) {
    for (auto const& tmp : v)
        std::cout << tmp << " ";
    std::cout << std::endl;
}
