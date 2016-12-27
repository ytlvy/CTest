//clang -shared -fpic -o libmlpic.so mlpic.c
//gcc -fpic -shared mlpic.c -o libmlpic.so
//otool -tV  显示汇编代码

int myglob = 42;

int ml_util_func(int a)
{
    return a + 1;
}

int ml_func(int a, int b)
{
    int c = b + ml_util_func(a);
    myglob += c;
    return b + myglob;
}