; nasm -f macho64 -o hello.o hello.asm && ld hello.o -o hello && ./hello

%define SYSCALL_WRITE 0x2000004
%define SYSCALL_EXIT  0x2000001

global start
start:
  mov rdi, 1
  lea rsi, [rel str]    ;mov rsi, str
  mov rdx, strlen
  mov rax, SYSCALL_WRITE
  syscall

  mov rax, SYSCALL_EXIT
  mov rdi, 0
  syscall

section .data
str:
  db `Hello, assembly!\n` ; to use escape sequences, use backticks
strlen equ $ - str