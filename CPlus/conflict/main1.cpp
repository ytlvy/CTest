#include <iostream>
void DoLayer();

int main()
{
  printf("start \n");
  DoLayer();
  printf("finished \n");
  return 0;
}
//g++ -c layer.cpp -o layer.o
//g++ -shared layer.o conflict.o -o libconflict.so
//
//g++ -c main1.cpp -o main1.o
//ar rc libmain1.a main1.o
//g++ -L. -o main -lmain1 -lconflict
