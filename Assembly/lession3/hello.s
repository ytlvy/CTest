	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 11, 0	sdk_version 11, 3
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48                     ; =48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32                    ; =32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	mov	w8, #0
	stur	wzr, [x29, #-4]
	stur	w8, [x29, #-12]                 ; 4-byte Folded Spill
	bl	_getchar
	sturb	w0, [x29, #-5]
	adrp	x9, ___stdinp@GOTPAGE
	ldr	x9, [x9, ___stdinp@GOTPAGEOFF]
	ldr	x0, [x9]
	bl	_fflush
	ldursb	w8, [x29, #-5]
	adrp	x9, l_.str@PAGE
	add	x9, x9, l_.str@PAGEOFF
	mov	x0, x9
	mov	x9, sp
                                        ; implicit-def: $x1
	mov	x1, x8
	str	x1, [x9]
	bl	_printf
	ldursb	w8, [x29, #-5]
	mov	x0, x8
	bl	_printBinary
	ldur	w0, [x29, #-12]                 ; 4-byte Folded Reload
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48                     ; =48
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_printBinary                    ; -- Begin function printBinary
	.p2align	2
_printBinary:                           ; @printBinary
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48                     ; =48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32                    ; =32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	w0, [x29, #-4]
	ldur	w8, [x29, #-4]
	and	w8, w8, #0x1
	stur	w8, [x29, #-8]
LBB1_1:                                 ; =>This Inner Loop Header: Depth=1
	ldur	w8, [x29, #-4]
	cbz	w8, LBB1_4
; %bb.2:                                ;   in Loop: Header=BB1_1 Depth=1
	ldur	w8, [x29, #-8]
                                        ; implicit-def: $x0
	mov	x0, x8
	adrp	x9, l_.str.1@PAGE
	add	x9, x9, l_.str.1@PAGEOFF
	str	x0, [sp, #16]                   ; 8-byte Folded Spill
	mov	x0, x9
	mov	x9, sp
	ldr	x10, [sp, #16]                  ; 8-byte Folded Reload
	str	x10, [x9]
	bl	_printf
; %bb.3:                                ;   in Loop: Header=BB1_1 Depth=1
	ldur	w8, [x29, #-4]
	asr	w8, w8, #1
	stur	w8, [x29, #-4]
	ldur	w8, [x29, #-4]
	and	w8, w8, #0x1
	stur	w8, [x29, #-8]
	b	LBB1_1
LBB1_4:
	adrp	x0, l_.str.2@PAGE
	add	x0, x0, l_.str.2@PAGEOFF
	bl	_printf
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48                     ; =48
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"char: %c\n"

l_.str.1:                               ; @.str.1
	.asciz	"%d"

l_.str.2:                               ; @.str.2
	.asciz	"\n"

.subsections_via_symbols
