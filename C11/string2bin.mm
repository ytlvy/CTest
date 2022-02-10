#include <iostream>
#include <cstdlib>

void longdiv2(const char* in, char* out)
{
    int carry = 0;

    while (*in)
    {
        int numerator = *in++ - '0';
        numerator += carry;

        carry = (numerator % 2) == 0 ? 0 : 10;
        *out++ = '0' + (numerator / 2);
    }

    *out = '\0';
}

int main(int argc, char const *argv[])
{
    char *str = "12345";
    char *out = new char[1000];
    longdiv2(str, (char *)out);
    printf("----%s\n", out);
    return 0;
}