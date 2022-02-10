/*
 * @Author: Y.t
 * @Date: 2021-06-09 09:51:00
 * @LastEditors: Y.t
 * @LastEditTime: 2021-10-15 23:27:43
 * @Description: 
* build: clang++ -std=c++17 tree.cpp -o out && ./out
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
#include <queue>
#include "../helper.h"

class Solution
{

private:
    void _preOderTraversalHelper(TreeNode *node, vector<int> &res);
    void _inOderTraversalHelper(TreeNode *node, vector<int> &res);
    void _postOderTraversalHelper(TreeNode *node, vector<int> &res);
    bool _isValidBST(TreeNode *root, TreeNode *min, TreeNode *max);
public:
    int maxDepth2(TreeNode *root);
    bool isBalance(TreeNode *root);
    int numOfLevelNodes(TreeNode *root, int k);
    int numOfNodes(TreeNode *root);
    int numOfLeaves(TreeNode *root);
    int minDepth_(TreeNode *node);
    int minDepth(TreeNode *root);
    int maxDepth(TreeNode *root);

    vector<int> preOrderTraversal2(TreeNode *root);
    vector<int> postOrderTraversal1(TreeNode *root);
    vector<int> inOrderTraversal1(TreeNode *root);
    vector<int> preOrderTraversal1(TreeNode *root);
    vector<int> postOrderTraversal(TreeNode *root);
    vector<int> inOrderTraversal(TreeNode *root);
    vector<int> preOrderTraversal(TreeNode *root);

    bool isTreeSame(TreeNode *t1, TreeNode *t2);
    bool isMirror(TreeNode *t1, TreeNode *t2);
    TreeNode *mirrorTree(TreeNode *root);
    bool findNode(TreeNode *root, TreeNode *node);
    TreeNode *lastCommonParent(TreeNode *root, TreeNode *t1, TreeNode *t2);
    TreeNode *trimBST(TreeNode *root, int low, int high);
    bool isValidBST(TreeNode *root);
};

void Solution::_preOderTraversalHelper(TreeNode *node, vector<int> &res)
{

    res.push_back(node->val);
    if (node->left != nullptr)
        _preOderTraversalHelper(node->left, res);
    if (node->right != nullptr)
        _preOderTraversalHelper(node->right, res);
}

void Solution::_inOderTraversalHelper(TreeNode *node, vector<int> &res)
{

    if (node->left != nullptr)
        _inOderTraversalHelper(node->left, res);
    res.push_back(node->val);
    if (node->right != nullptr)
        _inOderTraversalHelper(node->right, res);
}

void Solution::_postOderTraversalHelper(TreeNode *node, vector<int> &res)
{

    if (node->left != nullptr)
        _postOderTraversalHelper(node->left, res);
    if (node->right != nullptr)
        _postOderTraversalHelper(node->right, res);
    res.push_back(node->val);
}

vector<int> Solution::preOrderTraversal(TreeNode *root)
{
    vector<int> res;

    _preOderTraversalHelper(root, res);
    return res;
}

vector<int> Solution::inOrderTraversal(TreeNode *root)
{
    vector<int> res;

    _inOderTraversalHelper(root, res);
    return res;
}

vector<int> Solution::postOrderTraversal(TreeNode *root)
{
    vector<int> res;

    _postOderTraversalHelper(root, res);
    return res;
}

vector<int> Solution::preOrderTraversal1(TreeNode *root)
{
    vector<int> res;
    stack<const TreeNode *> s;
    if (root != nullptr)
        s.push(root);

    while (!s.empty())
    {
        const TreeNode *p = s.top();
        s.pop();

        res.push_back(p->val);

        if (p->right != nullptr)
            s.push(p->right);
        if (p->left != nullptr)
            s.push(p->left);
    }

    return res;
}

vector<int> Solution::inOrderTraversal1(TreeNode *root)
{
    vector<int> res;
    stack<const TreeNode *> s;
    const TreeNode *p = root;

    while (!s.empty() || p != nullptr)
    {

        if (p != nullptr)
        {
            s.push(p);
            p = p->left;
        }
        else
        {
            p = s.top();
            s.pop();
            res.push_back(p->val);
            p = p->right;
        }
    }

    return res;
}

vector<int> Solution::postOrderTraversal1(TreeNode *root)
{
    vector<int> res;
    stack<const TreeNode *> s;
    const TreeNode *cur = root;
    const TreeNode *pre = nullptr;

    do
    {
        //所有左子树进栈
        while (cur != nullptr)
        {
            s.push(cur);
            cur = cur->left;
        }

        //空右输出
        while (!s.empty())
        {
            cur = s.top();
            s.pop();

            if (cur->right == nullptr || cur->right == pre)
            {
                res.push_back(cur->val);
                pre = cur;
            }
            else
            {
                s.push(cur);
                cur = cur->right;
                break;
            }
        }

    } while (!s.empty());

    return res;
}

vector<int> Solution::preOrderTraversal2(TreeNode *root)
{
    vector<int> res;
    TreeNode *cur = root, *prev = nullptr;

    while (cur != nullptr)
    {
        if (cur->left == nullptr)
        { //没有左孩子
            res.push_back(cur->val);
            prev = cur;
            cur = cur->right;
        }
        else
        {
            //查找前驱
            TreeNode *node = cur->left;
            while (node->right != nullptr && node->right != cur)
            {
                node = node->right;
            }

            if (node->right == nullptr)
            { //未线索, 打标记
                res.push_back(cur->val);
                node->right = cur;
                prev = cur;
                cur = cur->left;
            }
            else
            {
                node->right = nullptr;
                cur = cur->right;
            }
        }
    }
    return res;
}
//最大深度
int Solution::maxDepth(TreeNode *root)
{
    if (root == nullptr)
        return 0;
    return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}

//最小深度
int Solution::minDepth(TreeNode *root)
{
    if (root == nullptr)
        return 0;

    return minDepth_(root);
}

int Solution::minDepth_(TreeNode *node)
{
    //一个子树为空时，不是叶子节点要继续寻找
    if (node == nullptr)
        return INT_MAX;

    if (node->left == nullptr && node->right == nullptr)
        return 1;

    return min(minDepth_(node->left), minDepth_(node->right)) + 1;
}

int Solution::numOfLeaves(TreeNode *root)
{
    if (root == nullptr)
        return 0;
    if (root->left == nullptr && root->right == nullptr)
        return 1;

    int left = numOfLeaves(root->left);
    int right = numOfLeaves(root->right);
    return left + right;
}

int Solution::numOfNodes(TreeNode *root)
{
    if (root == nullptr)
        return 0;

    int left = numOfNodes(root->left);
    int right = numOfNodes(root->right);
    return left + right + 1;
}

int Solution::numOfLevelNodes(TreeNode *root, int k)
{
    if (k < 1 || root == nullptr)
        return 0;

    if (k == 1)
        return 1;

    int left = numOfLevelNodes(root->left, k - 1);
    int right = numOfLevelNodes(root->right, k - 1);
    return left + right;
}

bool Solution::isBalance(TreeNode *root)
{

    return maxDepth2(root) != -1;
}

int Solution::maxDepth2(TreeNode *root)
{
    if (root == nullptr)
        return 0;

    int left = maxDepth2(root->left);
    int right = maxDepth2(root->right);
    if (left == -1 || right == -1 || abs(long(left - right)) > 1)
    {
        return -1;
    }
    return max(left, right) + 1;
}

/**/

