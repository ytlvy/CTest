/*
 * @Author: Y.t
 * @Date: 2021-06-17 17:47:35
 * @LastEditors: Y.t
 * @LastEditTime: 2021-06-17 20:03:39
 * @Description: 
 * build: clang++ -std=c++11 rob.cpp -o out && ./out
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

using namespace std;

class Solution {
private:
    vector<int> memo;
    //从start开始抢到的最大值
    int rob_(vector<int> &nums,  int start) {
        //basecase
        //start 值域 [0, nums.size()-1]
        //主函数从0 开始, 所以basecase 在右端
        if(start >= nums.size()) {
            return 0;
        }

        //缓存
        if(memo[start] != -1) return memo[start];

        //选择
        int doit = nums[start] + rob_(nums, start+2);
        int passby = rob_(nums, start + 1);
        int res = max(doit, passby);
        memo[start] = res;

        return res;
    }

public:
    
    int rob(vector<int> &nums) {
        memo = vector<int>(nums.size(), -1);
        return rob_(nums, 0);
    }
   
    int rob1(vector<int> &nums) {
        int n = nums.size();

        //dp 从第i间开始, 最多抢到的钱数
        //base case: dp[n] = 0
        //多余分配的2个空间用base case填充
        vector<int> dp(n+2, 0); 

        for(int i=n-1; i>=0; i--) {
            dp[i] = max(dp[i+1], nums[i]+dp[i+2]);
        }

        return dp[0];
    }

    int rob2(vector<int> &nums) {
        int n = nums.size();

        int dp_i_1=0, dp_i_2 = 0;

        int dp_i = 0;
        for(int i=n-1; i>=0; i--) {
            dp_i = max(dp_i_1, nums[i] + dp_i_2);
            dp_i_2 = dp_i_1;
            dp_i_1 = dp_i;
        }

        return dp_i;
    }

    int robInCycle(vector<int> &nums) {
        int n = nums.size();
        if(n == 1) return nums[0];

        return max( robInRange(nums, 0, n-2), robInRange(nums, 1, n-1));
    }
    private:
    int robInRange(vector<int> &nums, int start, int end) {
        int dp_i_1=0, dp_i_2 = 0;

        int dp_i = 0;
        for(int i=end; i>=start; i--) {
            dp_i = max(dp_i_1, nums[i] + dp_i_2);
            dp_i_2 = dp_i_1;
            dp_i_1 = dp_i;
        }

        return dp_i;
    }
    
};



int main(int argc, char *argv[]) {
    // int n[] = {9, 2, 3 , 4, 9} ;
    // vector<int> digits(n, n+5);
    
    vector<int> v = {2, 7, 9, 3, 1};
    int res = 12;

    Solution solution;
    printVector(v);
    auto length = solution.rob(v);
    cout<<"find: "<<length<<endl;
    
    length = solution.rob1(v);
    cout<<"find: "<<length<<endl;

    length = solution.rob2(v);
    cout<<"find: "<<length<<endl;


    length = solution.robInCycle(v);
    cout<<"find: "<<length<<endl;

    

    return 0;
}
