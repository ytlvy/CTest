#include <iostream>
#include "plusOne.cpp"
#include "printVec.h"

int main(int argc, char *argv[]) {
    int n[] = {9, 2, 3 , 4, 9} ;
    std::vector<int> digits(n, n+5);

    Solution solution;
    auto newV = solution.plusOneNew(digits);
    printVec(newV);


    newV = solution.plusOne(digits);
    printVec(newV);
}
