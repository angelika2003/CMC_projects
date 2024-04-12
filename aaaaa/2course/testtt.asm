%include "io.inc"

section .bss
    str_out resb 50
   
section .data
    str_in db "Abcd aBc abcD", 0
    
    word_len db 0 

section .text
    global _start
    
_start:
    mov ax, 0x00
    mov ds, ax
    
    lea si, [str_in]
    lea di, [str_out]
    
l:
    mov cx, 0
len: 
    lodsb
    cmp al, ' '
    je end_word
    cmp al, '\n'
    je end_word
    cmp al, '\0'
    je last_word
    inc cx
    jmp len
    
end_word:
    mov bl, al
    mov [word_len], cx
    
    dec si
    dec si
    
m:
    std
    lodsb
    cld
    stosb
    loop m
    
    add si, [word_len]
    mov [si], bl
    inc si
    jmp l
    xor eax, eax
    ret
    
last_word:
    dec si
    dec si
    
m1:
    std
    lodsb
    cld
    stosb
    loop m1
    
    add si, [word_len]
    mov byte [si], 0x00
    
    mov ax, 0x4c00
    int 0x21
    
    