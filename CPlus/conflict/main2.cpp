#include <iostream>
void DoThing();
void DoLayer();

int main()
{
  printf("start \n");
  DoThing();
  DoLayer();
  printf("finished \n");
  return 0;
}

//g++ -c main2.cpp -o main2.o
//g++ -c work.cpp -o work.o
//ar rc libmain2.a main2.o work.o
//g++  -L. -o main -lmain2 -lconflict && ./main
//DYLD_INSERT_LIBRARIES=$PWD/libconflict.so DYLD_FORCE_FLAT_NAMESPACE=1 ./main
