/*
x8, x16, x17, x18, 不可用
gcc -o student student.S

This is a short program to print a table of sine and 
cosine values using the fixed point sin/cos functions. 
Compile with:
gcc -o sincos sincos.S sincosmain.S fixedfuncs.c
clang -g -c -x assembler sincos.S sincosmain.S fixedfuncs.c && clang student.o -o sincos
*/

.section	__TEXT,__cstring
fmta: .string "%14.6f "
head: .asciz "     x               sin(x)        cos(x)\n"
line: .asciz "     --------------------------------------\n"
newline: .asciz "\n"
tab: .asciz "\t"
 
.section	__TEXT,__text
.global _main
.p2align	2
_main:   
	stp	x29, x30, [sp, #-64]!             ; 头部16字节用来存储X30 x29
    stp x27, x28, [sp, #48]
    str x19, [sp, #32]
    add x19, sp,  #40

    adrp x0, head@page
    add x0, x0, head@pageoff
    bl _printf

    adrp x0, line@page
    add x0, x0, line@pageoff
    bl _printf

    mov x27, #0

    adrp x0, _pi@page
    add x0, x0, _pi@pageoff
    ldrsw x0, [x0]
    str x0, [x19]
mloop:
    
    // load count to r0 and convert it to a number x 
    // between 0.0 and pi/2
    mov x0, x27

    ldr x1, [x19]

    smull x0, w0, w1
    lsr  x0, x0, #4
    mov x28, x0

    mov x1, #28
    adrp x2, fmta@page
    add x2, x2, fmta@pageoff
    bl _printS
    adrp x0, tab@page
    add x0, x0, tab@pageoff
    bl _printf

    //caculate and print sin(x)
    mov x0, x28
    bl _fixed_sin

    mov x1, #28
    adrp x2, fmta@page
    add x2, x2, fmta@pageoff
    bl _printS

    adrp x0, tab@page
    add x0, x0, tab@pageoff
    bl _printf

    //caculate and print cos(x)
    mov x0, x28
    bl _fixed_cos
    mov x1, #28
    adrp x2, fmta@page
    add x2, x2, fmta@pageoff
    bl _printS

    adrp x0, newline@page
    add x0, x0, newline@pageoff
    bl _printf

    add x27, x27, #1
    cmp x27, #33
    blt mloop

    //return
    mov x0, #0

    ldr x19, [sp, #32]
    ldp x27, x28, [sp, #48]
    ldp	x29, x30, [sp], #64             ; 16-byte Folded Reload
    ret
