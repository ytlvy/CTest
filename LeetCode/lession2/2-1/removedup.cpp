/*
 * @Author: Y.t
 * @Date: 2021-05-24 23:07:59
 * @LastEditors: Y.t
 * @LastEditTime: 2021-05-25 23:24:24
 * @Description:  
 * build: g++ removedup.cpp -o out && ./out
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
        if(nums.empty()) {
            return 0;
        }

        int index = 0;
        for (int i= 1; i < nums.size(); i++) {
            if(nums[index] != nums[i]){
                nums[++index] = nums[i];
            }
        }
        return index + 1;
    }

    int removeDuplicates1(vector<int> &nums) {
        auto end = unique(nums.begin(), nums.end());
        return distance(nums.begin(), end);
    }

    int removeDuplicates2(vector<int> &nums) {
        
        return distance(nums.begin(), removeDuplicates(nums.begin(), 
            nums.end(), nums.begin()));
    }

    template <typename InIt, typename OutIt>
    OutIt removeDuplicates(InIt first, InIt last, OutIt output){
        while (first != last) {
            *output++ = *first;
            first = upper_bound(first, last, *first);
        }
        
        return output;
    }
};



int main(int argc, char *argv[]) {
    // int n[] = {9, 2, 3 , 4, 9} ;
    // vector<int> digits(n, n+5);

    vector<int> v = {2, 0, 1, 5, 9, 2, 7};

    sort(v.begin(), v.end(), [](const int &a, const int &b){ return a < b; });
    // sort( nums.begin(). nums.end(), greater<int>());
    

    Solution solution;
    auto v1 = v;
    printVector(v1);
    auto length = solution.removeDuplicates(v1);
    printVector(v, length);
    
    
    return 0;
}
