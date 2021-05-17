/*
x8, x16, x17, x18, 不可用
gcc -o student student.S
clang -g -c -x assembler student.S && clang student.o -o student

This is a version of the sin/cos functions that uses symmetry to enhance precision. 
The actual sin and cos routines convert the input to lie in the range 0 to pi/2, 
then pass it to the worker routine that computes the result. The result is then 
converted back to correspond with the original input.We calculate sin(x) using the first 
seven terms of the Taylor Series: sin(x) = x - x^3/3! + x^5/5! - x^7/7! + x^9/9! - ... and 
we calculate cos(x) using the relationship: cos(x) = sin(pi/2-x)
We start by defining a helper function, which we call sinq. The sinq function calculates
sin(x) for 0<=x<=pi/2. The input, x, must be an S(1,30) number. The factors of x that sinq 
will use are: x, x^3, x^5, x^7, x^9, x^11, and x^13.Dividing by (2n+1)! is changed to a 
multiply by a coefficient as we compute each term, we will add it to the sum, stored as an S(2,61). 
Therefore, we want the product of each power of x and its coefficient to be converted to an S(2,61) 
for the add. It turns out that this just requires a small shift.We build a table to decide how much 
to shift each product before adding it to the total. x^2 will be stored as an S(2,29), and x is given 
as an S(1,30). After multiplying x by x^2, we will shift left one bit, so the procedure is:
x will be an S(1,30) - multiply by x^2 and shift left x^3 will be an S(3,28) - multiply by x^2
and shift left x^5 will be an S(5,26) - multiply by x^2 and shift left x^7 will be an S(7,24)
- multiply by x^2 and shift left x^9 will be an S(9,22) - multiply by x^2 and shift left x^11 
will be an S(11,20)- multiply by x^2 and shift left x^13 will be an S(13,18)- multiply by x^2 
and shift left x^15 will be an S(15,16)- multiply by x^2 and shift left x^17 will be an S(17,14)
*/
/*
The following table shows the constant coefficients needed for calculating each term.
    -1/3! = AAAAAAAA as an S(-2,32)
    1/5! = 44444445 as an S(-6,32)
    -1/7! = 97F97F97 as an S(-12,32)
    1/9! = 5C778E96 as an S(-18,32)
    -1/11! = 9466EA60 as an S(-25,32)
    1/13! = 5849184F as an S(-32,32)
    -1/15! = 94603063 as an S(-40,32)
    1/17! = 654B1DC1 as an S(-48,32)

Combining the two tables of power and coefficient formats, we
can now determine how much shift we need after each step in
order to do all sums in S(2,61) format:

    power   powerfmt    coef     coeffmt              resultfmt   right shift
    x       S(1,30) *    1     (skip the multiply)                1 -> S(2,61)
    x^3     S(3,28) *   -1/3!    S(-2,32)            = S(2,61)    0 -> S(2,61)
    x^5     S(5,26) *   1/5!     S(-6,32)            = S(0,63)    2 -> S(2,61)
    x^7     S(7,24) *   -1/7!    S(-12,32)           = S(-4,64)   6 -> S(2,61)
    x^9     S(9,22) *   1/9!     S(-18,32)           = S(-8,64)   10-> S(2,61)
    x^11    S(11,20) *  -1/11!   S(-25,32)           = S(-13,64)  15-> S(2,61)
    x^13    S(13,18) *  1/13!    S(-32,32)           = S(-18,64)  20-> S(2,61)
    x^15    S(15,16) *  -1/15!   S(-40,32)           = S(-24,64)  26-> S(2,61)
    x^17    S(17,14) *  1/17!    S(-48,32)           = S(-30,64)  32-> S(2,61)
Note: the last row has a shift of 32, which indicates that
it can contribute no more than 1/2 bit of precision
to the 32-bit result.
*/

.data
.global _pi
_pi:   .word   0x3243F6A8
    .equ PI_LO, 0xF6A8
    .equ PI_HI, 0x3243
_pi_2:  .word  0x1921FB54
    .equ PI_2_LO, 0xFB54
    .equ PI_2_HI, 0x1921
_pi_x2: .word  0x6487ED51
    .equ PI_X2_LO, 0xED51
    .equ PI_X2_HI, 0x6487

    .p2align 3
