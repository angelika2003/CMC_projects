extern printf       
extern scanf 

section .data
    fmt1 db `%u`, 0
    fmt2 db `0x%08X\n`, 0
    x dd 1

section .text
global main
main:
    push ebp        
    mov ebp , esp   
    and esp, 0xfffffff0
    
.l:
    sub esp, 8
    push x 
    push fmt1                       
    call scanf
    add esp , 16
    
    cmp eax, 0
    jl .end
    
    sub esp, 8
    push dword[x]        
    push fmt2       
    call printf     
    add esp , 16
    
    jmp .l

.end:

    mov esp, ebp    
    pop ebp         

    xor eax , eax
    ret