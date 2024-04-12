%include "io.inc"

; отсортировать строку
;
; zdert -> dertz

section .data
    a dd 3, 5,      7, 8,            2, 1,         0, 0,            3, 4

extern qsort

SIZE_OF_CHAR equ 1

section .text
comparator:
    push ebp
    mov ebp, esp
    
    
    push esi
    push edi
    
    mov esi, [ebp + 8]      ; void* pa
    mov edi, [ebp + 12]     ; void* pb 
    
    mov esi, dword[esi]   
    mov edi, dword[edi]   
    
    PRINT_STRING `cmp `
    PRINT_DEC 4, esi
    PRINT_STRING ` vs. `
    PRINT_DEC 4, edi
    NEWLINE
                    
    mov eax, esi
    sub eax, edi
    
    pop edi
    pop esi     
                                        
    mov esp, ebp
    pop ebp
   
    ret

global CMAIN
CMAIN:
    push ebp
    mov ebp, esp
    
    push comparator
    push 8
    push 5
    push a  ; адрес начала массива        
    call qsort    
    add esp, 16

    mov ecx, 0
.for_print:
    PRINT_DEC 4, [a + ecx*4]
    PRINT_CHAR ' '
    PRINT_DEC 4, [a + ecx*4+ 4]
    NEWLINE
    inc ecx
    inc ecx
    cmp ecx, 10
    jl .for_print
    
    mov esp, ebp
    pop ebp
    
    xor eax, eax
    ret