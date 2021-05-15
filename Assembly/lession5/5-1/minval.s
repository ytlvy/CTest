	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 11, 0	sdk_version 11, 3
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16                     ; =16
	.cfi_def_cfa_offset 16
	str	wzr, [sp, #12]
	adrp	x8, _a@PAGE
	ldr	x8, [x8, _a@PAGEOFF]
	adrp	x9, _b@PAGE
	ldr	x9, [x9, _b@PAGEOFF]
	subs	x8, x8, x9
	b.ge	LBB0_3
; %bb.1:
	adrp	x8, _a@PAGE
	ldr	x8, [x8, _a@PAGEOFF]
	adrp	x9, _c@PAGE
	ldr	x9, [x9, _c@PAGEOFF]
	subs	x8, x8, x9
	b.ge	LBB0_3
; %bb.2:
	adrp	x8, _a@PAGE
	ldr	x8, [x8, _a@PAGEOFF]
	adrp	x9, _x@PAGE
	str	x8, [x9, _x@PAGEOFF]
	b	LBB0_7
LBB0_3:
	adrp	x8, _b@PAGE
	ldr	x8, [x8, _b@PAGEOFF]
	adrp	x9, _c@PAGE
	ldr	x9, [x9, _c@PAGEOFF]
	subs	x8, x8, x9
	b.ge	LBB0_5
; %bb.4:
	adrp	x8, _b@PAGE
	ldr	x8, [x8, _b@PAGEOFF]
	adrp	x9, _x@PAGE
	str	x8, [x9, _x@PAGEOFF]
	b	LBB0_6
LBB0_5:
	adrp	x8, _c@PAGE
	ldr	x8, [x8, _c@PAGEOFF]
	adrp	x9, _x@PAGE
	str	x8, [x9, _x@PAGEOFF]
LBB0_6:
LBB0_7:
	adrp	x8, _x@PAGE
	ldr	x8, [x8, _x@PAGEOFF]
	adrp	x9, _y@PAGE
	str	x8, [x9, _y@PAGEOFF]
	mov	w10, #0
	mov	x0, x10
	add	sp, sp, #16                     ; =16
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__DATA,__data
	.p2align	3                               ; @a
_a:
	.quad	87                              ; 0x57

	.p2align	3                               ; @b
_b:
	.quad	117                             ; 0x75

	.p2align	3                               ; @c
_c:
	.quad	33                              ; 0x21

.zerofill __DATA,__bss,_x,8,3           ; @x
.zerofill __DATA,__bss,_y,8,3           ; @y
.subsections_via_symbols
