/*
 * @Author: Y.t
 * @Date: 2021-06-24 23:20:20
 * @LastEditors: Y.t
 * @LastEditTime: 2021-06-28 11:56:05
 * @Description: 
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
private:
    vector<vector<int>> dp;
public:
    void kmp(string &pattern){
        int m = pattern.size();
        for(int i=0; i<m; i++){
            dp.push_back(vector<int>(26, 0));
        }
        dp[0][pattern[0]-'A'] = 1;

        printVectors(dp);
        //影子状态
        int x = 0;
        for (int i = 1; i <m; i++) {
            for(int c =0; c < 26; c++) {
                dp[i][c] = dp[x][c];
            }
            dp[i][pattern[i]-'A'] = i + 1;
            x = dp[x][pattern[i]-'A'];
        }

        printVectors(dp);
    }

    void getNext(int *next, const string &s){
        int j = -1;
        next[0] = j;

        for(int i=1; i<s.size(); i++){
            while(j>=0 && s[i] != s[j+1]) {
                j = next[j];
            }

            if( s[i] == s[j+1]) {
                j++;
            }

            next[i] = j;
        }
    }

    int strStr(string haystack, string needle){
        if (needle.size() == 0) {
            return 0;
        }

        int next[needle.size()];
        getNext(next, needle);
        int j = -1;
        for(int i=0; i<haystack.size(); i++) {
            while(j>=0 && haystack[i] != needle[j+1]) {
                j = next[j];
            }

            if(haystack[i] == needle[j+1]) {
                j++;
            }

            if(j == needle.size()-1) {
                return (i - needle.size() + 1);
            }
        }
        return -1;
    }


    int search(string &s1, string &pattern) {
        int m = s1.size();
        int n = pattern.size();

        int j = 0;
        for(int i =0; i< n; i++) {
            int c = s1[i] - 'A';
            j = dp[j][c];
            if(j == m) return i-m+1;
        }

        return -1;
    }
   
    
};



int main(int argc, char *argv[]) {
    // int n[] = {9, 2, 3 , 4, 9} ;
    // vector<int> digits(n, n+5);

    string s = "ABABA";
    string pat = "BA";
    Solution solution;
    solution.kmp(pat);
    auto pos = solution.search(s, pat);
    cout<<"find: "<<pos<<endl;
    
    
    return 0;
}
