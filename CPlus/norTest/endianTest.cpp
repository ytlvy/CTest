#include <stdio.h>
#include <iostream>

int endian(){
	int one = 1;
	char *ptr;
	ptr = (char *)&one;
	
	return (*ptr);
}

int endian1(){
	union{
		int one;
		char ch;
	} endn;
	
	endn.one = 1;
	return endn.ch;
}

int main(int argc, char *argv[]) {
	if(endian()){
		std::cout << "little endian \n";
	}
	else{
		std::cout << "big endian \n";
	}
	
	int a = 0x1345; // x00003039
	char *ptr = (char*)(&a);
	for(int i = 0; i < sizeof(a); i++) {
		printf("%p\t0x%.2x\n", ptr+i, *(ptr+i));
	}
}