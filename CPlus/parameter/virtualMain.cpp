#include "vclassA.h"

void print1(A a) {
    a.print();
}

int main(int argc, char const *argv[]) {
    A a(11);
    print1(a);
    
    return 0;
}


// 0000000100000d00         push       rbp
// 0000000100000d01         mov        rbp, rsp
// 0000000100000d04         sub        rsp, 0x60
// 
// 0000000100000d08         mov        dword [rbp+var_4], 0x0
// 0000000100000d0f         mov        dword [rbp+var_8], edi
// 0000000100000d12         mov        qword [rbp+var_10], rsi
// 
// 0000000100000d16         lea        rsi, qword [rbp+var_20]
// 0000000100000d1a         mov        edi, 0xb
// 0000000100000d1f         mov        dword [rbp+var_40], edi
// 0000000100000d22         mov        rdi, rsi
// 0000000100000d25         mov        eax, dword [rbp+var_40]
// 0000000100000d28         mov        qword [rbp+var_48], rsi
// 0000000100000d2c         mov        esi, eax
// 0000000100000d2e         call       __ZN1AC1Ei                                  ; A::A(int)
// 
// 0000000100000d33         lea        rdi, qword [rbp+var_30]
// 0000000100000d37         mov        qword [rbp+var_50], rdi
// 0000000100000d3b         mov        rsi, qword [rbp+var_48]
// 0000000100000d3f         call       __ZN1AC1ERKS_                               ; A::A(A const&)
// 
// 0000000100000d44         mov        rdi, qword [rbp+var_50]
// 0000000100000d48         call       __Z6print11A                                ; print1(A)
// 
// 0000000100000d4d         jmp        loc_100000d52