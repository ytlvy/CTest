#include <stdio.h>

void funTest(int *p) {
    printf("p 's address %p\n", p);
    printf("i 's address %p\n", &(*p));
}

int main(int argc, char const *argv[])
{
    int i = 0;
    printf("i 's address %p\n", &i);

    funTest(&i);
    return 0;
}