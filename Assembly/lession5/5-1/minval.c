/*
clang -S -arch arm64 minval.c
*/

#include <stdio.h>

static long a = 0x57;
static long b = 0x75;
static long c = 0x21;
static long x;
static long y;

int main(void) {

    if ((a < b) && (a < c) ) {
        x = a;
    }
    else if (b < c) {
        x = b;
    }
    else {
        x = c;
    }

    y = x;
    return 0;
}