<!--
 * @Author: Y.t
 * @Date: 2019-09-04 10:19:27
 * @LastEditors: Y.t
 * @LastEditTime: 2021-05-17 09:51:10
 * @Description: 
-->
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


You can put a breakpoint on your destructor using the --method option,

(lldb) br s -M ~WebViewImpl
You can use the --name option with just the dtor method name too,

(lldb) br s -n ~WebViewImpl
and lldb should find it. Finally, you can pass the mangled name to breakpoint set and that will work as well,

(lldb) br s -n _ZN2pf11WebViewImplD1Ev

### callthread backtrace
```
bt
```

### thread backtrace all
```
bt all
```

### Select the stack frame that called the current stack frame.
```
up
```

### Select the stack frame that is called by the current stack frame.
```
down
```

### Write a new decimal value 123 to the current thread register rax.

```
register write rax 123
```

### Show the values for the register named rax in the current thread formatted as binary.
```
p/t $rax
```

### Read memory from address 0xbffff3c0 and show four hex uint32_t values.
```
memory read/4xw 0xbffff3c0
x/4xw 0xbffff3c0
```

read one
```
x/xw 0xbffff3c0
```

### Disassemble the current function for the current frame.

```
di -f

disassemble --name main
di -n main

disassemble --start-address 0x1eb8 --count 20
di -s 0x1eb8 -c 20
```

### List the main executable and all dependent shared libraries.
```
image list
```


### length bug
Solution: I needed to use -fno-integrated-as with clang to tell it to use GNU Assembler directly instead of its own built-in integrated assembler (which is suppose to be a drop-in replacement for GAS but apparently it's not). I used the following updated command to compile and run my aarch64 program without issue:
```
clang -nostdlib -fno-integrated-as -target aarch64-linux-gnu -s hello_world.s -o hello_world.out && ./hello_world.out
```

### voltron
```
voltron view stack
voltron view registers
{disasm,d,dis,command,c,cmd,registers,r,reg,register,memory,m,mem,stack,s,st,breakpoints,b,bp,break,backtrace,t,bt,back} ...
```