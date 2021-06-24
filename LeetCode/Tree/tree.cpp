/*
 * @Author: Y.t
 * @Date: 2021-06-09 09:51:00
 * @LastEditors: Y.t
 * @LastEditTime: 2021-06-24 19:48:58
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
#include "../../helper.h"

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
    //最大深度
    int maxDepth(TreeNode *root){
        if(root == nullptr) return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
   
    //最小深度
    int minDepth(TreeNode *root) {
        if(root == nullptr) return 0;

        return minDepth_(root);
    }

    int minDepth_(TreeNode *node) {
        //一个子树为空时，不是叶子节点要继续寻找
        if(node == nullptr) return INT_MAX;

        if(node->left == nullptr && node->right==nullptr) return 1;

        return min(minDepth_(node->left), minDepth_(node->right)) + 1;
    }

    int numOfLeaves(TreeNode *root) {
       if(root == nullptr) return 0;
       if(root->left == nullptr && root->right == nullptr) return 1;

       int left = numOfLeaves(root->left);
       int right = numOfLeaves(root->right);
       return left + right;
    }

    int numOfNodes(TreeNode *root){
        if(root == nullptr) return 0;

        int left = numOfNodes(root->left);
        int right = numOfNodes(root->right);
        return left+right+1;
    }

    int numOfLevelNodes(TreeNode *root, int k){
        if(k < 1 || root = nullptr) return 0;

        if(k==1) return 1;

        int left = numOfLevelNodes(root->left, k-1);
        int right = numOfLevelNodes(root->right, k-1);
        return left + right;
    }

    bool isBalance(TreeNode *root) {

        return maxDepth2(root) != -1;
    }
    

    int maxDepth2(TreeNode *root) {
        if(root == nullptr) return 0;

        int left = maxDepth2(root->left);
        int right = maxDepth2(root->right);
        if(left == -1 || right == -1 || abs(left - right)>1) {
            return -1;
        }
        return max(left, right) + 1;
    }

    bool isTreeSame(TreeNode *t1, TreeNode *t2) {
        if(t1 == nullptr && t2 == nullptr){
            return true;
        }

        if(t1 == nullptr || t2 == nullptr){
            return false;
        }

        if(t1->val != t2->val) {
            return false;
        }

        return isTreeSame(t1->left, t2->left) && isTreeSame(t1->right, t2->right);
    } 


    bool isMirror(TreeNode *t1, TreeNode *t2) {
        if(t1 == nullptr && t2 == nullptr){
            return true;
        }
        if(t1 == nullptr || t2 == nullptr) {
            return false;
        }

        if(t1->val != t2->val) {
            return false;
        }

        return isMirror(t1->left, t2->right) && isMirror(t1->right, t2->left);
    }


    TreeNode *mirrorTree(TreeNode *root) {
        if(root == nullptr) {
            return nullptr;
        }

        TreeNode *left = mirrorTree(root.left);
        TreeNode *right = mirrorTree(root.right);
        root->left = right;
        root->right = left;
        return root;
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

    vector<int> nodes {1, 2, 3, 4, 5, INT_MIN, 6, INT_MIN, INT_MIN, 7, 8};
    TreeNode *root1 =nullptr;
    makeTree(&root1, nodes);
    
    Solution s;

    auto preRes = s.preOrderTraversal(root);
    printVector(preRes);

    preRes = s.preOrderTraversal1(root1);
    printVector(preRes);

    // preRes = s.preOrderTraversal2(root);
    // printVector(preRes);

    cout<<"============in order=-=========="<<endl;

    preRes = s.inOrderTraversal(root);
    printVector(preRes);

    preRes = s.inOrderTraversal1(root1);
    printVector(preRes);
    
    cout<<"=======================post order"<<endl;
    preRes = s.postOrderTraversal(root);
    printVector(preRes);

    preRes = s.postOrderTraversal1(root1);
    printVector(preRes);

    return 0;
}

