%include "io.inc"

section .text
global CMAIN
CMAIN:
    GET_DEC 4, eax
    GET_DEC 4, ebx
    
    cmp eax, ebx
    jg .while
    mov ecx, eax
    mov eax, ebx
    mov ebx, ecx
    
.while: 
    mov edx, 0
    div ebx
    mov eax, ebx
    mov ebx, edx   
    
    cmp ebx, 0
    jne .while

    PRINT_DEC 4, eax    
   
    xor eax, eax
    ret