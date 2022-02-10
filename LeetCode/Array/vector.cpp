/*
 * @Author: Y.t
 * @Date: 2021-06-30 20:15:16
 * @LastEditors: Y.t
 * @LastEditTime: 2021-06-30 20:19:53
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
#include "../helper.h"

class Solution {

public:
    vector<int> sortedSquares(vector<int> &nums) {
        vector<int> res = vector<int>(nums.size(), 0);        
        for (int i = 0, j = nums.size(); i<=j;) {
            long ii = nums[i] * nums[i];
            long jj = nums[j] * nums[j];
             if(ii > jj) {
                 res.push_back(ii);
                 i++;
             }
             else {
                 res.push_back(jj);
                 j--;
             }
        }
    }
   
    
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
