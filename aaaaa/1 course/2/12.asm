%include "io.inc"

section .bss
x resb 1

section .data
const db 13;
card db `A23456789TJQK`
suit db `SCDH`

section .text
global CMAIN
CMAIN:
    GET_DEC 1, x
    
    mov ax, word[x]
    sub ax, 1
    div byte[const]
    
    movsx ecx, al

    ; al частное. ah остаток
    
    mov ax, word[x]
    div byte[const]
    
    movsx ebx, ah
    
    PRINT_CHAR card+ebx
    PRINT_CHAR suit+ecx
      
    xor eax, eax
    ret