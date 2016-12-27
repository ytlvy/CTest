/**
 *
 * g++  ctest.c cppHeader.cpp -o output
 */

#include "cppHeader.h"
extern void print(int i);

int main(int argc,char** argv)
{
    print(3);
    return 0;
}