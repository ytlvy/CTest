/*
 * @Author: Y.t
 * @Date: 2021-06-21 19:05:17
 * @LastEditors: Y.t
 * @LastEditTime: 2021-06-21 23:16:33
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
    int changeWithInfinityCoins(vector<int> &coins, int amount) {
        int n = coins.size() + 1;
        int m = amount + 1;
        // int p[N][M] = {0};

        //int **dp = (int **)calloc((n) * (m), sizeof(int));   
        //Then access array elements like array1[ii + 10*jj]

        int **dp = new int*[n];
        for(int i=0; i<n; i++){
            dp[i] = new int[m]();
        }

        //baseCase
        for(int i=0; i<n; i++) {
            dp[i][0] = 1;
        }

        vector<vector<int>> res;

        for(int i=1; i<n; i++) {
            for (int j=1; j< m; j++) {
                int lastSum = j - coins[i-1];
                if(lastSum >= 0){//新产生
                    dp[i][j] = dp[i-1][j] + dp[i][lastSum];
                }
                else {//继承之前的
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        
        return dp[coins.size()][amount];
    }

    // int changeWithInfinityCoins(vector<int> &coins, int amount) {
    //     int n = coins.size() + 1;
    //     int m = amount + 1;
    //     // int p[N][M] = {0};

    //     //int **dp = (int **)calloc((n) * (m), sizeof(int));   
    //     //Then access array elements like array1[ii + 10*jj]

    //     int **dp = new int*[n];
    //     for(int i=0; i<n; i++){
    //         dp[i] = new int[m]();
    //     }

    //     //baseCase
    //     for(int i=0; i<n; i++) {
    //         dp[i][0] = 1;
    //     }

    //     vector<vector<int>> res;

    //     for(int i=1; i<n; i++) {
    //         for (int j=1; j< m; j++) {
    //             int lastSum = j - coins[i-1];
    //             if(lastSum >= 0){//新产生
    //                 dp[i][j] =  dp[i][lastSum];
    //             }
    //         }
    //     }

        

    //     return dp[coins.size()][amount];
    // }
   
};



int main(int argc, char *argv[]) {
    // int n[] = {9, 2, 3 , 4, 9} ;
    // vector<int> digits(n, n+5);

    vector<int> v = {1, 2, 5};

    Solution solution;
    printVector(v);
    auto length = solution.changeWithInfinityCoins(v, 5);
    cout<<"find: "<<length<<endl;
    
    
    return 0;
}

