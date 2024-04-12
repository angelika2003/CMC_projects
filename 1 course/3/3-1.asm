%include "io.inc"
section .bss
    N resd 1
    x resd 1
    y resd 1
    z resd 1
    a resd 1

section .text
global CMAIN
CMAIN:
    GET_DEC 4, N
    GET_DEC 4, x
    GET_DEC 4, y
    GET_DEC 4, z
    
    mov eax, dword[x]
    cmp eax, dword[y]
    jge .noswapxy

    mov ebx, dword[y]
    mov dword[x], ebx
    mov dword[y], eax   
.noswapxy:      
    mov eax, dword[x]
    cmp eax, dword[z]
    jge .zx

    mov ebx, dword[y]
    mov ecx, dword[z]
    mov dword[y], eax
    mov dword[x], ecx  
    mov dword[z], ebx
    jmp .end   
.zx:
    mov ebx, dword[y]
    cmp ebx, dword[z]
    jge .end
    
    mov eax, dword[z]
    mov dword[z], ebx
    mov dword[y], eax           
.end:
    sub dword[N], 3
    cmp dword[N], 0
    jle .the_end
.while:
    GET_DEC 4, a  
    mov eax, dword[a] 
    cmp eax, dword[x]
    jl .naxy
    mov ebx, dword[x]
    mov ecx, dword[y]
    mov dword[z], ecx
    mov dword[y], ebx
    mov dword[x], eax
    jmp .end_while
.naxy:
    cmp eax, dword[y]
    jl .nxay 
    mov ecx, dword[y]
    mov dword[z], ecx
    mov dword[y], eax
    jmp .end_while
.nxay:  
    cmp eax, dword[z]  
    jl .end_while
    mov dword[z], eax
     
.end_while:       
    sub dword[N], 1
    cmp dword[N], 0
    jg .while      
      
.the_end:  
    PRINT_DEC 4, x 
    PRINT_CHAR ' ' 
    PRINT_DEC 4, y 
    PRINT_CHAR ' ' 
    PRINT_DEC 4, z   
    
    xor eax, eax
    ret