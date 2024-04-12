%include "io.inc"
    N equ 3
section .bss
    n resd 1
    a resd 1000 
    k resd 1

section .text
global CMAIN
CMAIN:
    GET_DEC 4, n
            
       
;    mov eax, dword[n]
;    mul dword[n]
;    mov ecx, 0     
;.for_input:
;    GET_DEC 4, [a+ecx*4]   
;    inc ecx
;    cmp ecx, eax
;    jne .for_input
    
    
;    mov ebx, dword[n]
    ;dec ebx
    
;    xor esi, esi
;    mov ecx, 0
;.for_output:
;    cmp esi, ebx
;    jne .no
;    NEWLINE
;    mov esi, 0    
;.no:    
;    PRINT_DEC 4, [a+ecx*4]
;    inc ecx
;    inc esi
;    cmp ecx, eax
;    jne .for_output   
    mov esi, 0
.for_1:
    mov edi, 0
.for_2:
    GET_DEC 4, eax
    imul edx, esi, N
    add edx, edi
    
    mov dword[a+edx*4], eax
    ;PRINT_DEC 4, edx
    
    inc edi
    cmp edi, dword[n]
    jne .for_2
    
    inc esi
    cmp esi, dword[n]
    jne .for_1  
    
;///////////////////////////////////////////////////////      
    mov esi, 0
.for_1t:
    mov edi, dword[k]
    inc dword[k]
.for_2t:
    
    imul edx, esi, N
    add edx, edi
    
    mov eax, dword[a+edx*4]
    
    imul ecx, edi, N
    add ecx, esi
    
    mov ebx, dword[a+ecx*4]
    
    mov dword[a+ecx*4], eax
    mov dword[a+edx*4], ebx
    
    inc edi
    cmp edi, dword[n]
    jne .for_2t
       
    inc esi
    cmp esi, dword[n]
    jne .for_1t     
    
                      
          
            
              
                  
    
;//////////////////////////////////////////////////////////////    
    mov esi, 0
.for_1p:
    mov edi, 0
.for_2p:
    
    imul edx, esi, N
    add edx, edi
    
    PRINT_DEC 4, [a+edx*4]
    
    inc edi
    cmp edi, dword[n]
    jne .for_2p
    
    NEWLINE
    
    inc esi
    cmp esi, dword[n]
    jne .for_1p      

    xor eax, eax
    ret