/*
gcc -o hello hello.S
 */



.zerofill __DATA,__bss
.section	__DATA,__data
i:  .word 

.section	__TEXT,__cstring
mesg:   .asciz "Hello World!\n"

.section	__TEXT,__text
.global _main
.p2align	2
_main:   
    stp x29, x30, [sp, # - 16]!

    adrp x0, mesg@PAGE
	add	x0, x0, mesg@PAGEOFF
	str	w8, [sp, #4]                    ; 4-byte Folded Spill
	bl	_printf

    //return
    mov w0, #0
    ldp x29, x30, [sp], #16

    ret

.equ arysize, (. - _main)