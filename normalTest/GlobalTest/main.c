#include <stdio.h>
#include <stdlib.h>

extern int fun(void);

int global_var1 = 0xff00ff00;       // 强符号
int global_var2 = 0x00ff00ff;       // 强符号

int main(int argc, const char *argv[])
{
/////////////////////////////////////////////////////////////////////
    printf("in main.c: &global_var1 = %p", &global_var1);
    printf(" global_var1 = %x\n", global_var1);
    printf("sizeof(global_var1) = %d\n", sizeof(global_var1));
/////////////////////////////////////////////////////////////////////
    printf("in main.c: &global_var2 = %p", &global_var2);
    printf(" global_var2 = %x\n", global_var2);
    printf("sizeof(global_var2) = %d\n", sizeof(global_var2));
/////////////////////////////////////////////////////////////////////
    fun();

    printf("global_var1 = %x\n", global_var1);
    printf("global_var2 = %x\n", global_var2);

    return 0;
}
