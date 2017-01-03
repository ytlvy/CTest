#include <stdio.h>

struct { 
	short s [5];
	union { 
		 float y; 
		 long z; 
	}u; 
} t; 

int main(int argc, char *argv[]) {
	printf("size of t: %d", sizeof(t));
}