/*
 * @Author: Y.t
 * @Date: 2021-06-30 23:31:48
 * @LastEditors: Y.t
 * @LastEditTime: 2021-07-01 00:05:21
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
#include <stack>
#include "../helper.h"

class Solution {
private:
    vector<vector<string>>res;
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<string> board(n, string(n, '.'));
        backtrack(board, 0);
        return res;
    }

    void backtrack(vector<string> &board, int row) {
        if (row == board.size()) {
            res.push_back(board);
            return;
        }

        int n = board[row].size();
        for(int col = 0; col < n; col++) {
            if(!isValid(board, row, col)) continue;
            
            board[row][col] = 'Q';
            backtrack(board, row + 1);
            board[row][col] = '.';
        }
    }
   
    bool isValid(vector<string> &board, int row, int col) {
        int n = board.size();
        
        //正上方
        for(int i=0; i<row; i++) {
            if(board[i][col] == 'Q') return false;
        }

        //右上方
        for(int i=row-1, j=col+1; i>=0&&j<n; i--,j++) {
           if(board[i][j] == 'Q') return false; 
        }

        //左上方
        for(int i=row-1, j=col-1; i>=0&&j>=0; i--,j--) {
           if(board[i][j] == 'Q') return false; 
        }
        return true;
    }
    
};



int main(int argc, char *argv[]) {
    // int n[] = {9, 2, 3 , 4, 9} ;
    // vector<int> digits(n, n+5);

    vector<int> v = {0, 1, 3, 5, 7, 8, 10};
    vector<int> v1 = {4, 6, 7, 8};

    Solution solution;
    printVector(v1);
    // auto length = solution.findMedianSortedArrays(v, v1);
    // cout<<"find: "<<length<<endl;
    
    
    return 0;
}
