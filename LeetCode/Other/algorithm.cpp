/*
 * @Author: Y.t
 * @Date: 2021-06-22 08:26:32
 * @LastEditors: Y.t
 * @LastEditTime: 2021-06-22 08:55:10
 * @Description: 
* build: clang++ -std=c++17 longestConsecutive.cpp -o out && ./out
 */

#include <stdio.h>
#include <vector>
#include <iostream>
#include <functional>
#include <numeric>
#include <string>
#include <algorithm> // unique, distance
#include <iterator>  // distance
#include <stack>
#include "helper.h"

bool mycomp(int i, int j)
{
    return (i < j);
}

class mycomp2 {
public:
    bool operator()(const int& i) {
        return ((i % 2) == 1);
    }
};

class Solution
{

public:
    void doReplace(void)
    {
        deque<int> data{10, -5, 12, -6, 10, 8, -7, 10, 11};
        replace(begin(data), end(data), 10, 99);
        // Result: 99 -5 12 -6 99 8 -7 99 11
    }

    void doSort(void)
    {
        vector<int> myvector{32, 71, 12, 45, 26, 80, 53, 33};

        stable_sort(myvector.begin(), myvector.begin() + 4);
        //(12 32 45 71) 26 80 53 33

        stable_sort(myvector.begin(), myvector.begin() + 4, greater<int>());
        //(71 45 32 12) 26 80 53 33

        stable_sort(myvector.begin(), myvector.end(), mycomp);

        //以默认的升序排序作为排序规则，将 myvector 中最小的 4 个元素移动到开头位置并排好序
        partial_sort(myvector.begin(), myvector.begin() + 4, myvector.end());
        printVector(myvector);

        vector<double> deg_F(myvector.size());
        transform(myvector.begin(), myvector.end(), deg_F.rbegin(),
                  [](double temp)
                  { return 32.0 + 9.0 * temp / 5.0; });
    }

    void doRemove(void)
    {
        deque<double> samples{1.5, 2.6, 0.0, 3.1, 0.0, 0.0, 4.1, 0.0, 6.7, 0.0};
        samples.erase(remove(begin(samples), end(samples), 0.0), end(samples));
        copy(begin(samples), end(samples), ostream_iterator<double>{cout, " "});
        cout << endl;


        vector<double> edited_samples;
        remove_copy(begin(samples), end(samples), back_inserter(edited_samples), 0.0);
    }

    void doInitVector(void){
        vector<string> data {12};
        fill (begin (data), end (data), "none"); // Set all elements to "none"
    }
    
    void doFind(void){
        vector<int> myvector{ 4,2,3,1,5 };
        //调用 find_if() 函数，并以 IsOdd() 一元谓词函数作为查找规则
        vector<int>::iterator it = find_if(myvector.begin(), myvector.end(), mycomp2());
        cout << "*it = " << *it;
    }
};

int main(int argc, char *argv[])
{

    vector<int> v = {0, 1, 3, 5, 7, 8, 10};
    vector<int> v1 = {4, 6, 7, 8};

    Solution solution;
    printVector(v1);

    return 0;
}
