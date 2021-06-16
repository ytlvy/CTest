/*
 * @Author: Y.t
 * @Date: 2021-05-27 19:17:04
 * @LastEditors: Y.t
 * @LastEditTime: 2021-05-27 20:07:21
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


template <typename T, typename M>
void printMap(unordered_map<T, M> &map) {
    cout << "map: ";
    for(auto it= map.begin(); it != map.end(); it++) {
        cout << it->first <<"-"<< it->second <<"\t";
    }
    cout<<endl;
}

class Solution {

public:
    //最长连续数字
    int longestConsecutive(const vector<int> &nums) {
        unordered_map<int, bool> used;
        for(auto i: nums)  used[i] = false;

        int longest = 0;
        for(auto i: nums) {
            if(used[i]) continue;

            int length = 1;
            used[i] = true;

            for(int j = i+1; used.find(j) != used.end(); j++) {
                used[j] = true;
                ++length;
            }

            for(int j = i-1; used.find(j) != used.end(); --j) {
                used[j] = true;
                ++length;
            }

            longest = max(longest, length);
        }

        return longest;
    }

    int longestConsecutiveV1(vector<int> &nums) {
        unordered_map<int, int> map;
        int length = 1;
        for(auto i: nums) {
            cout<<"begin parse: "<<i<<endl;
            if(map.find(i) != map.end()) {
                cout<<i<<"already in passby"<<endl;
                continue;
            }            
            map[i] = 1;
            if(map.find(i - 1) != map.end()) {
                length = max(length, mergeCluster(map, i-1, i));
            }
            if(map.find(i + 1) != map.end()) {
                length = max(length, mergeCluster(map, i, i + 1));
            }
            printMap(map);
        }

        return nums.size() == 0 ? 0 : length;
    }

    private:
        int mergeCluster(unordered_map<int, int> &map, int left, int right) {
            int upper = right + map[right] - 1;
            int lower = left - map[left] + 1;
            int length = upper - lower + 1;
            map[upper] = length;
            map[lower] = length;
            cout<<endl<<"after merge "<<left << "->" <<right<<endl;
            printMap(map);
            return length;
        }
};



int main(int argc, char *argv[]) {
    // int n[] = {9, 2, 3 , 4, 9} ;
    // vector<int> digits(n, n+5);

    vector<int> v = {100, 4, 200, 1, 3, 2};

    Solution solution;
    printVector(v);
    auto length = solution.longestConsecutiveV1(v);
    cout<<"find: "<<length<<endl;
    
    
    return 0;
}
