/*
 * @Author: Y.t
 * @Date: 2021-08-03 15:55:40
 * @LastEditors: Y.t
 * @LastEditTime: 2021-08-03 16:00:57
 * @Description: 
 */
#include "add1.h"
#include <iostream>

int callCnt;

int Add(int *x, int *y, int *z) {
    callCnt++;
    std::cout<<" add in add1 lib" << std::endl;
    return *x + *y;
}

void Fun2() {
    std::cout<< "Fun2 in add1 lib" << std::endl;
}
