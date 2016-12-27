#include <stdio.h>

// clang -g -Weverything -o simple simple.c
void foo();
void foobar();
void bar();

int main(void) {

    foo();
    printf("I seem to be a verb \n");
    return 0;

}

void foo() {
    foobar();
}

void foobar() {
    bar();
}

void bar() {
    printf("bar called\n");
}
