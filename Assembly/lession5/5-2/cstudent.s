	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 11, 0	sdk_version 11, 3
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #112                    ; =112
	stp	x29, x30, [sp, #96]             ; 16-byte Folded Spill
	add	x29, sp, #96                    ; =96
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	stur	x8, [x29, #-8]
	str	wzr, [sp, #16]
	add	x8, sp, #20                     ; =20
	mov	x0, x8
	adrp	x1, l_.str@PAGE
	add	x1, x1, l_.str@PAGEOFF
	mov	x9, #30
	mov	x2, x9
	str	x8, [sp, #8]                    ; 8-byte Folded Spill
	str	x9, [sp]                        ; 8-byte Folded Spill
	bl	___strcpy_chk
	ldr	x8, [sp, #8]                    ; 8-byte Folded Reload
	add	x9, x8, #30                     ; =30
	mov	x0, x9
	adrp	x1, l_.str.1@PAGE
	add	x1, x1, l_.str.1@PAGEOFF
	ldr	x2, [sp]                        ; 8-byte Folded Reload
	bl	___strcpy_chk
	mov	w10, #2
	ldr	x8, [sp, #8]                    ; 8-byte Folded Reload
	strb	w10, [x8, #60]
	mov	w10, #88
	str	w10, [sp, #84]
	adrp	x9, ___stack_chk_guard@GOTPAGE
	ldr	x9, [x9, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x9, [x9]
	ldur	x11, [x29, #-8]
	subs	x9, x9, x11
	b.ne	LBB0_2
; %bb.1:
	mov	w8, #0
	mov	x0, x8
	ldp	x29, x30, [sp, #96]             ; 16-byte Folded Reload
	add	sp, sp, #112                    ; =112
	ret
LBB0_2:
	bl	___stack_chk_fail
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"Sam"

l_.str.1:                               ; @.str.1
	.asciz	"Smith"

.subsections_via_symbols
