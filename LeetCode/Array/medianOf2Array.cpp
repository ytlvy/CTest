/*
 * @Author: Y.t
 * @Date: 2021-05-27 19:04:16
 * @LastEditors: Y.t
 * @LastEditTime: 2021-05-27 19:16:17
 * @Description: 
* build: clang++ -std=c++17 medianOf2Array.cpp -o out && ./out
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

    double findMedianSortedArrays(const vector<int> & A, const vector<int> &B) {
        const int m = A.size();
        const int n = B.size();
        int total = m + n;
        if(total & 0x1) {
            return find_kth(A.begin(), m, B.begin(), n, total/2 + 1);
        }
        else {
            return (find_kth(A.begin(), m, B.begin(), n, total/2) +
            find_kth(A.begin(), m, B.begin(), n, total/2 + 1)) / 2;
        }
    }

    static int find_kth(vector<int>::const_iterator A, int m, 
        vector<int>::const_iterator B, int n, int k) {
        //always assume the m is equal or smaller than n
        if(m > n) return find_kth(B, n, A, m, k);

        assert(m <= n);
        if(m == 0) return *(B+k-1);
        if(k == 1) return min(*A, *B);

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

    vector<int> v = {0, 1, 3, 5, 7, 8, 10};
    vector<int> v1 = {4, 6, 7, 8};

    Solution solution;
    printVector(v1);
    auto length = solution.findMedianSortedArrays(v, v1);
    cout<<"find: "<<length<<endl;
    
    
    return 0;
}