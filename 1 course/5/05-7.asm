EXTERN strcmp
EXTERN scanf
EXTERN printf

section .rodata
    fmt_n dd '%d', 0
    fmt_s dd '%10s', 0
 
section .bss
    pt resd 1
    pt1 resd 1    
    n resd 1
    res resd 1
    x resb 5500 
 
section .text
global main
main:
    push ebp
    mov ebp, esp
    and esp, 0xfffffff0
 
    sub esp, 8 
    push n
    push fmt_n
    call scanf
    add esp, 16
 
    mov dword[pt], x
 
;первое считывание вне очереди
    sub esp, 8    
    push dword[pt]
    push fmt_s
    call scanf
    add esp, 16
 
    cmp eax, -1
    je .end
 
    inc dword[res]  
    add dword[pt], 11
    mov esi, 1
 
    cmp esi, dword[n]
    je .end
  
.while:    
    sub esp, 8    
    push dword[pt]
    push fmt_s
    call scanf
    add esp, 16
  
    mov dword[pt1], x
    mov edi, esi
 
.while_for_cmp:
    sub esp, 8
    push dword[pt]
    push dword[pt1]
    call strcmp
    add esp, 16   
    
    cmp eax, 0
    je .end_cmp  

    dec edi
    add dword[pt1], 11
    cmp edi, 0
    jne .while_for_cmp

    inc dword[res]   
.end_cmp:    
    add dword[pt], 11
    inc esi
    cmp esi, dword[n]
    jne .while
 
.end:   
    sub esp, 8
    push dword[res]
    push fmt_n
    call printf
    add esp, 16

    xor ecx, ecx 
 
    mov esp, ebp
    pop ebp
 
    xor eax, eax
    ret