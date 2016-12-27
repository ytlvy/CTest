/*
 * =====================================================================================
 *
 *       Filename:  constTest.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015/04/14 15时44分58秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
int main(){
    int * const x;
    *x = 8;

    printf("str pointer address is :%p\n", x);
    *x = 9;
    printf("str pointer address is : %p", x);

    int *y;
   // *y = 10;
    //x = y;
    return 0;
}
