/*
 * @Author: Y.t
 * @Date: 2021-06-09 09:51:00
 * @LastEditors: Y.t
 * @LastEditTime: 2021-06-17 16:16:12
 * @Description: 
* build: clang++ -std=c++17 tree.cpp -o out && ./out
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
#include <queue>

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


class Solution {

private:
    void _preOderTraversalHelper(TreeNode *node, vector<int> &res) {

        res.push_back(node->val);
        if(node->left != nullptr) _preOderTraversalHelper(node->left, res);
        if(node->right != nullptr) _preOderTraversalHelper(node->right, res);
    }

    void _inOderTraversalHelper(TreeNode *node, vector<int> &res) {

        if(node->left != nullptr) _inOderTraversalHelper(node->left, res);
        res.push_back(node->val);
        if(node->right != nullptr) _inOderTraversalHelper(node->right, res);
    }

    void _postOderTraversalHelper(TreeNode *node, vector<int> &res) {

        
        if(node->left != nullptr) _postOderTraversalHelper(node->left, res);
        if(node->right != nullptr) _postOderTraversalHelper(node->right, res);
        res.push_back(node->val);
    }

public:

    vector<int>preOrderTraversal(TreeNode *root) {
        vector<int>res;

        _preOderTraversalHelper(root, res);
        return res;
    }

    vector<int>inOrderTraversal(TreeNode *root) {
        vector<int>res;

        _inOderTraversalHelper(root, res);
        return res;
    }

    vector<int>postOrderTraversal(TreeNode *root) {
        vector<int>res;

        _postOderTraversalHelper(root, res);
        return res;
    }


    vector<int> preOrderTraversal1(TreeNode *root) {
        vector<int> res;
        stack<const TreeNode *>s;
        if(root != nullptr) s.push(root);

        while(!s.empty()) {
            const TreeNode *p = s.top();
            s.pop();

            res.push_back(p->val);

            if(p->right != nullptr) s.push(p->right);
            if(p->left != nullptr) s.push(p->left);
        }
        
        return res;
    }

    vector<int>inOrderTraversal1(TreeNode *root) {
        vector<int> res;
        stack<const TreeNode*> s;
        const TreeNode *p= root;
        

        while(!s.empty() || p != nullptr) {

            if(p != nullptr) {
                s.push(p);
                p = p->left;
            }
            else {
                p = s.top();
                s.pop();
                res.push_back(p->val);
                p = p->right;
            }
        }

        return res;
    }

    vector<int>postOrderTraversal1(TreeNode *root) {
        vector<int> res;
        stack<const TreeNode*> s;
        const TreeNode *cur = root;
        const TreeNode *pre = nullptr;

        do {
            //所有左子树进栈
            while(cur != nullptr){
                s.push(cur);
                cur = cur->left;
            }

            //空右输出
            while(!s.empty()){
                cur = s.top();
                s.pop();

                if(cur->right == nullptr || cur->right == pre){
                    res.push_back(cur->val);
                    pre = cur;
                }
                else {
                    s.push(cur);
                    cur = cur->right;
                    break;
                }
            }
            
        }while(!s.empty());

        return res;
    }

    vector<int> preOrderTraversal2(TreeNode *root) {
        vector<int> res;
        TreeNode *cur = root, *prev = nullptr;

        while(cur != nullptr) {
            if(cur->left == nullptr) {//没有左孩子
                res.push_back(cur->val);
                prev = cur;
                cur = cur->right;
            }
            else {
                //查找前驱
                TreeNode *node = cur->left;
                while(node->right != nullptr && node->right != cur) {
                    node = node->right;
                }

                if(node->right == nullptr) {//未线索, 打标记
                    res.push_back(cur->val);
                    node->right = cur;
                    prev = cur;
                    cur = cur->left;
                }
                else {
                    node->right = nullptr;
                    cur = cur->right;
                }
            }
        }
        return res;
    }

    
   
    
};



int main(int argc, char *argv[]) {  
    ///        1
    ///      2    3
    ///    4   5    6
    ///       7   8

    struct TreeNode *root = new TreeNode{1};
    root->left = new TreeNode{2};
    root->right = new TreeNode{3};
    root->left->left = new TreeNode{4};
    root->left->right = new TreeNode{5};
    root->right->right = new TreeNode{6};
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(8);

    Solution s;

    auto preRes = s.preOrderTraversal(root);
    printVector(preRes);

    preRes = s.preOrderTraversal1(root);
    printVector(preRes);

    // preRes = s.preOrderTraversal2(root);
    // printVector(preRes);

    cout<<"============in order=-=========="<<endl;

    preRes = s.inOrderTraversal(root);
    printVector(preRes);

    preRes = s.inOrderTraversal1(root);
    printVector(preRes);
    
    cout<<"=======================post order"<<endl;
    preRes = s.postOrderTraversal(root);
    printVector(preRes);

    preRes = s.postOrderTraversal1(root);
    printVector(preRes);

    return 0;
}