bool Solution::isTreeSame(TreeNode *t1, TreeNode *t2)
{
    if (t1 == nullptr && t2 == nullptr)
    {
        return true;
    }

    if (t1 == nullptr || t2 == nullptr)
    {
        return false;
    }

    if (t1->val != t2->val)
    {
        return false;
    }

    return isTreeSame(t1->left, t2->left) && isTreeSame(t1->right, t2->right);
}

bool Solution::isMirror(TreeNode *t1, TreeNode *t2)
{
    if (t1 == nullptr && t2 == nullptr)
    {
        return true;
    }
    if (t1 == nullptr || t2 == nullptr)
    {
        return false;
    }

    if (t1->val != t2->val)
    {
        return false;
    }

    return isMirror(t1->left, t2->right) && isMirror(t1->right, t2->left);
}

TreeNode *Solution::mirrorTree(TreeNode *root)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    TreeNode *left = mirrorTree(root->left);
    TreeNode *right = mirrorTree(root->right);
    root->left = right;
    root->right = left;
    return root;
}

bool Solution::findNode(TreeNode *root, TreeNode *node)
{
    if (root == nullptr || node == nullptr)
    {
        return false;
    }
    if (root == node)
    {
        return true;
    }

    bool found = findNode(root->left, node);
    if (!found)
    {
        found = findNode(root->right, node);
    }
    return found;
}

TreeNode *Solution::lastCommonParent(TreeNode *root, TreeNode *t1, TreeNode *t2)
{
    if (findNode(root->left, t1))
    {
        if (findNode(root, t2))
        {
            return root;
        }
        else
        {
            return lastCommonParent(root->left, t1, t2);
        }
    }
    else
    {
        if (findNode(root->left, t2))
        {
            return root;
        }
        else
        {
            return lastCommonParent(root->right, t1, t2);
        }
    }
}

//选中在low, high 中间的节点
TreeNode *Solution::trimBST(TreeNode *root, int low, int high)
{
    if (root == nullptr)
        return nullptr;

    //选择右子树
    if (root->val < low)
    {
        TreeNode *right = trimBST(root->right, low, high);
        return right;
    }

    //选择左子树
    if (root->val > high)
    {
        TreeNode *left = trimBST(root->left, low, high);
        return left;
    }

    root->left = trimBST(root->left, low, high);
    root->right = trimBST(root->right, low, high);
    return root;
}

bool Solution::isValidBST(TreeNode *root)
{
    return _isValidBST(root, nullptr, nullptr);
}

bool Solution::_isValidBST(TreeNode *root, TreeNode *min, TreeNode *max) {
    if(root == nullptr) return true;
    if(min != nullptr && root->val <= min->val) return false;
    if(max != nullptr && root->val >= max->val) return false;

    return _isValidBST(root->left, min, max) && _isValidBST(root->right, min, max);
    
}

int main(int argc, char *argv[])
{
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

    vector<int> nodes{1, 2, 3, 4, 5, INT_MIN, 6, INT_MIN, INT_MIN, 7, 8};
    TreeNode *root1 = nullptr;
    makeTree(&root1, nodes);

    Solution s;

    auto preRes = s.preOrderTraversal(root);
    printVector(preRes);

    preRes = s.preOrderTraversal1(root1);
    printVector(preRes);

    // preRes = s.preOrderTraversal2(root);
    // printVector(preRes);

    cout << "============in order=-==========" << endl;

    preRes = s.inOrderTraversal(root);
    printVector(preRes);

    preRes = s.inOrderTraversal1(root1);
    printVector(preRes);

    cout << "=======================post order" << endl;
    preRes = s.postOrderTraversal(root);
    printVector(preRes);

    preRes = s.postOrderTraversal1(root1);
    printVector(preRes);

    return 0;
}
