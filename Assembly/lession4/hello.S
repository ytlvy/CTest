/*
gcc -o hello hello.S
clang -g -c -x assembler hello.S && clang hello.o -o hello
 */

.section	__TEXT,__cstring
fmt_1: .string "Enter a number in hex: \n"
fmt_2: .string "%016lx * %016lx = %016lx%016lx\n"
fmt_3: .string "%lx"

.section	__TEXT,__text
.global _main
.p2align	2
_main:   
    sub	sp, sp, #144                     ; 分配48字节控件
	stp	x29, x30, [sp, #128]             ; 头部16字节用来存储X30 x29
    stp x19, x20, [sp, #112]
	add	x29, sp, #112                    ; =112 剩余32字节 临时变量

    //printf("Enter a number in hex: \n")
    adrp x0, fmt_1@PAGE
    add x0, x0, fmt_1@PAGEOFF
    str x0, [x29, #-8]                      ;x29 - 8 fmt_1
    bl _printf

    //scanf
    adrp x0, fmt_3@PAGE
    add x0, x0, fmt_3@PAGEOFF
    str x0, [x29, #-16]                  ;x29 -16 fmt_3
    sub x11, x29, #24                    ;x29 -24 x
    str x11, [sp]
    bl _scanf

    ldr x0, [x29, #-8]
    bl _printf

 
    ldr x0, [x29, #-16]
    sub x11, x29, #32                 ;x29 - 32 y
    str x11, [sp]
    bl _scanf


    ldr x0, [x29, #-24]
    mov x19, x0
    ldr x1, [x29, #-32]
    mov x20, x1
    bl _longMul


    mov x4, x0
    adrp x0, fmt_2@PAGE
    add x0, x0, fmt_2@PAGEOFF
    str x19, [sp]
    str x20, [sp, #8]
    str x1, [sp, #16]
    str x4, [sp, #24]
    bl _printf


    //return
    mov x0, #0
    ldp x19, x20, [sp, #112]
    ldp	x29, x30, [sp, #128]             ; 16-byte Folded Reload
	add	sp, sp, #144                     ; =48

    ret


.global _longMul
.p2align	2
_longMul:  
    stp x29, x30, [sp, #-16]!         ; 可省略
    
    mul x9, x0, x1
    umulh x1, x0, x1
    mov x0, x9

    ldp x29, x30, [sp], #16           ;可省略
    ret