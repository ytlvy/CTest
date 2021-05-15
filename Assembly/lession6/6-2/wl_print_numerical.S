### Definitions for the wordlistnode type

.equ wln_word,   0
.equ wln_count,  8
.equ wln_left,   16
.equ wln_right,  24
.equ wln_height, 32
.equ wln_size,   40

### Definitions for the wordlist type
.equ wl_nwords, 0
.equ wl_head,   8
.equ wl_size,   16

### Define NULL
.equ NULL,      0

.section	__TEXT,__cstring
failstr: .string "Unable to allocate index\n"
fmtstr:  .string "%10d '%s'\n"

.text

#########################################
### Recursively traverses the tree, filling in the array of
### pointers
### wordlistnode **getptrs(wordslistnode *ptrs[], wordlistnode *node)
.global _getptrs
.p2align	2
_getptrs:  
    cmp x1, #0
    beq getptrs_exit

    stp x29, x30, [sp, #-32]!
    str x19, [sp, #16]

    mov x19, x1

    // ptrs = getptrs(ptrs, node->left)
    ldr x1, [x19, #wln_left]
    bl _getptrs

    // *(ptrs++)=node
    str x19, [x0], #8

    ldr x1, [x19, #wln_right]
    bl _getptrs

    ldr x19, [sp, #16]
    ldp x29, x30, [sp], #32

getptrs_exit:
    ret


##########################################

/*
wl_quicksort(wln **left, wln **right) quicksorts
the array of pointers in order of the word counts
 */
.global _wl_quicksort
.p2align	2
_wl_quicksort:  
    cmp x0, x1
    bge wl_quicksort_exit

    stp x29, x30, [sp, #-48]!
    stp x19, x20, [sp, #16]
    stp x21, x22, [sp, #32]

    ldr x12, [x0]               //x12 pivot
    ldr x12, [x12, #wln_count]
    mov x19, x0                 //x19 current left
    mov x20, x1                 //x20 current right
    mov x21, x0                 //x21 orignal left
    mov x22, x1                 //x22 orignal right

loopa:
    cmp x19, x20
    bgt final

    ldr x0, [x19]              // (*left)->count > pivot
    ldr x1, [x0, #wln_count]
    cmp x1, x12
    ble loopb                 //?
    add x19, x19, #8          // increment left
    b loopa

loopb:
    cmp x19, x20              // while left < right &&
    bgt final

    ldr x2, [x20]             // (*right)->count < pivot
    ldr x3, [x2, #wln_count]
    cmp x3, x12
    bge cmp                   //?
    sub x20, x20, #8
    b loopb

cmp:
    cmp x19, x20
    bgt final
    str x0, [x20], #-8        //swap pointers and 
    str x2, [x19], #8         //change indices
    b loopa

final:
    mov x0, x21        //quicksort array from
    mov x1, x20        //first to current right
    bl _wl_quicksort

    mov x0, x19        //quicksort array from
    mov x1, x22        //current left to last
    bl _wl_quicksort

    ldp x21, x22, [sp, #32]
    ldp x19, x20, [sp, #16]
    ldp x29, x30, [sp], #48   

wl_quicksort_exit:        
    ret

//
.global _wl_print_numerical
.p2align	2
_wl_print_numerical:  
    stp x29, x30, [sp, #-48]! 
    stp x19, x20, [sp, #16]
    str x21, [sp, #32]
    
    //wordlistnode **ptrs = malloc(list->nwords * sizeof(wordlistnode *))
    mov x19, x0                 
    ldr x20, [x0, #wl_nwords]   
    lsl x0, x20, #3          //x0 list->nwords*8
    bl _malloc

    //check return value
    cmp x0, #0
    bne malloc_ok

    adrp x0, failstr@PAGE
    add x0, x0, failstr@PAGEOFF
    bl _printf

    mov x0, #1
    ldr x21, [sp, #32]
    ldp x19, x20, [sp, #16]
    ldp x29, x30, [sp], #48
    bl _exit

malloc_ok:
    //getptrs(ptrs, list->root)
    mov   x21, x0
    ldr x1, [x19, #wl_head]
    bl _getptrs

    //wl_quicksort(**start, **end)
    mov x0, x21
    add x1, x0, x20, lsl #3
    sub x1, x1, #8
    bl _wl_quicksort

    //Print the word frequency list
    mov x19, #0

loop:
    cmp x19, x20
    bge done

    //printf("%10d '%s'\n", ptrs[i]->count, ptrs[i]->word)
    adrp x0, fmtstr@PAGE
    add x0, x0, fmtstr@PAGEOFF
    ldr x3, [x21, x19, lsl #3]
    add x19, x19, #1
    ldr w1, [x3, #wln_count]
    ldr x2, [x3, #wln_word]

    add sp, sp, #-16
    str w1, [sp]
    str x2, [sp, #8]
    bl _printf

    add sp, sp, #16

    b loop

done:
    ldr x21, [sp, #32]
    ldp x19, x20, [sp, #16]
    ldp x29, x30, [sp], #48

    ret