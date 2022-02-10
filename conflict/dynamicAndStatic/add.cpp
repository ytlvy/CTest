/*
 * @Author: Y.t
 * @Date: 2021-08-03 15:55:49
 * @LastEditors: Y.t
 * @LastEditTime: 2021-08-03 15:58:54
 * @Description: 
 */

#include "add.h"
#include <iostream>

int callCnt;

int Add(int *x, int *y) {
    callCnt++;
    std::cout<<" add in add lib" << std::endl;
    return *x + *y;
}

void Fun1() {
    std::cout<< "Fun1 in add lib" << std::endl;
}
