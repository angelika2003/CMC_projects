%include "io.inc"

extern scanf
extern malloc
extern printf

section .data
    fmt db `%d `, 0

section .bss
    x resd 1
    root resd 1
    
section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp
    
    push x
    push fmt
    call scanf
    
    cmp dword[x], 0
    je .endd
    
    push 8
    call malloc
    
    mov ecx, dword[x]
    mov dword[eax], ecx
    
    mov dword[root], eax
    
    
.while:
    push x
    push fmt
    call scanf
    
    cmp dword[x], 0
    je .end
    
    push dword[x]
    call add_node
    
    mov dword[root], eax
    
    jmp .while
        
.end:   
    mov ecx, dword[root]
    
.for_print:
    mov ebx, dword[ecx]
   
    push ecx
    push ebx
    push fmt
    call printf
    add esp, 8
    pop ecx
    

    
    mov ecx, dword[ecx+4]
    
    cmp ecx, 0
    je .endd  
    
    jmp .for_print                                    
    
    
.endd:
    mov esp, ebp
    pop ebp
    
    xor eax, eax
    ret
  
    
      
          
add_node:
    push ebp
    mov ebp, esp
    
    push 8
    call malloc
    
    mov ecx, dword[ebp+8]
    mov dword[eax], ecx
    
    mov ebx, dword[root]
    mov dword[eax+4], ebx
    
                                                                                     
    mov esp, ebp
    pop ebp
    ret    
    
    