%include "io.inc"

section .bss
    num_0 resd 1
    N resd 1
    k resd 1
    sum1 resd 1
    pascal resd 10000

section .text
global CMAIN
CMAIN:
    GET_DEC 4, N
    GET_DEC 4, k
    
    mov eax, dword[N]
    xor ecx, ecx 
.while:
    inc ecx
    shr eax, 1
    cmp eax, 0
    jnz .while
    
;esi - длина числа N
     mov esi, ecx
     mov edi, esi
      
;треугольник паскаля
    mov dword[pascal + 4 * 99], 1
    mov eax, 0

.next_step:
    mov ebx, dword[pascal + 4 * eax + 4]
    mov edx, dword[pascal + 4 * eax]
    add edx,ebx
    mov dword[pascal + 4 * eax + 400], edx
    inc eax
    cmp eax, 9999
    jb .next_step
      
;первая сумма        ebx    
    mov ebx, 0
    
    mov ecx, dword[k]   
    imul ecx, 100
    
    mov eax, 99
    
    sub esi, 2
       
    cmp esi, dword[k]
    jb .second
    
    imul esi, 100
    
.sum1:
    mov edx, ecx
    add edx, eax
    
    add ebx, dword[pascal + 4 * edx]
    dec eax
    add ecx, 100
    
    cmp ecx, esi
    jbe .sum1   
    
                 
.second:                                                              
                                                                                                                                                                                                                                                                                              
;вторая сумма; edi - длина числа
    mov edx, 1  ;вспомогат для взятия бита
    mov ecx, edi
    
.loop:   
    shl edx, 1
    
    dec ecx
    cmp ecx, 1
    ja .loop
       
    dec edi   
    mov esi, dword[k] 
    
.while1:   
    cmp esi, 0
    jb .the_end

    dec edi

    shr edx, 1
    mov eax, dword[N]
    and eax, edx
 
    cmp eax, 0
    je .else1

    dec esi
    cmp edi, esi
    jb .the_end
    
    mov ecx, edi
    imul ecx, 100
    add ecx, 99
    sub ecx, edi
    add ecx, esi

    add ebx, dword[pascal + 4 * ecx] 
    inc esi
    jmp .end      

.else1:
    inc dword[num_0]

.else:  
    dec esi  
    
    cmp edi, esi
    jb .the_end

.end:                                                             
    cmp edi, 0
    jnz .while1                                                  

    mov edi, dword[k]
    cmp edi, [num_0]
    jne .the_end
    inc ebx                    

.the_end:                  
    PRINT_DEC 4, ebx                     
                     
    xor eax, eax
    ret