#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {
	struct packed_struct {
		unsigned int f1:1;
		unsigned int f2:1;
		unsigned int f3:1;
		unsigned int f4:1;
		unsigned int type:4;
		unsigned int my_int:9;
	} pack;
	
	struct X {
		short s; /* 2 bytes */
				 /* 2 padding bytes */
		int   i; /* 4 bytes */
		char  c; /* 1 byte */
				 /* 3 padding bytes */
	};
	
	struct Y {
		int   i; /* 4 bytes */
		char  c; /* 1 byte */
				 /* 1 padding byte */
		short s; /* 2 bytes */
	};

	struct Z {
		int   i; /* 4 bytes */
		short s; /* 2 bytes */
		char  c; /* 1 byte */
				 /* 1 padding byte */
	};
	
	printf("pack length %lu\n", sizeof(packed_struct));
	printf("X length %lu\n", sizeof(X));
	printf("Y length %lu\n", sizeof(Y));
	printf("Z length %lu\n", sizeof(Z));
}