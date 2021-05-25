/*
 * @Author: Y.t
 * @Date: 2021-05-25 20:00:24
 * @LastEditors: Y.t
 * @LastEditTime: 2021-05-25 22:58:27
 * @Description: 
 * build: g++ -std=c++17 removedup.cpp -o out && ./out
 * g++ removedup.cpp -o out && ./out
 */
#include <stdio.h>
#include <vector>
#include <iostream>
#include <functional>
#include <numeric>
#include <string>
#include <algorithm>    // std::unique, std::distance
#include <iterator>     // std::distance

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
        if(nums.size() <= 2) {
            return nums.size();
        }

        int index = 2;
        for (int i = 2; i < nums.size(); i++) {
            if(nums[i] != nums[index - 2]) {
                nums[index++] = nums[i];
            }
        }
        
        return index;
    }

    int removeDuplicates1(vector<int> &nums) {
        const int n = nums.size();

        int index = 0;
        for (int i = 0; i < n; i++)
        {
            if(i > 0 && i < n -1 && nums[i] == nums[i-1] && 
                nums[i] == nums[i+1]) {
                continue;
            }
            nums[index++] = nums[i];
        }
        return index;
    }

    int removeDuplicates2(vector<int> &nums) {
        const int n = nums.size();

        int index = 0;
        int occur = 0;
        for (int i = 0; i < n; i++)
        {
            if(occur < 2) {
                nums[index++] = nums[i];
            }
            
            if(nums[i] == nums[i+1]) {
                occur ++;
            }
            else {
                occur = 0;
            }
        }
        return index;
    }
    
};



int main(int argc, char *argv[]) {
    // int n[] = {9, 2, 3 , 4, 9} ;
    // vector<int> digits(n, n+5);

    vector<int> v = {0, 1, 1, 1, 2, 2, 3};

    Solution solution;
    auto v1 = v;
    printVector(v1);
    auto length = solution.removeDuplicates(v1);
    printVector(v1, length);

    auto v2 = v;
    printVector(v2);
    length = solution.removeDuplicates2(v2);
    printVector(v2, length);
    
    
    return 0;
}