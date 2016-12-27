#import <Foundation/Foundation.h>

#include <stdio.h>

typedef unsigned char *byte_pointer;
void show_bytes(byte_pointer start, int len) {
	int i;
	for (i = 0; i < len; i++)
	printf(" %.2x", start[i]);
	printf("\n");
}


void show_int(int x) {
	show_bytes((byte_pointer) &x, sizeof(int));
}

void show_short_int(unsigned short x) {
	show_bytes((byte_pointer)&x, sizeof(unsigned short));
}

void show_float(float x) {
	show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
	show_bytes((byte_pointer) &x, sizeof(void *));
}

int main(int argc, char *argv[]) {
	@autoreleasepool {
		short int v = -12345;
		unsigned short uv = (unsigned short) v;
		
		printf("v = %d, uv = %u \n", v, uv);
		show_short_int(v);
	}
}