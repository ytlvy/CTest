/*
x8, x16, x17, x18, 不可用
gcc -o student student.S
clang -g -c -x assembler simd.S && clang simd.o -o simd
 */

.section	__TEXT,__cstring
fmt_1: .string "Sam"
fmt_2: .string "Smith"

.data
dtab:
    .word 0x55555555, 0xBFC55555  // -1.666666666666667e-01 (-1/3!)
    .word 0x11111111, 0x3F811111  // 8.333333333333333e-03   (1/5!)
    .word 0x1A01A01A, 0xBF2A01A0  // -1.984126984126984e-04 (-1/7!)
    .word 0xA556C734, 0x3EC71DE3  // 2.755731922398589e-06  (1/9!)
    .word 0x67F544E4, 0xBE5AE645  // -2.505210838544172e-08
    .word 0x13A86D09, 0x3DE61246  // 1.605904383682161e-10
    .word 0xE733B81F, 0xBD6AE7F3  // -7.647163731819816e-13
    .word 0x7030AD4A, 0x3CE952C7  // 2.811457254345521e-15
    .word 0x46814157, 0xBC62F49B  // -8.220635246624329e-18

.section	__DATA,__data
.p2align 3
_a:   .quad   0x57
.p2align 3
_b:  .quad 117

.zerofill __DATA,__bss,_x,8,3  

.section	__TEXT,__text


.global _main
.p2align	2
_main:   
	stp	x29, x30, [sp, #-32]!             ; 头部16字节用来存储X30 x29
    str x19, [sp, #16]

    adrp x0, dtab@page
    add x0, x0, dtab@pageoff

    ld3 {v0.b, v1.b, v2.b}[0], [x0], #32
    ld3 {v0.b, v1.b, v2.b}[1], [x0], #32
    ld3 {v0.b, v1.b, v2.b}[2], [x0], #32
    ld3 {v0.b, v1.b, v2.b}[3], [x0], #32
    ld3 {v0.b, v1.b, v2.b}[4], [x0], #32
    ld3 {v0.b, v1.b, v2.b}[5], [x0], #32
    ld3 {v0.b, v1.b, v2.b}[6], [x0], #32
    ld3 {v0.b, v1.b, v2.b}[7], [x0], #32


    //return
    mov x0, #0
    ldr x19, [sp, #16]
    ldp	x29, x30, [sp], #32             ; 16-byte Folded Reload
    ret
