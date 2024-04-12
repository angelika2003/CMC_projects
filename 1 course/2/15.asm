%include "io.inc"

section .bss
x1 resd 1
x2 resd 1
x3 resd 1
y1 resd 1
y2 resd 1
y3 resd 1

section .data
const dd 2;

section .text
global CMAIN
CMAIN:
    GET_DEC 4, x1
    GET_DEC 4, y1
    GET_DEC 4, x2
    GET_DEC 4, y2
    GET_DEC 4, x3
    GET_DEC 4, y3
    
    mov eax, dword[x2]
    sub eax, dword[x1]
    
    mov ebx, dword[y3]
    sub ebx, dword[y1] 
    
    imul eax, ebx
    
    mov edx, dword[x3]
    sub edx, dword[x1]
    
    mov ebx, dword[y2]
    sub ebx, dword[y1] 
    
    imul edx, ebx
    
    sub eax, edx
    
    cdq
    xor eax, edx
    sub eax, edx
    
    mov edx, 0
    
    div dword[const]
    PRINT_DEC 4, eax
    PRINT_CHAR `.`
    imul edx, 5

    PRINT_DEC 4, edx
   
    xor eax, eax
    ret