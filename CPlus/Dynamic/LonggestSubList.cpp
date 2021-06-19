#include <iostream>

using namespace std;

int longestSubList(int A[], int length) {
    int *statePool = new int[length]; //新建状态临时存储
    int longstLen = 1; //设置初始最大长度1

    for(int i=0; i<length; i++) {//遍历所有列表
        statePool[i] = 1; //初始化i状态最长为1

        for(int j=0;j<i;j++) {
            if(A[j]<=A[i] && statePool[j]+1>statePool[i]) { //满足存在前置子序列
                statePool[i] = statePool[j]+1;
            }

            if(statePool[i]>longstLen) longstLen = statePool[i];
        }

    }

    delete[] statePool;
    return longstLen;
}

int main (void) {
    int A[] = {
        5, 3, 4, 8, 6, 7
    };

    cout<<"hello"<<endl;
    cout<<longestSubList(A, 6)<<endl;

    return 0;
}