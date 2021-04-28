#include <stdio.h>

void myfunc1( void );
void myfunc2( void );
extern void testfun(void);

int main() {
    myfunc1();
    myfunc2();
    testfun();
    return 0;
}