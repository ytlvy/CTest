/*
x8, x16, x17, x18, 不可用
gcc -o student student.S
clang -g -c -x assembler pixel.S && clang pixel.o -o pixel
 */

.section	__TEXT,__cstring
fmt_1: .string "Sam"
fmt_2: .string "Smith"

.section	__TEXT,__text

.equ s_red,   0
.equ s_green, 1
.equ s_blue,  2
.equ s_size,  3

.equ s_image_width,  100
.equ s_image_height, 100 

.global _main
.p2align	2
_main:   
	stp	x29, x30, [sp, #-32]!             ; 头部16字节用来存储X30 x29
    str x19, [sp, #16]

    //malloc
    mov x0, #(s_image_width * s_image_height * s_size)
    bl _malloc

    cmp x0, #0
    bne endif
    mov x0, #1
    bl return

endif:
    mov x3, #2
    mov x4, #2
    mov x2, #30000
    add x2, x2, x0

    //move end addr back to quad boundary
    and x1, x2, #0xF                           //  x1 未对齐的多余部分
    sub x2, x2, x1                             //  对齐的部分
    mov x9, x0
loop: 
    stp x3, x4, [x9], #16
    cmp x9, x2
    blt loop

    //clear leftover bytes
loop2:
    strb w3, [x9], #1 
    subs x1, x1, #1
    b.ge loop2

done: 
    bl _free
    mov x0, #0

return:
    ldr x19, [sp, #16]
    ldp	x29, x30, [sp], #32             ; 16-byte Folded Reload
    ret

