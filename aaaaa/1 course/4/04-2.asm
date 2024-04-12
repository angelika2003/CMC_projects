%include "io.inc"

section .bss
N resd 1

section .data
notation dd 3

section .text
global CMAIN
CMAIN:
    push ebp                
    mov ebp, esp 
    
    GET_UDEC 4, N
    
    push 0
    push dword[N]  
    call p   
       
    PRINT_DEC 4, eax
           
    mov esp, ebp            
    pop ebp                    
        
    xor eax, eax
    ret
    
p:
    push ebp
    mov ebp, esp
    
    cmp dword[ebp+8], 0
    ja .recur  
    mov eax, dword[ebp+12]
    jmp .end
    
.recur:
    mov eax, dword[ebp+8] 
    mov edx, 0
    div dword[notation]
    
    mov ecx, dword[ebp+12]
    
    cmp edx, 1
    jne .not_one
    inc ecx    

.not_one:
    push ecx
    push eax

    call p           
.end:     
    mov esp, ebp
    pop ebp
    ret 