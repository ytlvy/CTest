/*
x8, x16, x17, x18, 不可用
gcc -o student student.S
clang -g -c -x assembler div.S && clang div.o -o div
 */

.section	__TEXT,__cstring
_msg: .string "%ld / %ld = %ld : %ld\n"

.data
.p2align 3
_x:   .quad   100
.p2align 3
_y:  .quad   -5

.p2align 3
_j:   .quad   100
.p2align 3
_k:  .quad   0xFFFFFFFFFFFFFFFF

.section	__TEXT,__text

.global _main
.p2align	2
_main:   
	stp	x29, x30, [sp, #-32]!             ; 头部16字节用来存储X30 x29
    str x19, [sp, #16]

    adrp x0, _x@PAGE          //x0 = Dividend
    ldr x0, [x0, _x@PAGEOFF]  
    adrp x1, _y@PAGE          //x1 = divisor
    ldr x1, [x1, _y@PAGEOFF]   
    bl _sdiv64

    //print result
    mov x4, x0
    mov x3, x1
    adrp x2, _y@PAGE          
    ldr x2, [x2, _y@PAGEOFF]  
    adrp x1, _x@PAGE        
    ldr x1, [x1, _x@PAGEOFF]  
    adrp x0, _msg@PAGE
    add x0, x0, _msg@PAGEOFF

    sub sp, sp, #32
    str x1, [sp]
    str x2, [sp, #8]
    str x3, [sp, #16]
    str x4, [sp, #24]
    bl _printf
    add sp, sp, #32

    #################################################### 128 div
    adrp x0, _x@PAGE          //x0 = DividendLow
    ldr x0, [x0, _x@PAGEOFF]
    adrp x1, _j@PAGE          //x1 = = DividendHi
    ldr x1, [x1, _j@PAGEOFF]
    //mov x1, #5

    adrp x2, _y@PAGE          //x2 = divisorLow
    ldr x2, [x2, _y@PAGEOFF]   
    adrp x3, _k@PAGE          //x4 = divisorHi
    ldr x3, [x3, _k@PAGEOFF]
    //mov x3, 0
    bl _sdiv128

    //print result
    mov x4, x0
    mov x3, x1
    adrp x2, _y@PAGE          
    ldr x2, [x2, _y@PAGEOFF]  
    adrp x1, _x@PAGE        
    ldr x1, [x1, _x@PAGEOFF]  
    adrp x0, _msg@PAGE
    add x0, x0, _msg@PAGEOFF

    sub sp, sp, #32
    str x1, [sp]
    str x2, [sp, #8]
    str x3, [sp, #24]
    str x4, [sp, #16]
    bl _printf
    add sp, sp, #32

    //return
    mov x0, #0
    ldr x19, [sp, #16]
    ldp	x29, x30, [sp], #32             ; 16-byte Folded Reload
    ret


###################
/*
  x0 dividend
  x1 divisor
  return quotient in x0, remainder in x1
 */
.global _udiv64
.p2align	2
_udiv64:
    cbnz x1, endif1            // zero check
    mov x0, #0
    mov x1, #0
    ret

endif1:
    clz x2, x1                // x2 = leading zero as count
    lsl x1, x1, x2
    mov x3, #0                // x3 = quotient
    add x2, x2, #1            // because loop after -1

divloop:
    lsl x3, x3, #1
    cmp x0, x1
    blo endif2               // 小于不触发计算
    orr x3, x3, #1
    sub x0, x0, x1

endif2://移位操作
    sub x2, x2, #1           // count--
    lsr x1, x1, #1           // shift divisor right
    cbnz x2, divloop         // count > 0
    mov x1, x0
    mov x0, x3
    ret

########################
.global _sdiv64
/*
  signed dive
  x0 dividend
  x1 divisor
  return quotient in x0, remainder in x1
 */
.p2align	2
_sdiv64:
    stp	x29, x30, [sp, #-32]!             ; Push FP, LR, &callee-saved
    str x19, [sp, #16]

    cmp x0, #0
    cneg x0, x0, lt
    cset x19, lt

    cmp x1, #0
    cneg x1, x1, lt
    eor x9, x19, #1
    csel x19, x9, x19, lt

    bl _udiv64

    cmp x19, #0      //Complement if sign bit is set
    cneg x0, x0, ne
    cneg x1, x1, ne
    
    ldr x19, [sp, #16]
    ldp	x29, x30, [sp], #32             ; Pop FP, LR, &callee-saved
    ret


#################################
.global _udiv128
/*
  128 div
  x0:x1 dividend  x0 low - x1 hi
  x2:x3 divisor   x2 low - x3 hi
  return quotient in x0:x1, remainder in x2:x3
 */
.p2align	2
_udiv128:
    orr x9, x2, x3        //zero check
    cbnz x9, endif3
    mov x0, #0
    mov x1, #0
    ret

endif3:
    mov x4, #0            //x4:x5   quotient             
    mov x5, #0

    //count leading zero
    clz x6, x3            //check hi
    cmp x6, #64
    b.lt endif4
    //cbnz x6, endif4
    clz x6, x2            //check low
    add x6, x6, #64       //add 64 hi

endif4://shift divisor

    //caculate x2 shift to x3 partial bits
    neg x7, x6            //x7 = -count
    add x8, x7, #128      //x8 = 128 - count
    add x9, x7, #64       //x9 = 64 - count

    cmp x9, #0
    csel x7, x8, x9, lt   //x7 msb carry -> x3
    b.lt shift128         //修正count > 64的处理情况

    //shift divisor x2:x3 << count
    lsl x3, x3, x6
    lsr x9, x2, x7        //tmp=Low >> (128-count)%64
    orr x3, x3, x9
    lsl x2, x2, x6

    b shiftend
shift128:
    mov x3, x2
    mov x2, 0
    sub x7, x6, #64
    lsl x3, x3, x7 


shiftend:
    add x6, x6, #1        //count+1
divloop128:

    lsl x5, x5, #1        //shift 0 into quotient
    lsr x9, x4, #63       // tmp = Low >> 63
    orr x5, x5, x9
    lsl x4, x4, #1

    cmp x1, x3
    bne endif5
    cmp x0, x2

endif5:
    blo endif6
    orr x4, x4, #1        //set LSB of quotient 1
    sub x0, x0, x2
    sub x1, x1, x3

endif6:
    sub x6, x6, #1
    lsr x2, x2, #1         //shift divisor right
    lsl x9, x3, #63        //LSB x3 << 63
    orr x2, x2, x9         
    lsr x3, x3, #1
    cbnz x6, divloop128

    mov x2, x0
    mov x3, x1
    mov x0, x4
    mov x1, x5
    ret

########################
.global _sdiv128
/*
  signed dive 128
  x0:x1 dividend  x0 low - x1 hi
  x2:x3 divisor   x2 low - x3 hi
  return quotient in x0:x1, remainder in x2:x3
 */
.p2align	2
_sdiv128:
    stp	x29, x30, [sp, #-32]!             ; Push FP, LR, &callee-saved
    str x19, [sp, #16]

    //compliment progress
    cmp x1, #0                      ;if dividendHi < 0
    bge endif7                         
    mvn x0, x0 
    mvn x1, x1
    adds x0, x0, #1
    adc x1, x1, xzr
    eor x19, x19, #1

endif7:
    cmp x3, #0
    bge endif8
    mvn x2, x2
    mvn x3, x3
    adds x2, x2, #1
    adc x3, x3, xzr
    eor x19, x19, #1

endif8:
    bl _udiv128

    cmp x19, #0
    beq endif9
    mvn x0, x0
    mvn x1, x1
    adds x0, x0, #1
    adc x1, x1, xzr 

endif9:

    ldr x19, [sp, #16]
    ldp	x29, x30, [sp], #32             ; Pop FP, LR, &callee-saved
    ret
