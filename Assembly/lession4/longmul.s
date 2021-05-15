	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 11, 0	sdk_version 11, 3
	.globl	_longMul                        ; -- Begin function longMul
	.p2align	2
_longMul:                               ; @longMul
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16                     ; =16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	str	x1, [sp]
	ldr	x8, [sp, #8]
	ldr	x9, [sp]
	mul	x0, x8, x9
	umulh	x1, x8, x9
	add	sp, sp, #16                     ; =16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #144                    ; =144
	stp	x29, x30, [sp, #128]            ; 16-byte Folded Spill
	add	x29, sp, #128                   ; =128
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	mov	w8, #0
	stur	wzr, [x29, #-4]
	adrp	x9, l_.str@PAGE
	add	x9, x9, l_.str@PAGEOFF
	mov	x0, x9
	str	w8, [sp, #60]                   ; 4-byte Folded Spill
	str	x9, [sp, #48]                   ; 8-byte Folded Spill
	bl	_printf
	adrp	x9, l_.str.1@PAGE
	add	x9, x9, l_.str.1@PAGEOFF
	mov	x0, x9
	mov	x10, sp
	sub	x11, x29, #16                   ; =16
	str	x11, [x10]
	str	x9, [sp, #40]                   ; 8-byte Folded Spill
	bl	_scanf
	ldr	x9, [sp, #48]                   ; 8-byte Folded Reload
	mov	x0, x9
	bl	_printf
	ldr	x9, [sp, #40]                   ; 8-byte Folded Reload
	mov	x0, x9
	mov	x10, sp
	sub	x11, x29, #24                   ; =24
	str	x11, [x10]
	bl	_scanf
	ldur	x9, [x29, #-16]
	ldur	x1, [x29, #-24]
	mov	x0, x9
	bl	_longMul
                                        ; implicit-def: $q0
	mov.d	v0[0], x0
	mov.d	v0[1], x1
	str	q0, [sp, #64]
	ldr	q0, [sp, #64]
                                        ; kill: def $d0 killed $d0 killed $q0
	stur	d0, [x29, #-32]
	ldr	q1, [sp, #64]
	mov.16b	v0, v1
	mov	d2, v1[1]
	mov	x9, #64
	subs	x10, x9, #64                    ; =64
	subs	x11, x9, #64                    ; =64
	fmov	x12, d0
	fmov	x13, d2
	lsl	x11, x13, x11
	orr	x11, x11, x12, lsr #0
	fmov	x12, d2
	lsr	x10, x12, x10
	cmp	x9, #64                         ; =64
	csel	x10, x11, x10, lo
	fmov	x11, d0
	cmp	x9, #0                          ; =0
	csel	x9, x11, x10, eq
	stur	x9, [x29, #-40]
	ldur	x9, [x29, #-16]
	ldur	x10, [x29, #-24]
	ldur	x11, [x29, #-40]
	ldur	x12, [x29, #-32]
	adrp	x0, l_.str.2@PAGE
	add	x0, x0, l_.str.2@PAGEOFF
	mov	x13, sp
	str	x9, [x13]
	str	x10, [x13, #8]
	str	x11, [x13, #16]
	str	x12, [x13, #24]
	bl	_printf
	ldr	w8, [sp, #60]                   ; 4-byte Folded Reload
	mov	x0, x8
	ldp	x29, x30, [sp, #128]            ; 16-byte Folded Reload
	add	sp, sp, #144                    ; =144
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"Enter a number in hex: "

l_.str.1:                               ; @.str.1
	.asciz	"%lx"

l_.str.2:                               ; @.str.2
	.asciz	"%016lx * %016lx = %016lx%016lx\n"

.subsections_via_symbols
