/**
 * gcc -shared -fPIC sqrtcus.c -o sqrtcus.so
 * clang -dynamiclib -undefined suppress -flat_namespace -std=c99 -fPIC -O2 sqrtcus.c -o libsqrtcus.dylib
 * DYLD_INSERT_LIBRARIES=$PWD/sqrtcus.so DYLD_FORCE_FLAT_NAMESPACE=1 ./sqrtTest
 * DYLD_INSERT_LIBRARIES=$PWD/libsqrtcus.dylib DYLD_FORCE_FLAT_NAMESPACE=1 ./sqrtTest
 *
 *
 */

 #define _GNU_SOURCE
 #include <dlfcn.h>
 #include <stdio.h>
 #include <stdlib.h>

 #define DYLD_INTERPOSE(_replacment,_replacee) \
 __attribute__((used)) static struct{ const void* replacment; const void* replacee; } _interpose_##_replacee \
 __attribute__ ((section ("__DATA,__interpose"))) = { (const void*)(unsigned long)&_replacment, (const void*)(unsigned long)&_replacee };

double sqrt(double x){
    return 42;
}

DYLD_INTERPOSE(sqrt, sqrt);
