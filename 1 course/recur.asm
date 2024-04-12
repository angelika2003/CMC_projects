%include "io.inc"

extern scanf
extern printf

section .data
    fmt db '%d', 0
    fmt_2 db '%d %d', 0

section .bss
    n resd 1
    a resd 1
    b resd 1

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp
    
    push b
    push a
    push fmt_2
    call scanf
    add esp, 8
    
    push dword[b]
    push dword[a]
    call evclid
    add esp, 8
    
    push eax
    push fmt
    call printf
    add esp, 8
        
    mov esp, ebp
    pop ebp
    xor eax, eax
    ret
    
    
;b +12
;a +8   
evclid:
    push ebp
    mov ebp, esp
    push esi
    push edi
    
    mov esi, dword[ebp+8]
    mov edi, dword[ebp+12]
    
    cmp edi, 0
    je .end_a    
    
    jge .a_gr
    
    push esi
    push edi
    call evclid
    add esp, 8
    jmp .end_evcl
.a_gr:
    xor edx, edx
    mov eax, esi
    div edi

    push edx
    push edi
    call evclid
    add esp, 8
    jmp .end_evcl
        
    
    
.end_a:  
    mov eax, esi  
.end_evcl:   
    pop edi
    pop esi         
    mov esp, ebp
    pop ebp
    ret    

;n +8        
n_numbers:
    push ebp
    mov ebp, esp
    push esi
    
    mov esi, dword[ebp+8]
    
    cmp esi, -1
    je .end_n
    
    dec esi
    push esi
    call n_numbers
    add esp, 4
    
    inc esi
    push esi
    push fmt
    call printf
    add esp, 8    
    
.end_n:  
    pop esi    
    mov esp, ebp
    pop ebp
    ret                
    
;n +8 /////////////////////////////   
fib:
    push ebp
    mov ebp, esp
    push ebx
    push esi
    
    mov ebx, dword[ebp+8]
    mov esi, 0
    
    cmp ebx, 1
    je .end_1
    
    cmp ebx, 2
    je .end_1
    
    dec ebx
    push ebx
    call fib
    add esp, 4
    
    mov esi, eax
    
    dec ebx
    push ebx
    call fib
    add esp, 4 
    
    add eax, esi
    jmp .end_fib
    
.end_1:
    mov eax, 1      
    
.end_fib:
    pop esi
    pop ebx       
    mov esp, ebp
    pop ebp
    ret   