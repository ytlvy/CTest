/*
 * @Author: Y.t
 * @Date: 2021-05-16 10:55:25
 * @LastEditors: Y.t
 * @LastEditTime: 2021-05-16 22:24:59
 * @Description: This file provides funcitons for caculating sine and cosin using fixed-point
 *  arithmetic. It uses the firstt nine terms in the Taylor series
 */

#include <stdio.h>
#include "fixedfuncs.h"

struct tabentry{
    int coeff;
    int shift;
};

//create a table of coefficients and shift amounts.
#define TABSIZE  8
static struct tabentry sintab[]={
    {0xAAAAAAAA, 0}, // term 2 
    {0x44444445, 2}, // term 3 
    {0x97F97F97, 6}, // term 4 
    {0x5C778E96, 10}, // term 5 
    {0x9466EA60, 15}, // term 6 
    {0x5849184F, 20}, // term 7 
    {0x94603063, 26}, // term 8 
    {0x654B1DC1, 32} // term 9
};

// sinq is used internally by the sin and cosin functions
// input: x as an S(1, 30), s.t. 0 <= x <= pi/2
// returns sin(x) as an S(3, 28)
// S(3, 28) fixed point float
static int sinq(int x) {
    long long sum = (long long) x << 31;// init 64 bit sum to x
    long long curpower = x;
    long long xsq = (long long)x * (long long)x;
    xsq >>=31;
    long long tmp = 0;
    int i = 0;
    do {
        curpower = (curpower * xsq) >> 31;
        tmp = curpower * sintab[i].coeff;
        if(tmp < 0) {
            tmp ++;
        }
        tmp >>= sintab[i].shift;
        sum += tmp;
    }while(++i < TABSIZE);

    return sum >> 33;
}

int fixed_sin_C(int x) {
    while(x<0) {
        x += kpi_x2;
    }
    while (x>kpi_x2)
    {
        x -= kpi_x2;
    }
    if(x <= kpi_2) {
        return sinq(x << 2);
    }
    if(x<=kpi) {
        return sinq( (kpi-x) << 2 );
    }
    if(x<=kpi+kpi_2) {
        return -sinq( (x-kpi) <<2);
    }
    return -sinq((kpi_x2-x) <<2);
}

int fixed_cos_C(int x) {
    if(x<=0) {
        x += kpi_x2;
    }
    x = kpi_2 - x;
    return fixed_sin_C(x);
}
