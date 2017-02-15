#include <iostream>
void DoThing();

int main()
{
  printf("start \n");
  DoThing();
  printf("finished \n");
  return 0;
}
//g++ -c work.cpp -o work.o
//ar rc libwork.a work.o
//
//g++ -c main.cpp -o main.o
//ar rc libmain.a main.o
//
//g++  -L. -o main -lwork -lmain  && ./main
//
//g++ -c conflict.cpp -o conflict.o
//ar rc libconflict.a conflict.o
//
//g++  -L. -o main -lmain -lwork -lconflict && ./main
//g++  -L. -o main -lmain -lconflict -lwork && ./main
//
//g++ -shared conflict.o -o libconflict.so
//g++ -L. -o main -lmain -lwork
//DYLD_INSERT_LIBRARIES=$PWD/libconflict.so DYLD_FORCE_FLAT_NAMESPACE=1 ./main
//
//g++ -L. -o main -lmain
//DYLD_INSERT_LIBRARIES=$PWD/libconflict.so DYLD_FORCE_FLAT_NAMESPACE=1 ./main
//clang++ main.cpp -L. -lconflict -O2 -o main
//clang++ main.cpp work.cpp -L. -lconflict -O2 -o main
//
