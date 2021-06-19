#include <stdio.h>

int main(int argc, char *argv[]) {
	printf ("Characters: %c %c \n", 'a', 65);
	
	printf ("Decimals: %d %ld\n", 1977, 650000L);
	printf ("Preceding with blanks: %10d \n", 1977);
	printf ("Preceding with zeros: %010d \n", 1977);
	printf ("Some different radices: %d %x %o %#x %#o \n", 100, 100, 100, 100, 100);
	printf ("floats: %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416);
	printf ("Width trick: %*d \n", 5, 10);
	
	//For integer specifiers (d, i, o, u, x, X): precision specifies the minimum number of digits to be written. If the value to be written is shorter than this number, the result is padded with leading zeros. The value is not truncated even if the result is longer. A precision of 0 means that no character is written for the value 0
	printf ("Decimals: %010d %ld\n", 1977, 650000L);
	printf ("Decimals: %.10d %ld\n", 1977, 650000L);
	
	// For s: this is the maximum number of characters to be printed. By default all characters are printed until the ending null character is encountered.
	printf ("%.3s \n", "A string");  //.number 
	return 0;
}