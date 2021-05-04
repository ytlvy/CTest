/*
gcc -O0 -o hello1.s -S hello1.c 

clang -S -arch arm64 hello.c

clang -S -arch arm64 -isysroot `xcrun --sdk iphoneos --show-sdk-path` hello1.c
*/

#include <stdio.h>
void printBinary(int val);

int main(void) {

    char c = getchar();
    fflush(stdin);
    printf("char: %c\n", c);
    printBinary((int)c);
    return 0;
}

void printBinary(int val) {

    for (int i = val & 1; val; val=val>>1, i = val&1)
    {
        printf("%d", i);
    }
    
    printf("\n");
}