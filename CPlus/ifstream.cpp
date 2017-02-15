#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>

extern "C" {
    double sqrt(double x) {
        return 10.0;
    }
}

#include <math.h>


void test() {

    // typical use case: an input stream represented as a pair of iterators
    std::istringstream in("Hello, world");
    std::vector<char> v( (std::istreambuf_iterator<char>(in)),
                          std::istreambuf_iterator<char>() );
    std::cout << "v has " << v.size() << " bytes. ";
    v.push_back('\0');
    std::cout << "it holds \"" << &v[0] << "\"\n";


    // demonstration of the single-pass nature
    std::istringstream s("abc");
    std::istreambuf_iterator<char> i1(s), i2(s);
    std::cout << "i1 returns " << *i1 << '\n'
              << "i2 returns " << *i2 << '\n';
    ++i1;
    std::cout << "after incrementing i1, but not i2\n"
              << "i1 returns " << *i1 << '\n'
              << "i2 returns " << *i2 << '\n';
    ++i2; // this makes the apparent value of *i2 to jump from 'a' to 'c'
    std::cout << "after incrementing i2, but not i1\n"
              << "i1 returns " << *i1 << '\n'
              << "i2 returns " << *i2 << '\n';
}

void test1 () {
    std::ifstream inputFile("/Users/gyj/Downloads/main_test.cpp");
    inputFile.unsetf(std::ios::skipws);
    // std::string contents(std::istreambuf_iterator<char>(inputFile), (std::istreambuf_iterator<char>()) );

    std::string contents((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

    std::cout << contents << '\n';
}



int main(int argc, char const *argv[]) {

    double x = sqrt(100000);
    std::cout << x << '\n';
}
