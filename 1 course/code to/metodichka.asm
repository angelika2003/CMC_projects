%include "io.inc"


section .text
global CMAIN
CMAIN:
    mov al, 194
    add al, 205

    xor eax, eax
    ret