/*
 * @Author: Y.t
 * @Date: 2021-07-01 22:44:39
 * @LastEditors: Y.t
 * @LastEditTime: 2021-07-01 23:19:59
 * @Description: 
 *
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

    //将数字拆分为至少两个数字之和最大
    int integerBreak(int n) {
        vector<int> dp(n + 1);
        
        dp[2] = 1;
        for(int i = 3; i<=n; i++) {
            for (int j=1; j<i-1; j++) {
                dp[i] = max(dp[i], max( (i-j)*j, dp[i-j]*j));
            }
        }
        return dp[n];
    }
    
    //n个数字组成二叉搜索树个数
    int numTrees(int n) {
        vector<int> dp(n + 1);//n个数字组成的搜索树个数
        dp[0] = 1;


        for(int i = 1; i<=n; i++) {
            for (int j=1; j<=i; j++) {
                dp[i] += dp[j-1] * dp[i-j];
            }
        }

        return dp[n];
    }
   
    
};



int main(int argc, char *argv[]) {

    vector<int> v = {0, 1, 3, 5, 7, 8, 10};

    Solution solution;
    auto length = solution.integerBreak(10);
    cout<<"find: "<<length<<endl;
    
    
    return 0;
}

