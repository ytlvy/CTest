#include <stdio.h>



int main(void) {
    
static int i = 0, j = 1;
static char ch[] = {'A', 'B' , '0'};
static int ary[] = {1, 2, 3, 4};
    printf("hello world");
    return 0;
}

/*
gcc -O0 -o hello1.s -S hello1.c 

clang -S -arch arm64 hello1.c

clang -S -arch arm64 -isysroot `xcrun --sdk iphoneos --show-sdk-path` hello1.c
*/