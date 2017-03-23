#include <ostream>

class A {
public:
    explicit A(int a):aa(a){};
    ~A(){};
    void print(){printf("A.aa=%d\n", aa);};
private:
    int aa;
};

void print1(A a) {
    a.print();
}

int main(int argc, char const *argv[]) {
    A a(11);
    print1(a);
    
    return 0;
}

// main
// 0000000100000d90         push       rbp
// 0000000100000d91         mov        rbp, rsp
// 0000000100000d94         sub        rsp, 0x30
// 
// 0000000100000d98         mov        dword [rbp+var_4], 0x0
// 0000000100000d9f         mov        dword [rbp+var_8], edi
// 0000000100000da2         mov        qword [rbp+var_10], rsi
// 
// 0000000100000da6         lea        rdi, qword [rbp+var_18]                     ;预先分配的对象A地址
// 0000000100000daa         mov        esi, 0xb
// 0000000100000daf         call       __ZN1AC1Ei                                  ; A::A(int)
// 
// 0000000100000db4         mov        esi, dword [rbp+var_18]
// 0000000100000db7         mov        dword [rbp+var_20], esi
// 0000000100000dba         lea        rdi, qword [rbp+var_20]
// 0000000100000dbe         call       __Z6print11A                                ; print1(A)
// 
// 0000000100000dc3         jmp        loc_100000dc8
// 
// print
// 0000000100000d50         push       rbp                                         ; CODE XREF=_main+46
// 0000000100000d51         mov        rbp, rsp
// 0000000100000d54         call       __ZN1A5printEv                              ; A::print()
// 0000000100000d59         pop        rbp
// 0000000100000d5a         ret
//                         ; endp
// 0000000100000d5b         nop        dword [rax+rax]
// 
// A::print
// 0000000100000d60         push       rbp                                         ; CODE XREF=__Z6print11A+4
// 0000000100000d61         mov        rbp, rsp
// 0000000100000d64         sub        rsp, 0x10
// 0000000100000d68         lea        rax, qword [0x100000f88]                    ; "A.aa=%d\\n"
// 0000000100000d6f         mov        qword [rbp+var_8], rdi
// 0000000100000d73         mov        rdi, qword [rbp+var_8]
// 0000000100000d77         mov        esi, dword [rdi]
// 0000000100000d79         mov        rdi, rax                                    ; argument "format" for method imp___stubs__printf
// 0000000100000d7c         mov        al, 0x0
// 0000000100000d7e         call       imp___stubs__printf
// 0000000100000d83         mov        dword [rbp+var_C], eax
// 0000000100000d86         add        rsp, 0x10
// 0000000100000d8a         pop        rbp
// 0000000100000d8b         ret
//                         ; endp
// 0000000100000d8c         nop        dword [rax]