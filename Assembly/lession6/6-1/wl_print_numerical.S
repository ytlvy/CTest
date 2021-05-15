### Definitions for the wordlistnode type

.equ wln_word,   0
.equ wln_count,  8
.equ wln_next,   16
.equ wln_size,   24

### Definitions for the wordlist type
.equ wl_nwords, 0
.equ wl_head,   8
.equ wl_size,   16

### Define NULL
.equ NULL,      0


/*
x0   source listnode
x1   dst    listnode
x2   currently moved node
x3   loop  cur
x4   loop  prev
w5   moved node count
w6   cur count
 */
.global _sort_numerical
.p2align	2
_sort_numerical:  
    stp x29, x30, [sp, #-16]!         
    
    mov x1, #NULL
    //loop until source list is empty
loopa: 
    cmp x0, #NULL
    beq endloopa

    mov x2, x0
    ldr w5, [x2, #wln_count]
    ldr x0, [x0, #wln_next]

    //find location to insert x2
    mov x3, x1   //maybe erro should be mov x3, x0
    mov x4, #NULL

loopb:
    cmp x3, #NULL
    beq found
    ldr w6, [x3, #wln_count]
    cmp w5, w6
    bgt found
    mov x4, x3
    ldr x3, [x3, #wln_next]
    b loopb

found:
    str x3, [x2, #wln_next]
    cmp x4, #NULL
    //repeat with next list item
    csel x1, x2, x1, eq   //x4 == NULL 代表插入在头部
    beq loopa
    str x2, [x4, #wln_next]
    b loopa

endloopa:
    mov x0, x1
    ldp x29, x30, [sp], #16           
    ret

//
.global _wl_print_numerical
.p2align	2
_wl_print_numerical:  
    stp x29, x30, [sp, #-32]! 
    str x0, [sp, #16]
    ldr x0, [x0, wl_head]
    bl _sort_numerical

    ldr x1, [sp, #16]
    str x0, [x1, #wl_head]

    mov x0, x1
    bl _wl_print

    ldp x29, x30, [sp], #32           
    ret