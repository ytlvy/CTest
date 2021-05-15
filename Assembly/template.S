/*
x8, x16, x17, x18, 不可用
gcc -o student student.S
clang -g -c -x assembler student.S && clang student.o -o student
 */

.section	__TEXT,__cstring
fmt_1: .string "Sam"
fmt_2: .string "Smith"

.section	__DATA,__data
.p2align 3
_a:   .quad   0x57
.p2align 3
_b:  .quad 117

.zerofill __DATA,__bss,_x,8,3  

.section	__TEXT,__text

.equ s_frist_name, 0
.equ s_last_name, 30
.equ s_class, 60
.equ s_grade, 64
.equ s_size,  68
.equ s_size_aligned, 80     //16的倍数, 堆栈

.global _main
.p2align	2
_main:   
	stp	x29, x30, [sp, #-32]!             ; 头部16字节用来存储X30 x29
    str x19, [sp, #16]


    


    //return
    mov x0, #0
    ldr x19, [sp, #16]
    ldp	x29, x30, [sp], #32             ; 16-byte Folded Reload
    ret
