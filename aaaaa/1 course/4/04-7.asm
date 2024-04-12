%include "io.inc"

section .bss
K resd 1
N resd 1
A resd 1

section .data
divider dd 2011

section .text
global CMAIN
CMAIN:
    push ebp                
    mov ebp, esp 
    
    GET_DEC 4, K
    GET_DEC 4, N
    GET_DEC 4, A
    
    xor edx, edx
    mov eax, dword[A]
    div dword[divider]
    mov eax, edx
     
    mov ecx, dword[N]
.while:
    imul eax, eax
    
    push eax
    call F
    
    xor edx, edx
    div dword[divider]
    mov eax, edx
   
    dec ecx
    cmp ecx, 0
    jne .while    

    PRINT_DEC 4, eax        
 
    mov esp, ebp
    pop ebp
        
    xor eax, eax
    ret

F:
    push ebp                
    mov ebp, esp 
    
    mov eax, dword[ebp+8]
    mov ebx, 0
.while:
    xor edx, edx
    div dword[K]
    imul ebx, dword[K]
    add ebx, edx
 
    cmp eax, 0
    jne .while 
     
    mov eax, ebx        
                    
    mov esp, ebp
    pop ebp        
    ret  