extern fopen
extern fscanf
extern printf

section .rodata
    filename_from   db `data.in`, 0
    read_mode       db `r`,0
    fmt db `%d`, 0
    
section .bss    
    x resd 1
    fp resd 1
    res resd 1
   
section .text
global main
main:
    push ebp        
    mov ebp , esp  
    and esp, 0xfffffff0
    
    sub esp, 8
    push read_mode      
    push filename_from           
    call fopen     
    add esp, 16
    
    mov [fp], eax
   
.while:   
    sub esp, 4               
    push x
    push fmt
    push dword[fp]
    call fscanf
    add esp, 16       
    
    cmp eax, 0
    jle .end
    inc dword[res]
    jmp .while
    
.end:
    sub esp, 8
    push dword[res]    
    push fmt      
    call printf     
    add esp , 16

    mov esp, ebp    
    pop ebp         

    xor eax , eax
    ret