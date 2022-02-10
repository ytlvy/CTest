/*
 * @Author: Y.t
 * @Date: 2021-06-29 23:03:05
 * @LastEditors: Y.t
 * @LastEditTime: 2021-06-29 23:28:16
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

public:
    Solution(void) : succesor(nullptr){}
    ListNode *reverse(ListNode *root) {
        if(root->next == nullptr) return root;

        ListNode *last = reverse(root->next);
        root->next->next = root;
        root->next = nullptr;
        return last;
    }
   
    
    ListNode *reverse(ListNode *head, int n) {
        if(n == 1 || head->next == nullptr) {
            succesor = head->next;
            return head;
        }

        //shoud add head->next nullptr
        auto last = reverse(head->next, n-1);
        head->next->next = head;
        head->next = succesor;
        return last;
    }
    private:
    ListNode *succesor;    
    
};



int main(int argc, char *argv[]) {

    vector<int> v = {0, 1, 3, 5, 7, 8, 10};

    ListNode *root = makeList(v);
    printList(root);
    Solution solution;    
    ListNode *newroot = solution.reverse(root, 11);
    printList(newroot);
    
    
    return 0;
}
