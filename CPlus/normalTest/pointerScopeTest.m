#include "stdio.h"
 
int * gPtr;
 
int main()
{
 int * lPtr = NULL;
 
 if(gPtr == lPtr)
 {
	printf("Equal!");
 }
 else
 {
  printf("Not Equal");
 }
 
 return 0;
}