/*
 * @Author: Y.t
 * @Date: 2021-06-23 23:17:35
 * @LastEditors: Y.t
 * @LastEditTime: 2021-06-23 23:41:09
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
    
    vector<vector<int>> res_;
    private:
    void permutation_(vector<int> &nums, vector<int> &track){

        if(track.size() == nums.size()) {
            res_.push_back(track);
        }
        
        for(int i=0; i<nums.size(); i++){
            if(find(track.begin(), track.end(), nums[i]) != track.end()){
                continue;
            }

            track.push_back(nums[i]);
            permutation_(nums, track);
            track.pop_back();
        }
    }

    void permutation_1(vector<int> &nums, vector<int> &track){

        if(track.size() == nums.size()) {
            res_.push_back(track);
        }
        
        for(int i=0; i<nums.size(); i++){
            if(find(track.begin(), track.end(), nums[i]) != track.end()){
                continue;
            }

            track.push_back(nums[i]);
            
            permutation_(nums, track);
            track.pop_back();
        }
    }

public:
    vector<vector<int>> permutation(vector<int> &nums) {
        vector<int> track;
        permutation_(nums, track);

        return res_;
    } 
   
    
};



int main(int argc, char *argv[]) {
    // int n[] = {9, 2, 3 , 4, 9} ;
    // vector<int> digits(n, n+5);

    vector<int> v = {0, 1, 3, 5};

    Solution solution;
    // printVector(v);
    auto res = solution.permutation(v);
    for(auto per : res) {
        printVector(per);
    }
    
    
    return 0;
}

