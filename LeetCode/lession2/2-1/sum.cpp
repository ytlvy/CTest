/*
 * @Author: Y.t
 * @Date: 2021-06-08 09:43:15
 * @LastEditors: Y.t
 * @LastEditTime: 2021-06-08 10:00:20
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
#include <unordered_map>

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
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mapping;
        vector<int> result;

        for (int i=0; i<nums.size(); i++) {
            mapping[nums[i]] = i;
        }

        for( int i =0; i<nums.size(); i++) {
            const int gap = target - nums[i];
            if(mapping.find(gap) != mapping.end() && mapping[gap] > i) {
                result.push_back(i+1);
                result.push_back(mapping[gap] + 1);
                break;
            }
        }

        return result;
    }

    vector<vector<int> > threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        if(nums.size() < 3) return result;

        sort(nums.begin(), nums.end());
        const int target = 0;
        auto last = nums.end();
        for(auto i=nums.begin(); i< last-2; ++i) {
            auto j = i+1;
            if(i>nums.begin() && *i==*(i-1)) continue;
            auto k = last - 1;
            while(j < k) {
                if(*i + *j + *k < target) {
                    ++j;
                    while(*j == *(j-1) && j<k) ++j;
                }
                else if(*i + *j + *k > target) {
                    --k;
                    while(*k==*(k+1) && j<k) --k;
                }
                else {
                    result.push_back({*i, *j, *k});
                    ++j;
                    --k;
                    while(*j==*(j-1) && *k ==*(k+1) && j<k) ++j;
                }
            }

        }
        return result;
    }
   
    
};



int main(int argc, char *argv[]) {
    // int n[] = {9, 2, 3 , 4, 9} ;
    // vector<int> digits(n, n+5);

    vector<int> v = {0, 1, 3, 5, 7, 8, 10};
    vector<int> v1 = {4, 6, 7, 8};

    Solution solution;
    printVector(v1);
    auto length = solution.findMedianSortedArrays(v, v1);
    cout<<"find: "<<length<<endl;
    
    
    return 0;
}