_sinab: 
    .word 0xAAAAAAAA, 0 // -1/3! as an S(-2,32)
    .word 0x44444445, 2 // 1/5! as an S(-6,32)
    .word 0x97F97F97, 6 // -1/7! as an S(-12,32)
    .word 0x5C778E96, 10 // 1/9! as an S(-18,32)
    .word 0x9466EA60, 15 // -1/11! as an S(-25,32)
    .word 0x5849184F, 20 // 1/13! as an S(-32,32)
    .word 0x94603063, 26 // -1/15! as an S(-40,32)
    .word 0x654B1DC1, 32 // 1/17! as an S(-48,32)
    .equ tablen, 64//(.-_sintab) // set tablen to size of table

.section	__TEXT,__text
//-------------------------------------------------------------
// sinq(x)
// input: x -> S(1,30) s.t. 0 <= x <= pi/2
// returns sin(x) -> S(3,28)
// x0 : Sum of terms
// x1 : pointer to table
// x2 : next coefficient
// x3 : next shift
// x4 : x^2
// x5 : x^(2n-1)
// x6 : next term
// x7 : pointer to end of table

.global _sinq
.p2align	2
_sinq:   
	smull x4, w0, w0             //  x4 = x^2 S(3,60)
    mov x5, x0                   //  x5 = x^(2n-1)  as an S(1,30)
    
    //load sintab
    lsl x0, x0, #31              //x0 sum    S(2,61) by shifting it left
    adrp x1, _sinab@PAGE         //x1 table
    add x1, x1, _sinab@PAGEOFF
    add x1, x1, #8

    mov w2, #0xAAAAAAAA           //x2 next coefficient
    mov x3, #0                    //x3 = next shift
    asr x4, x4, #31               //x4 = x^2 S(2, 29)
    add x7, x1, #(tablen-8)         //x7 end tablee

    b firstmul
sloop:
    ldpsw x2, x3, [x1], #8       //

firstmul:
    //1 x^(2n-1)
    smull x5, w4, w5
    cmp x1, x7                  //test end table
    asr x5, x5, #31             //convert x^(2n-1) to S(3,28)

    //2 *coefficient
    smull x6, w5,w2             // mul coefficient
    add x6, x6, x6, lsr #63     //if the result is negative, then add one

    //3 shift 
    asr x6, x6, x3              // apply shift to make an S(2,61)

    add x0, x0, x6              // sum
    blt sloop

    asr x0, x0, #33            //convert from S(2,61) to S(3,28) and return
    ret

//-------------------------------------------------------------
// cos(x) NOTE: The cos(x) function does not return.
// It is an alternate entry point to sin(x).
// input: x -> S(3,28)
// returns cos(x) -> S(3,28)

.global _fixed_cos

_fixed_cos:
    cmp x0, 0
    bge cosgood
    //load 2PI
    adrp x1, _pi_x2@PAGE
    add x1, x1, _pi_x2@PAGEOFF
    ldrsw x1, [x1]
    add x0, x0, x1

cosgood:
    //load PI/2
    adrp x1, _pi_2@PAGE
    add x1, x1, _pi_2@PAGEOFF
    ldrsw x1, [x1]
    sub x0, x1, x0
    // now we just fall through into the sin function

//-------------------------------------------------------------
// sin(x)
// input: x -> S(3,28)
// returns sin(x) -> S(3,28)
    .global _fixed_sin
_fixed_sin:
    stp x29, x30, [sp, #-16]!

    // load w1, w2 and w3 with constants 
    mov w1, #PI_2_LO
    movk w1, #PI_2_HI, lsl #16
    mov w2, #PI_LO
    movk w2, #PI_HI, lsl #16
    mov w3, #PI_X2_LO
    movk w3, #PI_X2_HI, lsl #16

negl:
    cmp x0, #0
    bge nonneg
    add x0, x0, x3
    b negl

nonneg:
    cmp x0, x3
    ble inrange
    sub x0, x0, x3
    b nonneg

inrange:
    cmp x0, x1
    bgt chkq2
    // < PI/2
    lsl x0, x0, #2
    bl _sinq
    b sin_done

chkq2: 
    cmp x0, x2
    bgt chkq3
    // between PI/2 <> PI
    sub x0, x2, x0
    lsl x0, x0, #2
    bl _sinq
    b sin_done

chkq3: // x > PI
    add x1, x1, x2
    cmp x0, x1
    bgt chkq4
    // between PI <> PI*1.5
    sub x0, x0, x2
    lsl x0, x0, #2
    bl _sinq
    neg x0, x0
    b sin_done

chkq4:// between PI*1.5 <> PI*2
    sub x0, x0, x2
    sub x0, x2, x0
    lsl x0, x0, #2
    bl _sinq
    neg x0, x0

sin_done:

    ldp x29, x30, [sp], #16
    ret