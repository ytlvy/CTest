/*
 * @Author: Y.t
 * @Date: 2021-07-06 22:46:57
 * @LastEditors: Y.t
 * @LastEditTime: 2021-07-26 09:53:45
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

    ///字符串t 在字符串s的子序列中出现的个数
    ///dp数组定义: 在s的前i个字符中, 出现以j结尾的子序列个数
    int numDistinct(string &s, string &t) {
        vector<vector<int64_t>> dp(s.size()+1, vector<int64_t>(t.size()+1));
        
        for(int i=0; i<s.size(); i++) dp[i][0] = 1;
        for(int j=0; j<t.size(); j++) dp[0][j] = 0;
        for(int i=1; i<s.size(); i++) {
            for (int j=1; j<t.size(); j++) {
                if(s[i-1] == t[j-1]) {
                    dp[i][j] = dp[i-1][j-1]/*  */ + dp[i-1][j];
                }
                else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }

        return dp[s.size()][t.size()];
    }

    ///只能删除 最小距离
    int minDistance(string &s, string &t) {
       vector<vector<int>> dp(s.size()+1, vector<int>(t.size()+1));
        
        for(int i=0; i<s.size(); i++) dp[i][0] = i;
        for(int j=0; j<t.size(); j++) dp[0][j] = j;
        for(int i=1; i<s.size(); i++) {
            for (int j=1; j<t.size(); j++) {
                if(s[i-1] == t[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                }
                else {
                    dp[i][j] = min({dp[i-1][j-1]+2, dp[i-1][j]+1, dp[i][j-1]+1});
                }
            }
        }

        return dp[s.size()][t.size()]; 
    }

    ///可以替换
    int minDistance1(string &s, string &t) {
       vector<vector<int>> dp(s.size()+1, vector<int>(t.size()+1));
        
        for(int i=0; i<s.size(); i++) dp[i][0] = i;
        for(int j=0; j<t.size(); j++) dp[0][j] = j;
        for(int i=1; i<s.size(); i++) {
            for (int j=1; j<t.size(); j++) {
                if(s[i-1] == t[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                }
                else {
                    dp[i][j] = min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]}) + 1;
                }
            }
        }

        return dp[s.size()][t.size()]; 
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
