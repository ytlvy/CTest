/*
 * @Author: Y.t
 * @Date: 2021-06-17 19:59:28
 * @LastEditors: Y.t
 * @LastEditTime: 2021-06-17 20:25:43
 * @Description: 
 */

#include<vector>
#include<iostream>
#include<queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) :val(x), left(nullptr), right(nullptr){}
};

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

TreeNode *makeTree(vector<int> &nums) {
    if(nums.size() == 0) return nullptr;
    queue<int> q2;

    queue<int> q1;
    queue<TreeNode *>q_t;

    q1.push(nums[0]);
    TreeNode *curNode = nullptr;
    
    int i =0;
    while(i<nums.size()) {
        
        
        while(!q1.empty()) {
            int cur = q1.front();
            q1.pop();
            
            TreeNode *node = new TreeNode(cur);
            
        }
        
    }
}