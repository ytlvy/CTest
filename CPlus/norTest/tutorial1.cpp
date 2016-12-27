#include <iostream>
#include <curses.h>

using namespace std;

int GetValueFromASM(){

    _asm{
        mov eax, 39
    }
}

int int main(int argc, char const *argv[])
{
    count<< "ASM said"<<GetValueFromASM()<<endl;
    _getch();


    return 0;
}