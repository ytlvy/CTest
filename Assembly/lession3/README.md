### debug
```
$ clang -g -c -x assembler hello.s
$ clang hello.o -o hello
$ ./hello
Hello, world!
$ lldb hello
(lldb) target create "hello"
Current executable set to 'hello' (x86_64).
(lldb) b hello.s:10
Breakpoint 1: where = hello`main + 16, address = 0x0000000100000f7c
(lldb) run
Process 40460 launched: '/Users/mike/GoogleDrive/Projects/Sort/hello' (x86_64)
Hello, world!
Process 40460 stopped
* thread #1, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
    frame #0: 0x0000000100000f7c hello`main at hello.s:10
   7        mov rbp, rsp
   8        lea rdi, [rip + _main.S_0]
   9        call    _puts
-> 10       mov rax, 0
   11       mov rsp, rbp
   12       pop rbp
   13       ret
```