%include "io.inc"

section .bss
a11 resd 1
a12 resd 1
a21 resd 1
a22 resd 1
b1 resd 1
b2 resd 1

not_a11 resd 1
not_a12 resd 1
not_a21 resd 1
not_a22 resd 1
not_b1 resd 1
not_b2 resd 1

section .data
x dd 0
y dd 0

section .text
global CMAIN
CMAIN:
    GET_UDEC 4, a11
    GET_UDEC 4, a12
    GET_UDEC 4, a21
    GET_UDEC 4, a22
    GET_UDEC 4, b1
    GET_UDEC 4, b2
    
    mov eax, [a11]
    not eax
    mov [not_a11], eax
    
    mov eax, [a12]
    not eax
    mov [not_a12], eax
    
    mov eax, [a21]
    not eax
    mov [not_a21], eax    
    
    mov eax, [a22]
    not eax
    mov [not_a22], eax    
    
    mov eax, [b1]
    not eax
    mov [not_b1], eax    
    
    mov eax, [b2]
    not eax
    mov [not_b2], eax    
    
    
    ;xxx1
    mov eax, [not_a11]
    and eax, [not_a12]
    and eax, [a21]
    and eax, [not_a22]
    and eax, [not_b1]
    and eax, [b2]
    or [x], eax
    ;2
    mov eax, [not_a11]
    and eax, [a12]
    and eax, [a21]
    and eax, [not_a22]
    and eax, [not_b1]
    and eax, [b2]
    or [x], eax
    ;3   
    mov eax, [not_a11]
    and eax, [a12]
    and eax, [a21]
    and eax, [not_a22]
    and eax, [b1]
    and eax, [b2]
    or [x], eax
    ;4
    mov eax, [not_a11]
    and eax, [a12]
    and eax, [a21]
    and eax, [a22]
    and eax, [not_b1]
    and eax, [b2]
    or [x], eax    
    ;5
    mov eax, [not_a11]
    and eax, [a12]
    and eax, [a21]
    and eax, [a22]
    and eax, [b1]
    and eax, [not_b2]
    or [x], eax    
    ;6
    mov eax, [a11]
    and eax, [not_a12]
    and eax, [not_a21]
    and eax, [not_a22]
    and eax, [b1]
    and eax, [not_b2]
    or [x], eax   
    ;7
    mov eax, [a11]
    and eax, [not_a12]
    and eax, [not_a21]
    and eax, [a22]
    and eax, [b1]
    and eax, [not_b2]
    or [x], eax    
    ;8
    mov eax, [a11]
    and eax, [not_a12]
    and eax, [not_a21]
    and eax, [a22]
    and eax, [b1]
    and eax, [b2]
    or [x], eax                        
    ;9
    mov eax, [a11]
    and eax, [not_a12]
    and eax, [a21]
    and eax, [not_a22]
    and eax, [b1]
    and eax, [b2]
    or [x], eax       
    ;10
    mov eax, [a11]
    and eax, [not_a12]
    and eax, [a21]
    and eax, [a22]
    and eax, [b1]
    and eax, [not_b2]
    or [x], eax     
    ;11
    mov eax, [a11]
    and eax, [not_a12]
    and eax, [a21]
    and eax, [a22]
    and eax, [b1]
    and eax, [b2]
    or [x], eax     
    ;12
    mov eax, [a11]
    and eax, [a12]
    and eax, [not_a21]
    and eax, [a22]
    and eax, [not_b1]
    and eax, [b2]
    or [x], eax     
    ;13
    mov eax, [a11]
    and eax, [a12]
    and eax, [not_a21]
    and eax, [a22]
    and eax, [b1]
    and eax, [not_b2]
    or [x], eax     
    ;14
    mov eax, [a11]
    and eax, [a12]
    and eax, [a21]
    and eax, [not_a22]
    and eax, [not_b1]
    and eax, [b2]
    or [x], eax     
    ;15
    mov eax, [a11]
    and eax, [a12]
    and eax, [a21]
    and eax, [not_a22]
    and eax, [b1]
    and eax, [b2]
    or [x], eax 
    
    PRINT_UDEC 4, [x]
    PRINT_CHAR ' '

