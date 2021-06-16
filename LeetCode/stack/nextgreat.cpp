/*
 * @Author: Y.t
 * @Date: 2021-06-16 18:50:02
 * @LastEditors: Y.t
 * @LastEditTime: 2021-06-16 23:07:26
 * @Description: 
* build: clang++ -std=c++17 nextgreat.cpp -o out && ./out
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
    ///2 1 2 4 3
    ///4 2 4 -1 -1
    vector<int> nextGreate(vector<int> &nums) {
        stack<int> s;
        vector<int> res(nums.size());

        for(int i=nums.size()-1; i>=0; i--) {

            while(!s.empty() && nums[i] >= s.top()) {
                s.pop();
            }

            res[i] =  s.empty() ? -1:s.top();
            s.push(nums[i]);
        }
        return res;
    }


    //[73, 74, 75, 71, 69, 72, 76, 73]
    //[1,  1,  4,  2,  1,  1,  0,  0]
    vector<int> nextGreate1(vector<int> &nums) {
        stack<int> s;
        vector<int> res(nums.size());

        for(int i=nums.size()-1; i>=0; i--) {

            while(!s.empty() && nums[i] >= nums[s.top()]) {
                s.pop();
            }

            res[i] =  s.empty() ? 0 :s.top() - i;
            s.push(i);
        }

        return res;
    }
    
    vector<int> dailyTemperature(vector<int> &nums){
        
    }

    
};



int main(int argc, char *argv[]) {
    // int n[] = {9, 2, 3 , 4, 9} ;
    // vector<int> digits(n, n+5);

    vector<int> v = {73, 74, 75, 71, 69, 72, 76, 73};
    vector<int> v1 = {2, 1, 2, 4, 3};

    Solution solution;
    printVector(v1);
    
    auto res = solution.nextGreate(v1);
    printVector(res);
    
    res = solution.nextGreate1(v);
    printVector(res);
    
    return 0;
}

