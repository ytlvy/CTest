/*
 * @Author: Y.t
 * @Date: 2021-08-03 10:57:22
 * @LastEditors: Y.t
 * @LastEditTime: 2021-08-03 16:44:03
 * @Description: 
 */
#include <iostream>

using namespace std;

extern "C" int Add(int *x, int *y);
void Fun1();
void Fun2();

int x = 1;
int y = 2;

int main(void) {
    Add(&x, &y);

    Fun1();
    Fun2();
    return 0;
}