;yyy1
    mov eax, [not_a11]
    and eax, [not_a12]
    and eax, [not_a21]
    and eax, [a22]
    and eax, [not_b1]
    and eax, [b2]
    or [y], eax
    ;2
    mov eax, [not_a11]
    and eax, [not_a12]
    and eax, [a21]
    and eax, [a22]
    and eax, [not_b1]
    and eax, [b2]
    or [y], eax
    ;3   
    mov eax, [not_a11]
    and eax, [a12]
    and eax, [not_a21]
    and eax, [not_a22]
    and eax, [b1]
    and eax, [not_b2]
    or [y], eax
    ;4
    mov eax, [not_a11]
    and eax, [a12]
    and eax, [not_a21]
    and eax, [a22]
    and eax, [b1]
    and eax, [b2]
    or [y], eax    
    ;5
    mov eax, [not_a11]
    and eax, [a12]
    and eax, [a21]
    and eax, [not_a22]
    and eax, [b1]
    and eax, [not_b2]
    or [y], eax    
    ;6
    mov eax, [not_a11]
    and eax, [a12]
    and eax, [a21]
    and eax, [not_a22]
    and eax, [b1]
    and eax, [b2]
    or [y], eax   
    ;7
    mov eax, [not_a11]
    and eax, [a12]
    and eax, [a21]
    and eax, [a22]
    and eax, [b1]
    and eax, [not_b2]
    or [y], eax    
    ;8
    mov eax, [not_a11]
    and eax, [a12]
    and eax, [a21]
    and eax, [a22]
    and eax, [b1]
    and eax, [b2]
    or [y], eax                        
    ;9
    mov eax, [a11]
    and eax, [not_a12]
    and eax, [not_a21]
    and eax, [a22]
    and eax, [not_b1]
    and eax, [b2]
    or [y], eax       
    ;10
    mov eax, [a11]
    and eax, [not_a12]
    and eax, [not_a21]
    and eax, [a22]
    and eax, [b1]
    and eax, [b2]
    or [y], eax     
    ;11
    mov eax, [a11]
    and eax, [not_a12]
    and eax, [a21]
    and eax, [a22]
    and eax, [not_b1]
    and eax, [b2]
    or [y], eax     
    ;12
    mov eax, [a11]
    and eax, [not_a12]
    and eax, [a21]
    and eax, [a22]
    and eax, [b1]
    and eax, [not_b2]
    or [y], eax     
    ;13
    mov eax, [a11]
    and eax, [a12]
    and eax, [not_a21]
    and eax, [not_a22]
    and eax, [b1]
    and eax, [not_b2]
    or [y], eax     
    ;14
    mov eax, [a11]
    and eax, [a12]
    and eax, [not_a21]
    and eax, [a22]
    and eax, [not_b1]
    and eax, [b2]
    or [y], eax     
    ;15
    mov eax, [a11]
    and eax, [a12]
    and eax, [not_a21]
    and eax, [a22]
    and eax, [b1]
    and eax, [b2]
    or [y], eax         
    ;16
    mov eax, [a11]
    and eax, [a12]
    and eax, [a21]
    and eax, [not_a22]
    and eax, [not_b1]
    and eax, [b2]
    or [y], eax     
    ;17
    mov eax, [a11]
    and eax, [a12]
    and eax, [a21]
    and eax, [not_a22]
    and eax, [b1]
    and eax, [not_b2]
    or [y], eax     
    ;18
    mov eax, [a11]
    and eax, [a12]
    and eax, [a21]
    and eax, [a22]
    and eax, [b1]
    and eax, [b2]
    or [y], eax 
    
    PRINT_UDEC 4, [y]          
  
  
  
    xor eax, eax
    ret