// test.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double global_var1;

int fun(void)
{
    printf("in test.c: &global_var1 = %p", &global_var1);
    printf(" global_var1 = %x\n", global_var1);
    printf("sizeof(global_var1) = %d\n", sizeof(global_var1));

    memset(&global_var1, 0, sizeof(global_var1));

    return 0;
}
