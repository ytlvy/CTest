/*
 * =====================================================================================
 *
 *       Filename:  prog1.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015/05/25 20时49分53秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>
using namespace std;

void my_subroutine() {
    cout << "Hello world" << endl;
}

int main() {
    int x = 4;
    int *p = NULL;
    my_subroutine();
    *p = 3;
    cout << x << ", " << *p << endl;
    return 0;
}

