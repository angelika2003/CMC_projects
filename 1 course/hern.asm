%include "io.inc"

section .data
    p dd 1, 2, 3
    q dw 3, 4
    
section .text
global CMAIN
CMAIN:
    mov eax, p
    cmp eax, 0
    jne .no_1
    mov eax, 0
    jmp .end
.no_1:  
    mov eax, q
    cmp eax, 0
    jne .no_2
    mov eax, 0
    jmp .end 
.no_2:    
    mov bx, word[q]
    dec bx
    movsx ebx, bx
        PRINT_DEC 4, [p+2*4]
    NEWLINE
    add dword[p+2*4], ebx
    PRINT_DEC 4, [p+2*4]
    NEWLINE
    
    cmp dword[p+2], 0
    jne .no_3
    mov eax, 0
    jmp .end 
.no_3:  
    mov eax, 1      
    
     
.end:  
    PRINT_DEC 4, eax 
    xor eax, eax
    ret
    
    

    


