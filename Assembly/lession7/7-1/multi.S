/*
x8, x16, x17, x18, 不可用
gcc -o student student.S
clang -g -c -x assembler multi.S && clang multi.o -o multi
 */

.section	__TEXT,__cstring
_msg: .string "%ld * %ld = %016ld%016ld\n"

.data
.p2align 3
_x:   .quad   0x57
.p2align 3
_y:  .quad 0x75

.section	__TEXT,__text
.global _main
.p2align	2

/*
 Multiplies x and y by adding a series of partial products.
 Shifts x(multiplicand) left and y(multiplier) right. Only
 adds if the least significant bit of multiplier is 1.
 */
_main:   
	stp	x29, x30, [sp, #-32]!             ; 头部16字节用来存储X30 x29

    mov x0, #0                //x0 = resultLow
    mov x1, #0                //x1 = resultHight
    adrp x2, _x@PAGE          //x2 = multiplicandLow
    ldr x2, [x2, _x@PAGEOFF]  
    mov x3, #0                //x3 = multiplicandHigh
    adrp x4, _y@PAGE          //x4 = multiplier
    ldr x4, [x4, _y@PAGEOFF]   

loop:
    tst x4, #1                //only add if lowest is 1
    beq endif
    adds x0, x0, x2
    adc  x1, x1, x3

endif:// shift 128-bit multiplicand left. carry bit from lo to hi
    ands xzr, x2, #(1<<63)   //test multiplicand most significant bit
    lsl  x2, x2, #1
    lsl  x3, x3, #1
    cinc x3, x3, ne          // condition inc x3

    //shift multiplier right
    lsr x4, x4, #1

    //if (y != 0) repeat loop
    cmp x4, #0
    bne loop

    //print result
    mov x4, x0
    mov x3, x1
    adrp x2, _x@PAGE          
    ldr x2, [x2, _x@PAGEOFF]  
    adrp x1, _y@PAGE        
    ldr x1, [x1, _y@PAGEOFF]  
    adrp x0, _msg@PAGE
    add x0, x0, _msg@PAGEOFF

    sub sp, sp, #32
    str x1, [sp]
    str x2, [sp, #8]
    str x3, [sp, #16]
    str x4, [sp, #24]
    bl _printf
    add sp, sp, #32

    //return
    mov x0, #0
    ldp	x29, x30, [sp], #32             ; 16-byte Folded Reload
    ret
