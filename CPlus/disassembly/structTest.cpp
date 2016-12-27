#include <iostream>
using namespace std;
struct test1
{
    int member1;
    int member2;
    int member3;
};
 
int main(int argc, char* argv[])
{
    test1 local_struct;
    local_struct.member1 = 1;
    local_struct.member2 = 1;
    local_struct.member3 = 1;
    
    __asm
    {
        add dword ptr [ ebp - 12],55 ; structure 1
        add dword ptr [ ebp - 8] , 100 ; structure 2
        add dword ptr [ ebp - 4] , 23 ; structure 3
    }
    cout << "member 1: " << local_struct.member1 << endl;
    cout << "member 2: " << local_struct.member2 << endl;
    cout << "member 3: " << local_struct.member3 << endl;
    return 1;
}