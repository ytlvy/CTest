/*
 * @Author: Y.t
 * @Date: 2021-05-17 18:38:25
 * @LastEditors: Y.t
 * @LastEditTime: 2021-05-17 19:59:59
 * @Description: 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_DECIMAL_DIGITS 16

int base10double(char n1[MAX_DECIMAL_DIGITS])
{
    int carry = 0;
    for (int i = 0; i < MAX_DECIMAL_DIGITS; i++)
    {
        n1[i] += n1[i] + carry;
        if (n1[i] > 9)
        {
            n1[i] -= 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
    }
    return carry;
}

int strtoSfixed(char *s, int frac_bits)
{
    char *point = s;
    char digits[MAX_DECIMAL_DIGITS];
    int negative = 0;
    if (*s == '-')
    {
        negative = 1;
        s++;
    }

    unsigned int value = atoi(s);
    while (*point != '.' && *point != 0)
    {
        point++;
    }

    if (*point == 0 || *(point + 1) == 0)
    {
        if (negative)
        {
            value = -value;
        }
        return value << frac_bits;
    }

    ++point;
    for (int i = MAX_DECIMAL_DIGITS - 1; i >= 0; i--)
    {
        if (*point == 0)
        {
            digits[i] = 0;
        }
        else
        {
            digits[i] = *point - '0';
            ++point;
        }
    }

    while (frac_bits > 0)
    {
        value <<= 1;
        if (base10double(digits))
        {
            value |= 1;
        }
        frac_bits--;
    }

    if (negative)
    {
        value = -value;
    }

    return value;
}

int roundit(int *digits, int current)
{
    while (current > 0)
    {
        if (digits[current] > 9)
        {
            digits[current] %= 10;
            digits[current - 1]++;
        }
        current--;
    }

    if (current == 0 && digits[current] > 9)
    {
        digits[current] %= 10;
        return 1;
    }

    return 0;
}

/* Print a signed fixed point number with the given 
number of bits in the fractional part. NOTE: frac_bits 
must be between 0 and 31 for this function to work properly.
*/
#define MAX_DIGITS 8
void printS(int num, int frac_bits)
{
    unsigned int mask = (1 << frac_bits) - 1;
    int count = 0;
    unsigned int fracpart;
    int intpart = 0;
    int frac_digits[MAX_DIGITS + 1];

    if (num < 0)
    {
        printf("-");
        num = -num;
    }
    else
    {
        printf(" ");
    }

    fracpart = num & mask;
    intpart = num >> frac_bits;
    for (count = 0; count < MAX_DIGITS + 1; count++)
    {
        fracpart *= 10;
        frac_digits[count] = fracpart >> frac_bits;
        fracpart &= mask;
    }

    frac_digits[MAX_DIGITS] += 5;
    intpart += roundit(frac_digits, MAX_DIGITS);
    printf("%d.", intpart);

    for (count = 0; count < MAX_DIGITS; count++)
    {
        printf("%d", frac_digits[count]);
    }
}