%include "io.inc"
section .data
    const_2 dd 2
section .bss
    a resd 100
    n resd 1

section .text
global CMAIN
CMAIN:
    GET_DEC 4, n
    
    mov ecx, 0
.while_input:
    GET_DEC 4, [a+ecx*4]
    inc ecx
    cmp ecx, dword[n]
    jne .while_input
    
    mov esi, 0
    mov edi, dword[n]
    dec edi
    
.while:
    PRINT_DEC 4, esi
    PRINT_DEC 4, edi
    NEWLINE
    mov ebx, edi
    sub ebx, esi
    cmp ebx, 1
    je .end 
    
    mov eax, edi
    add eax, esi
    xor edx, edx
    div dword[const_2]
    
    mov ecx, dword[a+eax*4]
    cmp ecx, 0
    jne .one
    mov esi, eax
    jmp .while
.one:
    mov edi, eax
    jmp .while    

.end:
    PRINT_DEC 4, edi
    xor eax, eax
    ret