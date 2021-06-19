#include <stdio.h>

void myfunc1(void);

extern void testfun(void) {
    myfunc1();
}

void myfunc1(void) {
    printf( "This is my func1!\n" );
}