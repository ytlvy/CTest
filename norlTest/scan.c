#include <stdio.h>

int main(int argc, char const *argv[])
{
    char name[11], name1[11];

    int count;

    count = scanf("%5s %10s", name, name1);
    printf("%s %s\n", name, name1);

    return 0;
}