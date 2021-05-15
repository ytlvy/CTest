/*
clang -S -arch arm64 hello.c
*/


#include <stdio.h>
#include <stdint.h>

__uint128_t longMul(uint64_t x, uint64_t y) {
    return (__uint128_t)x * (__uint128_t)y;
}

//读取两个无符号整数, 将相乘结果输出
int main(void) {
    long x, y, lo, hi;

    printf("Enter a number in hex: ");
    scanf("%lx", &x);
    printf("Enter a number in hex: ");
    scanf("%lx", &y);

    __uint128_t prod = longMul(x, y);
    lo = (uint64_t)prod;
    hi = (uint64_t)(prod >>64);

    printf("%016lx * %016lx = %016lx%016lx\n", x, y, hi, lo);

    return 0;
}
