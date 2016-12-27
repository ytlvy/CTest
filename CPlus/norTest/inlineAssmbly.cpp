#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {
	char *fmt = "Hello, %s\n";
	char *s = "World";
	int ret = 0;
	asm (" callq printf\n\t"
			: "=a"(ret)
			: "D"(fmt), "S"(s));
	printf("ret: %d\n", ret);
	return 0;
}