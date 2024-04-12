%include "io.inc"

section .bss
x resb 1
y resb 1

section .data
desk dd 8
two dd 2

section .text
global CMAIN
CMAIN:
    GET_CHAR x
    GET_DEC 1, y
    sub byte[x], 'A'
    add byte[x], 1
    
    movsx eax, byte[x]
    neg eax
    add eax, dword[desk]
    
    movsx ebx, byte[y]
    neg ebx
    add ebx, dword[desk]
    
    imul eax, ebx
    
    xor edx, edx
    
    div dword [two]
    
    PRINT_DEC 4, eax    
    
    xor eax, eax
    ret