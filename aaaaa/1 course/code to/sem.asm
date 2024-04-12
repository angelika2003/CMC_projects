%include "io.inc"

section .bss
    a resd 1
    b resd 1

section .text
global CMAIN
CMAIN:
    push ebp                ; стандартный пролог
    mov ebp, esp            ; стандартный пролог

    GET_DEC 4, [a]
    GET_DEC 4, [b]    

    push dword[b]
    push dword[a]

    call gcd
    
    PRINT_DEC 4, eax

    mov esp, ebp            ; стандартный эпилог
    pop ebp                 ; стандартный эпилог

    xor eax, eax
    ret
    
;------------------------------------------------------------------------------------------------    

gcd:
    push ebp                ; стандартный пролог
    mov ebp, esp            ; стандартный пролог
    
    cmp dword[ebp+12], 0    ; if (b == 0) { return a; }
    je .b_zero
  
    mov eax, [ebp + 8]  ; eax <- a
    xor edx, edx    
    div DWORD[ebp+12]   ; edx <- a % b

    ; вызов gcd(b, a % b)
    
    push edx            ; на стек <- a % b
    push dword[ebp+12]  ; на стек <- b
                        ; (в обраном порядке)
    call gcd
        
    jmp .end

.b_zero:
    mov eax, [ebp+8]        ; if (b == 0) { return a; }

.end:
    mov esp, ebp            ; стандартный эпилог
    pop ebp                 ; стандартный эпилог
    
    ret