%include "io.inc"

extern fopen
extern fclose
extern fprintf
extern fscanf

section .bss
    s resb 100

section .rodata
    fn_from db `input.txt`, 0
    fn_to db `output.txt`, 0
    w db `w`, 0
    r db `r`, 0
    lc0 db `%s\n`, 0
    lc1 db `%100s`, 0
    
section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp
    and esp, 0xfffffff0
    sub esp, 16
    
    mov dword[esp], fn_from
    mov dword[esp+4], r
    call fopen
    mov edi, eax
    
    mov dword[esp], fn_to
    mov dword[esp+4], w
    call fopen
    mov ebx, eax
    
    xor esi, esi          
    .while:
        mov dword[esp], edi
        mov dword[esp+4], lc1
        mov dword[esp+8], s
        call fscanf
        
        cmp eax, -1
        je .exit
        
        mov dword[esp], ebx
        mov dword[esp+4], lc0
        mov dword[esp+8], s
        call fprintf
        
        jmp .while
    .exit:
        mov dword[esp], ebx
        call fclose
        
        mov dword[esp], edi
        call fclose
        
    leave
    xor eax, eax
    ret
