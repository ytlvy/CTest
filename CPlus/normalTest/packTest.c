#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	union {
		unsigned char raw[8];
		struct {
			char one;
			int two;
			char three;
			char four;
			char five;
		} formatted __attribute__((packed));  
//		} __attribute__((packed)) formatted ;  //correct
	} test;

	printf("one   : %d\n", (int)&test.formatted.one - (int)&test);
	printf("two   : %d\n", (int)&test.formatted.two - (int)&test);
	printf("three : %d\n", (int)&test.formatted.three - (int)&test);
	printf("four  : %d\n", (int)&test.formatted.four - (int)&test);
	printf("five  : %d\n", (int)&test.formatted.five - (int)&test);
	return 0;
}