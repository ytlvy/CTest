/*
0000000100000f2f    leaq    -0x14(%rbp), %rcx

0000000100000f41    movl    $0x3, -0x14(%rbp)

0000000100000f48    movq    %rcx, -0x20(%rbp)
0000000100000f4c    movq    %rcx, -0x28(%rbp)
*/

#include <iostream>

int main(int argc, char** argv) {
    int i =3;

    int *j = &i;
    int &k = i;

    printf("j is %d\n", *j);
    printf("k is %d\n", k);

    return 0;
}