#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
    std::vector<int> myvec = (std::vector<int>)(1, 2, 3);
    for (auto x: myvec) {
        std::cout << x;
    }
    std::cout << std::endl;

    return 0;
}