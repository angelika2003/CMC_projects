%include "io.inc"

section .data
    p dd 1, 2, 3
    q dw 3, 4
    
section .text
global CMAIN
CMAIN:
    xor, eax, eax

    mov ecx, p
    cmp ecx, 0
    je .end

    mov ecx, q
    cmp ecx, 0
    je .end 
   
    mov bx, word[q]
    dec bx
    movsx ebx, bx

    add dword[p+2*4], ebx
    
    cmp dword[p+2*4], 0
    je .end 
 
    mov eax, 1      

.end:  
    xor eax, eax
    ret
    
    

    


