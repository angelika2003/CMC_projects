%include "io.inc"
extern printf

section .data
    fmt db `%ld`, 0
    
section .bss
    x resq 1    

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp
    
    mov eax, 50
    cdq
    
    mov dword[x], eax
    mov dword[x+4], edx
   
    push dword[x+4]  
    push dword[x]
    push fmt
    call printf
    add esp, 12    
    
    mov esp, ebp
    pop ebp
        
    xor eax, eax
    ret