%include "io.inc"

section .bss
x_1 resd 1
x_2 resd 1
x_3 resd 1
x_4 resd 1
res_1 resd 1
res_2 resd 1

section .text
global CMAIN
CMAIN:
    push ebp                
    mov ebp, esp 
    
    GET_DEC 4, x_1
    GET_DEC 4, x_2
    GET_DEC 4, x_3
    GET_DEC 4, x_4
    
    push dword[x_1]
    push dword[x_2]   
    call p   
    mov [res_1], eax
    
    push dword[x_3]
    push dword[x_4]    
    call p   
    mov [res_2], eax
    
    push dword[res_1]
    push dword[res_2]    
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
    jg .recur  
    mov eax, dword[ebp+12]
    jmp .end
    
.recur:
    mov eax, dword[ebp+12] 
    mov edx, 0
    div dword[ebp+8]
    mov ecx, dword[ebp+8]
    push ecx
    push edx
    
    call p
  
.end:     
    mov esp, ebp
    pop ebp
    ret     