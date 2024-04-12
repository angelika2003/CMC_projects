%include "io.inc"

section .bss
    N resd 1

section .text
global CMAIN
CMAIN:
    GET_UDEC 4, N
    mov eax, 0
    
.while:
    test dword[N], 1
    je .no
    inc eax
.no:    
    shr dword[N], 1

    cmp dword[N], 0
    jne .while
    
    PRINT_DEC 4, eax
                
    xor eax, eax
    ret