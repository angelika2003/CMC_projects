%include "io.inc"

section .data
e0 dd 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
e9 dd e0, 0, 0, 0, 0, 0, 0, 0, 0, 0
e8 dd 0, 0, 0, 0, 0, 0, 0, 0, 0, e9
e7 dd 0, 0, 0, 0, 0, 0, 0, 0, e8, 0
e6 dd 0, 0, 0, 0, 0, 0, 0, e7, 0, 0
e5 dd 0, 0, 0, 0, 0, 0, e6, 0, 0, 0
e4 dd 0, 0, 0, 0, 0, e5, 0, 0, 0, 0
e3 dd 0, 0, 0, 0, e4, 0, 0, 0, 0, 0
e2 dd 0, 0, 0, e3, 0, 0, 0, 0, 0, 0
e1 dd 0, 0, e2, 0, 0, 0, 0, 0, 0, 0
root dd 0, e1, 0, 0, 0, 0, 0, 0, 0, 0
prefix dd 1, 2, 3, 4, 5, -1
lenght dd 5

section .text
global CMAIN
CMAIN:
    mov ecx, root
    mov edx, prefix
    push dword[lenght]    
    call bor
    ;add esp, 4
        
    xor eax, eax
    ret

                
bor:
    cmp dword[edx], -1
    je .print
    
    mov eax, dword[edx]
    mov ecx, dword[ecx+4*eax]
    add edx, 4
    push dword[lenght]  
    call bor
    ;add esp, 4
       
    jmp .end    
.print: 
    mov eax, -1
.search:
    inc eax
    cmp dword[ecx+4*eax], 0
    je .search
    
    PRINT_DEC 4, eax
    
    mov ecx, dword[ecx+4*eax]
    
    dec dword[esp+4]
    cmp dword[esp+4], 0
    jne .print
               
.end:   
    ret 4