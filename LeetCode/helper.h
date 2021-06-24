/*
 * @Author: Y.t
 * @Date: 2021-06-17 19:59:28
 * @LastEditors: Y.t
 * @LastEditTime: 2021-06-22 08:41:25
 * @Description: 
 */

#include<vector>
#include<iostream>
#include<queue>
#include<cmath>
#include<cstdio>


using namespace std;

#define kMIN(s1, s2, s3)  min( min( (s1), (s2) ), (s3) )


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

int makeTree(TreeNode **root, vector<int> &nums) {
    if(nums.size() == 0) return 0;

    queue<TreeNode *> q1;
    queue<TreeNode *> q2;
        
    for(size_t i =0; i<nums.size(); i++) {
        if(q1.empty()) { //root
            TreeNode *node = new TreeNode(nums[i]);
            q1.push(node);
            *root = node;
            continue;
        }
        
        TreeNode* curNode = q1.front();
        q1.pop();
        
        int val = nums[i++];
        if(val != INT_MIN){
            TreeNode *left = new TreeNode(val);
            curNode->left = left;
            q2.push(left);
        }

        if(i< nums.size()) {
            int rval = nums[i];
            if(rval != INT_MIN){
                TreeNode *right = new TreeNode(nums[i]);
                curNode->right = right;
                q2.push(right);
            }
        }
        
        if(q1.empty()) {
            swap(q1, q2);
        }
    }

    return 0;
}

void memory_dump(void *ptr, int len) {
    int i;

    for (i = 0; i < len; i++) {
        if (i % 8 == 0 && i != 0)
            std::cout << " ";
        if (i % 16 == 0 && i != 0)
            std::cout << endl;
        printf("%02x ", *((uint8_t *)ptr + i));
    }
    std::cout << endl;
}

void display(int** a, int r, int c){
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            cout << a[i][j] << ' ';
        }
        cout << endl;
    }
}

namespace mem
{
    std::string IntToHexa(int num)
    { 
        int values[2];
        int rest;
        for(int i = 0; i < 2; i++)
        {
            rest = num % 16;
            if(rest == 0 && num > 0)
            {
                values[i] = num/16;
            }else{
                values[i] = num % 16;
            }
            num -= values[i] * std::pow(16, i);

            if(values[i] > 9)
            {
                values[i] = 65 + values[i] - 10;
            }
        }

        std::string output;
        for(int i = 1; i > -1; i--)
        {
            if(values[i] > 10)
            {
                output += char(values[i]);
            }else{
                output += std::to_string(values[i]);
            }
        }
    return output;
    }

    template<typename POINTER>
    void MemView(POINTER pointer, int length = 10, int lines = 1)
    {
        unsigned char* ptr= (unsigned char*)pointer;
        for(int x = 0; x < lines; x++)
        {
            std::cout << (void*)ptr << "   ";
            for(int i = 0; i < length; i++)
            {
                std::cout << IntToHexa((int)*ptr) << "  ";
                ptr++;
            }
            std::cout << std::endl;
        }
    }
}