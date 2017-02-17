/**
 *  gcc sqrtTest.c -o sqrtTest
 *  DYLD_INSERT_LIBRARIES=$PWD/sqrtcus.so DYLD_FORCE_FLAT_NAMESPACE=1 X=1  ./sqrtTest
 *  clang sqrtTest.c -std=c99 -L. -lsqrtcus -O2 -o sqrtTest
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
  double x = sqrt(100);
  printf("sqrt(100) = %f\n", x);

  return 0;
}
