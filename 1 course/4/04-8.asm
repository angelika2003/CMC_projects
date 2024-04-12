%include "io.inc"

section .bss
N resd 1
K resd 1
res resd 1

section .text
global CMAIN
CMAIN:
    push ebp                
    mov ebp, esp 
    
    GET_UDEC 4, N
    GET_UDEC 4, K
    
    mov dword[res], 0
    mov eax, dword[N]
    add dword[res], eax
    
.l:   
    push eax
    mov esi, eax
    
    call summ
    
    add dword[res], eax
  
    cmp esi, eax
    jne .l
  
    PRINT_UDEC 4, [res]
           
    mov esp, ebp            
    pop ebp                    
        
    xor eax, eax
    ret
    
summ:   
    push ebp
    mov ebp, esp
    
    mov eax, dword[ebp+8]
    xor ecx, ecx
    
.while:    
    xor edx, edx
    div dword[K]
    add ecx, edx
    
    cmp eax, 0
    ja .while
             
    mov eax, ecx 
      
    mov esp, ebp
    pop ebp
    ret    
    
    