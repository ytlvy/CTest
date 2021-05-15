/*
x8, x16, x17, x18, 不可用
gcc -o student student.S
clang -g -c -x assembler student.S && clang student.o -o student
 */

.section	__TEXT,__cstring,cstring_literals
fmt_1: .asciz "Sam"            //0x53616d
fmt_2: .asciz "Smith"          //0x536d697468

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


    //struct student new
    sub sp, sp, #s_size_aligned
    mov x19, sp

    add x0, x19, #s_frist_name
    adrp x1, fmt_1@PAGE
    add x1, x1, fmt_1@PAGEOFF
    mov x9, #30
    str x9, [sp]
    bl ___strcpy_chk

    add x0, x19, #s_last_name
    adrp x1, fmt_2@PAGE
    add x1, x1, fmt_2@PAGEOFF
    bl _strcpy

    mov w1, #2
    strb w1, [x19, #s_class]
    mov w1, #88
    str w1, [x19, #s_grade]

    add sp, sp, #s_size_aligned             //此处下断点检测


    //return
    mov x0, #0
    ldr x19, [sp, #16]
    ldp	x29, x30, [sp], #32             ; 16-byte Folded Reload
    ret

/*
lldb student
b student.S:48
run
register read sp
x/20xw 0x000000016fdff4d0      20个word

 */