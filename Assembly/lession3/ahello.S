/*
gcc -o ahello ahello.S
clang -g -c -x assembler ahello.S && clang ahello.o -o ahello
 */

.section	__TEXT,__cstring
tips:   .string "please input a char\n"
fmt:    .string "u input a odd char: %c\n"
bfmt:   .asciz "%d"
breturn:   .asciz "\noutput binary end\n"

.section	__TEXT,__text
.global _main
.p2align	2
_main:   
    sub	sp, sp, #48                     ; 分配48字节控件
	stp	x29, x30, [sp, #32]             ; 头部16字节用来存储X30 x29
	add	x29, sp, #32                    ; =32 剩余32字节 临时变量

    adrp x0, tips@PAGE
    add x0, x0, tips@PAGEOFF
    bl _printf

Lp:    bl _getchar
    
    sturb	w0, [x29, #-1]              ;存贮输入到
    bl _printBinary

    adrp	x9, ___stdinp@GOTPAGE       ;清空输入缓冲区, 防止回车干扰
	ldr	x9, [x9, ___stdinp@GOTPAGEOFF]
	ldr	x0, [x9]
	bl	_fflush
    
    ldursb	w8, [x29, #-1]              ;取出数据
    tbz w8, #0, Lp

    adrp x0, fmt@PAGE
    add x0, x0, fmt@PAGEOFF
    str	x8, [sp]         //这个参数要放到栈上
    bl _printf


    //return
    mov w0, #0
    ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48                     ; =48

    ret


.global _printBinary
.p2align	2
_printBinary:  
    sub sp, sp, #48 
    stp x29, x30, [sp, #32]
    stp x8, x9, [sp, #16]
    add x29, sp, 16

    mov x8, x0
LBB1_1:    
    and w9, w8, #1
    str w8, [x29, #-8]    //w8 在下面的函数调用会被变更, 所以需要存储

    adrp x0, bfmt@PAGE
    add x0, x0, bfmt@PAGEOFF
    str	x9, [sp]         //这个参数要放到栈上
    bl _printf

    ldr w8, [x29, #-8]
    lsr	w8, w8, #1
    cbnz w8, LBB1_1

    adrp x0, breturn@PAGE
    add x0, x0, breturn@PAGEOFF
    bl _printf


    ldp x8, x9, [sp, #16]
    ldp x29, x30, [sp, #32]
    add sp, sp, #48
    ret