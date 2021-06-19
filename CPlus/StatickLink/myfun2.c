#include <stdio.h>
void myfunc2(void);

void testfun(void) {
    myfunc2();
}

void myfunc2(void) {
    printf( "This is my func2!\n" );
}