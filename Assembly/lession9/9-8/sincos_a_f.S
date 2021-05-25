/*
x8, x16, x17, x18, 不可用
gcc -o student student.S
clang -g -c -x assembler sincos_a_f.S && clang sincos_a_f.o -o sincos_a_f
 */

.data
// The following is a table of constants used in the 
// Taylor series approximation for sine
.align 5                  // Align to cache
ctab: .word 0xBE2AAAAA          // -1.666666e-01
    .word 0x3C088889          // 8.333334e-03 
    .word 0xB9500D00          // -1.984126e-04
    .word 0x3638EF1D          // 2.755732e-06
    .word 0xB2D7322A          // -2.505210e-08
    .equ TERMS, 20   //((. - ctab)/4)

.text 

.global _sin_a_f
.p2align	2
// float sin_a_f(x)
// sin_a_f implements the sine function using 
//IEEE single
// precision floating point. It computes sine by summing 
// the first six terms of the Taylor series.
// s0 contains x
_sin_a_f:   
	//stp	x29, x30, [sp, #-32]!             ; 头部16字节用来存储X30 x29
    //str x19, [sp, #16]

    fmul s1, s0, s0         // s1 x^2
    fmov s3, s0
    adrp x0, ctab@page      // x0 ctable
    ldr x0, [x0, ctab@pageoff]

    mov x3, #TERMS          //counter

loop:
    fmul s3, s3, s1
    ldr s4, [x0], #4
    subs x3, x3, #1
    fmadd s0, s3, s4, s0
    bne loop

    //return
    //mov x0, #0
    //ldr x19, [sp, #16]
    //ldp	x29, x30, [sp], #32             ; 16-byte Folded Reload
    ret

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
    .equ DTERMS, 72    //((. - ctab)/8)
 
    .text
// double sin_a_d(double x)
// sin_a_f_d implements the sine function using IEEE
// double precision floating point. It computes sine 
// by summing the first ten terms of the Taylor series.
// d0 contains x
.global _sin_a_d
.p2align	2
_sin_a_d:   
	@ stp	x29, x30, [sp, #-32]!             ; 头部16字节用来存储X30 x29
    @ str x19, [sp, #16]

    fmul d1, d0, d0         // s1 x^2
    fmov d3, d0
    adrp x0, dtab@page      // x0 ctable
    ldr x0, [x0, dtab@pageoff]

    mov x3, #DTERMS          //counter

loop:
    fmul d3, d3, d1
    ldr d4, [x0], #8
    subs x3, x3, #1
    fmadd d0, d3, d4, d0
    bne loop

    //return
    //mov x0, #0
    //ldr x19, [sp, #16]
    //ldp	x29, x30, [sp], #32             ; 16-byte Folded Reload
    ret


