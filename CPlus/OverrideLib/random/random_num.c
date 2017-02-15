/**
 * gcc random_num.c -o random_num
 * LD_PRELOAD=$PWD/unrandom.so ./random_num
 * set env DYLD_INSERT_LIBRARIES /usr/lib/libMallocDebug.dylib
 * DYLD_INSERT_LIBRARIES=./libfaketime.so.1 DYLD_FORCE_FLAT_NAMESPACE=y FAKETIME="-15d" date
 * DYLD_INSERT_LIBRARIES=$PWD/unrandom.so DYLD_FORCE_FLAT_NAMESPACE=1  ./random_num
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
  srand(time(NULL));
  int i = 10;
  while(i--) printf("%d\n",rand()%100);
  return 0;
}
