/*
  析构了两次
  0000000100000d90         push       rbp
  0000000100000d91         mov        rbp, rsp
  0000000100000d94         sub        rsp, 0x40
 
  0000000100000d98         mov        dword [rbp+var_4], 0x0
  0000000100000d9f         mov        dword [rbp+var_8], edi
  0000000100000da2         mov        qword [rbp+var_10], rsi
 
 
  0000000100000da6         lea        rsi, qword [rbp+var_18]
  0000000100000daa         mov        rdi, rsi
  0000000100000dad         mov        qword [rbp+var_30], rsi
  0000000100000db1         call       __ZN5WigetC1Ev                              ; Wiget::Wiget()
 
  0000000100000db6         mov        rdi, qword [rbp+var_30]
  0000000100000dba         call       __ZN5WigetD1Ev                              ; Wiget::~Wiget()
  0000000100000dbf         jmp        loc_100000dc4
 
                       loc_100000dc4:
  0000000100000dc4         lea        rdi, qword [rbp+var_18]                     ; CODE XREF=_main+47
  0000000100000dc8         mov        dword [rbp+var_4], 0x0
  0000000100000dcf         call       __ZN5WigetD1Ev                              ; Wiget::~Wiget()
 
  0000000100000dd4         mov        eax, dword [rbp+var_4]
  0000000100000dd7         add        rsp, 0x40
  0000000100000ddb         pop        rbp
  0000000100000ddc         ret
                          ; endp
                          
  0000000100000ddd         mov        ecx, edx
  0000000100000ddf         mov        qword [rbp-0x20], rax
  0000000100000de3         mov        dword [rbp-0x24], ecx
  0000000100000de6         lea        rdi, qword [rbp-0x18]
  0000000100000dea         call       __ZN5WigetD1Ev                              ; Wiget::~Wiget()
 
  0000000100000def         jmp        _main+100
  0000000100000df4         jmp        _main+105                                   ; CODE XREF=_main+95
  0000000100000df9         mov        rdi, qword [rbp-0x20]                       ; CODE XREF=_main+100
  0000000100000dfd         call       imp___stubs___Unwind_Resume
 
  0000000100000e02         mov        ecx, edx
  0000000100000e04         mov        rdi, rax
  0000000100000e07         mov        dword [rbp-0x34], ecx
  0000000100000e0a         call       ___clang_call_terminate
  0000000100000e0f         nop
 */


#include <ostream>

class Wiget {
public:
    Wiget ():st_(new char[10]){};
    ~Wiget(){
        printf("destructed\n");
        delete[] st_;
    };
private:
    char *st_;
};

int main(int argc, char const *argv[]) {
    Wiget w;
    
    w.~Wiget();
    
    // new (&w) Wiget;
    
    return 0;
}