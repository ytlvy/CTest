/*
x8, x16, x17, x18, 不可用
gcc -o student student.S
clang -g -c -x assembler student.S && clang student.o -o student
 */

.data 
A1:         .word 1, 2, 3, 4, 5, 6, 7, 8
A2:         .quad 10, -20, 30, -40, 50, -60, 70, -80

.text
A3:         .short 100, 200, -300, 400, 500, -600, 700, 800

// extern "C" int TestLDR1_(unsigned int i, unsigned long j);
    .global TestLDR1_
.TestLDR1_
    ldr x2, =A1

    ldr w3, [x2, w0, uxtw 2]
    ldr w4, [x2, x1, lsl 2]

    add 

ret 