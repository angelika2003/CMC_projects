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
    
    GET_UDEC 4, K
    GET_UDEC 4, N
    GET_UDEC 4, A
    
    xor edx, edx
    mov eax, dword[A]
    div dword[divider]
    mov eax, edx
           
    mov ecx, dword[N]
    mov esi, eax
    mov edi, eax
.while:    
    push edi
    push esi
    call F
    
    xor edx, edx
    div dword[divider]
    mov eax, edx
    
    mov esi, edi
    mov edi, eax
   
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
    inc ebx
 
    cmp eax, 0
    jne .while 
     
    mov eax, dword[ebp+12]
.shift: 
    mul dword[K]
    dec ebx
    cmp ebx, 0
    jne .shift   
     
    add eax, dword[ebp+8]
                            
    mov esp, ebp

    pop ebp        
    ret