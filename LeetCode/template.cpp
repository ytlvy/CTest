/*
 * @Author: Y.t
 * @Date: 2021-05-27 19:17:04
 * @LastEditors: Y.t
 * @LastEditTime: 2021-06-19 15:53:17
 * @Description: 
 * build: clang++ -std=c++17 longestConsecutive.cpp -o out && ./out
 */


#include <stdio.h>
#include <vector>
#include <iostream>
#include <functional>
#include <numeric>
#include <string>
#include <algorithm>    // std::unique, std::distance
#include <iterator>     // std::distance
#include <stack>
#include "helper.h"

class Solution {

public:

   
    
};



int main(int argc, char *argv[]) {
    // int n[] = {9, 2, 3 , 4, 9} ;
    // vector<int> digits(n, n+5);

    vector<int> v = {0, 1, 3, 5, 7, 8, 10};
    vector<int> v1 = {4, 6, 7, 8};

    Solution solution;
    printVector(v1);
    // auto length = solution.findMedianSortedArrays(v, v1);
    // cout<<"find: "<<length<<endl;
    
    
    return 0;
}
