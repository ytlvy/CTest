/*
 * @Author: Y.t
 * @Date: 2021-05-24 23:07:59
 * @LastEditors: Y.t
 * @LastEditTime: 2021-05-25 09:49:31
 * @Description:  
 * build: g++ -std=c++17 removedup.cpp -o removedup & ./removedup
 */
#include <stdio.h>
#include <vector>
#include <iostream>
#include <functional>
#include <numeric>
#include <string>
#include <algorithm>
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
    int removeDuplicates(vector<int> &nums) {
        if(nums.empty()) {
            return 0;
        }

        sort(nums.begin(), nums.end(), [](const int &a, const int &b){ return a > b; });
        // sort( nums.begin(). nums.end(), greater<int>());

        printVector(nums);

        int index = 0;
        for (int i= 1; i < nums.size(); i++) {
            if(nums[index] != nums[i]){
                nums[++index] = nums[i];
            }
        }
        return index + 1;
    }
};



int main(int argc, char *argv[]) {
    // int n[] = {9, 2, 3 , 4, 9} ;
    // vector<int> digits(n, n+5);

    vector<int> v = {2, 0, 1, 5, 9, 2, 7};

    Solution solution;
    auto length = solution.removeDuplicates(v);

    printVector(v, length);
    
    return 0;
}
