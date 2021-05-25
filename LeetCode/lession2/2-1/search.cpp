/*
 * @Author: Y.t
 * @Date: 2021-05-25 23:21:10
 * @LastEditors: Y.t
 * @LastEditTime: 2021-05-25 23:24:12
 * @Description: 
 * build: clang++ std=c++17 search.cpp -o out && ./out
 */

#include <stdio.h>
#include <vector>
#include <iostream>
#include <functional>
#include <numeric>
#include <string>
#include <algorithm>    // std::unique, std::distance
#include <iterator>     // std::distance

using namespace std;


template <typename T>
void printVector(vector<T> &v) {
    copy(v.begin(), v.end(), ostream_iterator<T>(cout, " "));
    cout << endl;
}

template <typename T>
void printVector(vector<T> &v, int length) {
    copy(v.begin(), v.begin()+length, ostream_iterator<T>(cout, " "));
    cout << endl;
}


class Solution {

public:
    
    
};



int main(int argc, char *argv[]) {
    // int n[] = {9, 2, 3 , 4, 9} ;
    // vector<int> digits(n, n+5);

    vector<int> v = {0, 1, 1, 1, 2, 2, 3};

    Solution solution;
    auto v1 = v;
    printVector(v1);
    auto length = solution.removeDuplicates(v1);
    printVector(v1, length);

    auto v2 = v;
    printVector(v2);
    length = solution.removeDuplicates2(v2);
    printVector(v2, length);
    
    
    return 0;
}