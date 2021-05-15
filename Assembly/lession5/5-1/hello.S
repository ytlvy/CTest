/*
gcc -o hello hello.S
clang -g -c -x assembler hello.S && clang hello.o -o hello
 */

.section	__TEXT,__cstring
fmt_1: .string "Enter a number in hex: \n"

.section	__DATA,__data
.p2align 3
_a:   .quad   0x57
.p2align 3
_b:  .quad 117
.p2align 3
_c: .quad 33

.zerofill __DATA,__bss,_x,8,3           ; @x
.zerofill __DATA,__bss,_y,8,3           ; @y

.section	__TEXT,__text
.global _main
.p2align	2
_main:   
	stp	x29, x30, [sp, #-16]!             ; 头部16字节用来存储X30 x29


    adrp	x0, _a@PAGE
	ldr	x0, [x0, _a@PAGEOFF]
    adrp	x1, _b@PAGE
	ldr	x1, [x1, _b@PAGEOFF]
    adrp	x2, _c@PAGE
	ldr	x2, [x2, _c@PAGEOFF]

if:  // if((a<b) && (a<c))
    cmp x0, x1
    bge   elseif
    cmp x0, x2
    bge   elseif
    b endif
elseif:
    cmp x1, x2
    csel x0, x1, x2, lt

endif:
    adrp x9, _x@PAGE
    add x9, x9, _x@PAGEOFF
    str x0, [x9]

    //return
    mov x0, #0
    ldp	x29, x30, [sp], 16             ; 16-byte Folded Reload
	add	sp, sp, #144                     ; =48

    ret
