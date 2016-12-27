#include <stdlib.h>
#include <stdio.h>

int my_constructor(void) __attribute__((constructor));
int my_constructor2(void) __attribute__((constructor(102)));
int my_constructor3(void) __attribute__((constructor(101)));

__attribute__((destructor)) static void mydtor(void) {
  printf("finalized\n");
}

int main(int argc, char const *argv[]){
    printf("main function\n");
    return 0;
}

int my_constructor(void) {
    printf("my_constructor\n");
    
    return 0;
}

int my_constructor2(void){
    printf("my_constructor2\n");
    return 0;
}

int my_constructor3(void)  { 
    printf("my_constructor3\n");
    return 0;
}