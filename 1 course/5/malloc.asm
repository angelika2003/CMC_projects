%include "io.inc"

extern malloc
extern free

SIZE_OF_INT EQU 4

section .bss
    x resd 1
    n resd 1

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp

    GET_DEC 4, [n]

    ;----------------------------------------
    mov al, [n]
    mov bl, SIZE_OF_INT
    mul bl   ; ax=4n

    cwde    ;ax->eax
    
    push eax
    call malloc

    add esp, 4
    ;----------------------------------------
   
    mov [x], eax
    
            
    mov ecx, 0
    mov ebx, [x]

.for_input:
    GET_DEC 4, [ebx + ecx * SIZE_OF_INT]
    inc ecx
    cmp ecx, [n]
    jl .for_input

    mov ecx, 0
    mov ebx, [x]

.for_print:
    PRINT_STRING `x[`
    PRINT_DEC 4, ecx
    PRINT_STRING `] = `
    PRINT_CHAR ` `
    PRINT_DEC 4, [ebx + ecx * SIZE_OF_INT]
    NEWLINE

    inc ecx
    cmp ecx, [n]
    jl .for_print

    push DWORD[x]
    call free
    add esp, 4
    
    mov esp, ebp
    pop ebp

    xor eax, eax
    ret