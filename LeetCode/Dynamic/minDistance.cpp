/*
 * @Author: Y.t
 * @Date: 2021-06-21 23:16:57
 * @LastEditors: Y.t
 * @LastEditTime: 2021-06-22 11:20:54
 * @Description: 
* build: clang++ -std=c++17 longestConsecutive.cpp -o out && ./out
 */

#include <stdio.h>
#include <vector>
#include <iostream>
#include <functional>
#include <numeric>
#include <string>
#include <algorithm> // std::unique, std::distance
#include <iterator>  // std::distance
#include <stack>
#include "../helper.h"

typedef enum StringChoice_{
    StringChoice_PassBy = 0,
    StringChoice_Insert,
    StringChoice_Delete,
    StringChoice_Replace,
}StringChoice;

class Node {
    public:
    int val;
    StringChoice choice;
    Node(int val_=0): val(val_){}
    Node &operator=(const Node &other) {
        if(this == &other){
            return *this;
        }
        
        val = other.val;
        choice = other.choice;
        return *this;
    }
    bool operator < (const Node &other)const {
        return val > other.val;
    //     return std::tie(first_name, mid_name, last_name) < 
    //   std::tie(other.first_name, other.mid_name, other.last_name);
    }
};

class Solution
{

public:
    int minDistance1(string &s1, int start1, string &s2, int start2)
    {
        //base
        if (start1 == -1)
            return start2 + 1;
        if (start2 == -1)
            return start1 + 1;

        if (s1[start1] == s2[start2])
        {
            return minDistance1(s1, start1 - 1, s2, start2 - 1);
        }
        else
        {
            return kMIN(minDistance1(s1, start1 - 1, s2, start2),
                        minDistance1(s1, start1, s2, start2 - 1),
                       minDistance1(s1, start1 - 1, s2, start2 - 1)) +1;
        }
    }

    int minDistance(string &s1, string &s2)
    {
        int m = s1.size(), n = s2.size();

        vector<vector<Node>> dp (m+1);
        for (int i = 0; i <= m; i++)
            dp[i] = vector<Node>(n+1);

        for (int i = 1; i <= m; i++)
            dp[i][0].val = i;

        for (int i = 1; i <= n; i++)
            dp[0][i].val = i;

        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (s1[i - 1] == s2[j - 1])
                {
                    dp[i][j].val = dp[i - 1][j - 1].val;
                    dp[i][j].choice = StringChoice_PassBy;
                }
                else
                {
                    int minVal = dp[i][j - 1].val;
                    StringChoice choice = StringChoice_Insert;
                    if(dp[i - 1][j] < dp[i][j - 1]){
                        minVal = dp[i - 1][j].val;
                        choice = StringChoice_Delete;
                    }
                    if(minVal > dp[i-1][j-1].val){
                        minVal = dp[i-1][j-1].val;
                        choice = StringChoice_Replace;
                    }

                    dp[i][j].val = minVal + 1;
                    dp[i][j].choice = choice;
                }
            }
        }
        return dp[m][n].val;
    }
};

int main(int argc, char *argv[])
{
    string s1("horse");
    string s2("ros");

    Solution sol;
    auto length = sol.minDistance(s1, s2);
    cout << "find: " << length << endl;

    length = sol.minDistance1(s1, s1.size() - 1, s2, s2.size() - 1);
    cout << "find: " << length << endl;

    return 0;
}
