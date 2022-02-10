/*
 * @Author: Y.t
 * @Date: 2021-07-06 15:17:21
 * @LastEditors: Y.t
 * @LastEditTime: 2021-07-06 15:26:39
 * @Description: 
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
    //;连续子序列 通过滑动窗口解决
    int minSubArrayLen(vector<int> &nums, int target) {
        int winSum = 0, winLen = 0, winBegin = 0, res = INT32_MAX;
        for( int j=0; j<nums.size(); j++) {
            winSum += nums[j];

            while(winSum >= target){
                winLen = j - winBegin + 1;
                res = min(res, winLen);
                winSum -= nums[winBegin++];
            }
        }
        return res == INT32_MAX ? 0 : res; 
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