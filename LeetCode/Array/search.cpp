/*
 * @Author: Y.t
 * @Date: 2021-05-25 23:21:10
 * @LastEditors: Y.t
 * @LastEditTime: 2021-05-27 10:01:30
 * @Description: 
 * build: clang++ -std=c++17 search.cpp -o out && ./out
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
    int searchInDupAndRotate(const vector<int>& nums, int target) {
        int first = 0, last = nums.size();
        while (first != last)
        {
            const int mid = first + (last - first) / 2;
            if (nums[mid] == target) {
                return mid;
            }
            else if (nums[first] < nums[mid]) {//前半段递增
                if(nums[first] <= target && target < nums[mid]){
                    last = mid;
                }
                else
                    first = mid + 1;
            }
            else if(nums[first] > nums[mid]){ //前半段递减
                if (nums[mid] < target && target <= nums[last-1]) {
                    first = mid + 1;
                }
                else 
                    last = mid;
            }
            else { //skip duplicate
                first++;
            }
        }
        return -1;
    }

    int searchInRotate(const vector<int>& nums, int target) {
        int first = 0, last = nums.size();
        while (first != last)
        {
            const int mid = first + (last - first) / 2;
            if (nums[mid] == target) {
                return mid;
            }
            else if (nums[first] <= nums[mid]) {//前半段递增
                //target 在前半部分
                if(nums[first] <= target && target < nums[mid]){
                    last = mid;
                }
                else//target 在后半部分
                    first = mid + 1;
            }
            else{ //后半段递增

                //target 在后半段
                if (nums[mid] < target && target <= nums[last-1]) {
                    first = mid + 1;
                }
                else 
                    last = mid;
            }
        }
        return -1;
    }

    double findMedianSortedArrays(const vector<int> & A, const vector<int> &B) {
        const int m = A.size();
        const int n = B.size();
        int total = m + n;
        if(total & 0x1) {

        }
        else {

        }
    }

    static int find_kth(vector<int>::const_iterator A, int m, 
        vector<int>::const_iterator B, int n, int k) {
        //always assume the m is equal or smaller than n
        if(m > n) return find_kth(B, n, A, m, k);

        assert(m <= n);
        if(m == 0) return *(B+k-1);
        if(n == 0) return min(*A, *B);

        // 将A, B 数组划分为 4 部分,  
        // 其中 A的前部分和B的前部分和为k个
        
        int ia = min(k/2, m);
        int ib = k - ia;

        if(*(A+ia-1) < *(B+ib-1)) {
            return find_kth(A+ia, m-ia, B, n, k-ia);
        }
        else if(*(A + ia -1) > *(B + ib - 1)) {
            return find_kth(A, m, B+ib, n-ib, k-ib);
        }
        else {
            return A[ia - 1];
        }

    }
    
};



int main(int argc, char *argv[]) {
    // int n[] = {9, 2, 3 , 4, 9} ;
    // vector<int> digits(n, n+5);

    vector<int> v = {0, 1, 1, 1, 2, 2, 3};
    vector<int> v1 = {2, 2, 3, 0, 1, 1, 1};

    Solution solution;
    printVector(v1);
    auto length = solution.searchInDupAndRotate(v1, 2);
    cout<<"find"<<length<<endl;
    
    
    return 0;
}