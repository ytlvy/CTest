#hello.s

#to build an executable:
#  as -o hello.o hello.s
#  ld -s -o hello hello.o

.section __TEXT,__text
#Export the entry point to the elf linker or loader. The conventional
#entry point is " _start". user "ld -e foo" to override the default
.global _main

_main:

    movl    $0x2000004, %eax            #preparing system call 4
    movl    $1, %edi                    #STDOUT file descripter is 1
    movq    msg@GOTPCREL(%rip), %rsi    #the value to print
    movq    $100, %rdx
    syscall
                            #and exit
    movl    $0, %ebx
    movl    $0x2000001, %eax
    syscall

.section __DATA, __data
msg:
    .asciz "Hello, world!\n"


