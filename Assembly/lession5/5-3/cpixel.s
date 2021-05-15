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
	stur	wzr, [x29, #-4]
	mov	x0, #30000
	bl	_malloc
	str	x0, [sp, #16]
	ldr	x8, [sp, #16]
	cbnz	x8, LBB0_2
; %bb.1:
	adrp	x8, ___stderrp@GOTPAGE
	ldr	x8, [x8, ___stderrp@GOTPAGEOFF]
	ldr	x0, [x8]
	adrp	x1, l_.str@PAGE
	add	x1, x1, l_.str@PAGEOFF
	bl	_fprintf
	mov	w9, #1
	stur	w9, [x29, #-4]
	b	LBB0_11
LBB0_2:
	str	wzr, [sp, #12]
LBB0_3:                                 ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB0_5 Depth 2
	ldr	w8, [sp, #12]
	cmp	w8, #100                        ; =100
	b.ge	LBB0_10
; %bb.4:                                ;   in Loop: Header=BB0_3 Depth=1
	str	wzr, [sp, #8]
LBB0_5:                                 ;   Parent Loop BB0_3 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	ldr	w8, [sp, #8]
	cmp	w8, #100                        ; =100
	b.ge	LBB0_8
; %bb.6:                                ;   in Loop: Header=BB0_5 Depth=2
	ldr	x8, [sp, #16]
	ldr	w9, [sp, #12]
	mov	w10, #100
	mul	w9, w9, w10
	ldr	w11, [sp, #8]
	add	w9, w9, w11
	mov	w11, #3
	smaddl	x8, w9, w11, x8
	mov	w9, #0
	strb	w9, [x8]
	ldr	x8, [sp, #16]
	ldr	w11, [sp, #12]
	mul	w11, w11, w10
	ldr	w12, [sp, #8]
	add	w11, w11, w12
	mov	w12, #3
	smaddl	x8, w11, w12, x8
	strb	w9, [x8, #1]
	ldr	x8, [sp, #16]
	ldr	w11, [sp, #12]
	mul	w10, w11, w10
	ldr	w11, [sp, #8]
	add	w10, w10, w11
	mov	w11, #3
	smaddl	x8, w10, w11, x8
	strb	w9, [x8, #2]
; %bb.7:                                ;   in Loop: Header=BB0_5 Depth=2
	ldr	w8, [sp, #8]
	add	w8, w8, #1                      ; =1
	str	w8, [sp, #8]
	b	LBB0_5
LBB0_8:                                 ;   in Loop: Header=BB0_3 Depth=1
; %bb.9:                                ;   in Loop: Header=BB0_3 Depth=1
	ldr	w8, [sp, #12]
	add	w8, w8, #1                      ; =1
	str	w8, [sp, #12]
	b	LBB0_3
LBB0_10:
	ldr	x0, [sp, #16]
	bl	_free
	stur	wzr, [x29, #-4]
LBB0_11:
	ldur	w0, [x29, #-4]
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48                     ; =48
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__const
	.globl	_kImageWidth                    ; @kImageWidth
	.p2align	2
_kImageWidth:
	.long	100                             ; 0x64

	.globl	_kImageHeight                   ; @kImageHeight
	.p2align	2
_kImageHeight:
	.long	100                             ; 0x64

	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"Error: out of memory. \n"

.subsections_via_symbols
