; nasm -f macho64 -o hello2.o hello2.asm && ld hello2.o -o hello2 && ./hello2

%define SYSCALL_WRITE 0x2000004
%define SYSCALL_EXIT 0x2000001

;initialised data section
section .data
    ; Define constants
    num1:   equ 100
    num2:   equ 50
    ; initialize message
    msg:    db `Sum is correct!\n`
    msglen  equ $ - msg

section .text

global start

;; entry point
start:
    ; set num1's value to rax
    mov rax, num1
    ; set num2's value to rbx
    mov rbx, num2
    ; get sum of rax and rbx, and store it's value in rax
    add rax, rbx
    ; compare rax and 150
    cmp rax, 150
    ; go to .exit label if rax and 150 are not equal
    jne .exit
    ; go to .rightSum label if rax and 150 are equal
    jmp .rightSum

; Print message that sum is correct
.rightSum:
    ;; write syscall
    mov     rax, SYSCALL_WRITE
    ;; file descritor, standard output
    mov     rdi, 1
    ;; message address
    lea     rsi, [rel msg]
    ;; length of message
    mov     rdx, msglen
    ;; call write syscall
    syscall
    ; exit from program
    jmp .exit

; exit procedure
.exit:
    ; exit syscall
    mov    rax, SYSCALL_EXIT
    ; exit code
    mov    rdi, 0   ; first parameter
    ; call exit syscall
    syscall
