%include "io.inc"

section .bss
N resd 1

section .text
global CMAIN
CMAIN:    
    GET_DEC 4, N       
    mov ecx, 2

.while:
    mov eax, dword[N]
    mov edx, 0
    div ecx
        
    mov ebx, ecx
    imul ebx, ecx
    cmp ebx, dword[N]
    jg .end
    
    inc ecx
    cmp edx, 0
    jne .while
        
    dec ecx
    
    mov eax, dword[N]
    mov edx, 0
    div ecx
       
    PRINT_DEC 4, eax
    jmp .the_end

.end:
    PRINT_CHAR '1'
.the_end:    
    xor eax, eax
    ret