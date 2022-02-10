/*
 * @Author: Y.t
 * @Date: 2021-07-02 20:01:04
 * @LastEditors: Y.t
 * @LastEditTime: 2021-07-02 20:26:28
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
    int twoDBag(vector<int> &weights, vector<int>values, int bagWeight) {
        int m = weights.size();

        //前x个物品, 背包重量为y 下 最大价值
        vector<vector<int>> dp(m+1, vector<int>(bagWeight+1, 0));
        
        //前1个物品, 背包重量大于第一个物品的前提下 都是第一个物品重量
        for(int j=bagWeight; j>=weights[0]; j--) {
            dp[0][j] = weights[0];
        }

        for(int i=1; i<m; i++) {
            for(int j=0; j<=bagWeight;j++) {
                if(j < weights[i]) {
                    dp[i][j] = dp[i-1][j];
                }
                else {
                    dp[i][j] = max(dp[i-1])[j], (dp[i-1][j-weights[i]]+values[i]));
                }
            }
        }
    }
   
    
};



int main(int argc, char *argv[]) {
    // int n[] = {9, 2, 3 , 4, 9} ;
    // vector<int> digits(n, n+5);

    vector<int> weights = {1, 3, 4};
    vector<int> v1 = {15, 20, 30};

    Solution solution;
    auto length = solution.findMedianSortedArrays(v, v1);
    cout<<"find: "<<length<<endl;
    
    
    return 0;
}