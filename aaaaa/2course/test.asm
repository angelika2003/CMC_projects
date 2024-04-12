%include "io.inc"

section .data
a db 1
b db 2
c db 3
d db 1
e db 0

section .text
global main

main:
push ebp
mov ebp, esp 

;получение 4*(d+e) в ecx
mov al, 4; al:=4
cbw ; ax:=4
mov cx, ax ; cx:=4

mov al, byte[d]; al:=d
cbw ; ax:=d
mov bx, ax

mov al, byte[e]; al:=e
cbw ; ax:=e
add ax, bx

imul cx; dx:ax = 4*(d+e)

ROL edx,16
mov dx, ax
mov ecx, edx

;получение c in ESI | EDI
mov al, byte[c]; al:=c
cbw ; ax:=c
cwde; eax:=c
cdq
mov esi, edx
mov edi, eax

;получение a*b^6 in EDX | EAX
mov al, byte[b]; al:=b
cbw ; ax:=b
cwde ; eax:=b
mov ebx, eax; ebx:=b

mov al, byte[a]; al:=a
cbw ; ax:=a
cwde ; eax:=a

imul ebx
imul ebx
imul ebx
imul ebx
imul ebx
imul ebx

;получение a*b^6+c

add eax, edi
adc edx, esi

;деление
idiv ecx ;результат в eax 

PRINT_DEC 4, eax

mov esp, ebp 
pop ebp
xor eax, eax
ret






















