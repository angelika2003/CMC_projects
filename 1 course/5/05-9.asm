%include "io.inc"

extern scanf
extern printf

section .data
    fmt db '%d ', 0
    new_l db `\n`, 0

section .bss
    n resd 1
    array resd 1000000 ;текущий ответ
    res resd 1000000   ;предполагаемый ответ
    size resd 1
    res_size resd 1
    
    cur_tr resq 1
    max_tr resq 1
    zero resq 1
    x resq 1
    

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp
    
    push n
    push fmt
    call scanf
    add esp, 8
    
    cmp dword[n], 0
    je .end
    
.for:

;считали размер текущего
    push size
    push fmt
    call scanf
    add esp, 8

;сам массив
    xor ecx, ecx

    mov esi, dword[size]   
    imul esi, dword[size]    ; количество на считывание

    
.get_array:
    lea edx, [array+ecx*4]
    push ecx
    push edx
    push fmt
    call scanf
    add esp, 8
    pop ecx
    
    inc ecx
    cmp ecx, esi
    jne .get_array
    
    
;текущий след  
    finit
    fld qword[zero]
    xor ecx, ecx
    
   
.cur_t:
    mov edx,dword[size]
    inc edx
    imul edx, ecx
    mov edx, dword[array+4*edx]
    
    mov eax, edx
    cdq
    mov dword[x+4], eax
    mov dword[x], edx
    
    fld qword[x]
    faddp 
    
    inc ecx
    
    cmp dword[size], ecx
    jne .cur_t
    
    fstp qword[cur_tr]
    
;сравниваем текущий со следом предполагаемого результата
    mov eax, dword[cur_tr]
    ;PRINT_DEC 4, eax
    ;PRINT_DEC 4, max_tr
    cmp eax, dword[max_tr]
    jbe .less
    ;PRINT_CHAR 'c'
    ;NEWLINE
    ;обновляем макс
    mov dword[max_tr], eax
    ;обновляем матрицу
    xor ecx, ecx
    mov esi, dword[size]   
    imul esi, dword[size]    ; количество на копирование   
.copy_array:
    mov edx, dword[array+ecx*4]
    mov dword[res++ecx*4], edx
        
    inc ecx
    cmp ecx, esi
    jne .copy_array  
    ;обновляем размер 
    mov eax, [size]
    mov [res_size], eax 
  
.less:  
    mov dword[cur_tr], 0      
    dec dword[n]
    cmp dword[n], 0
    jne .for  
    
;печатаем результат 
    mov esi,0
    mov edi, 0   
.for_:
    mov edx, esi
    imul edx, dword[res_size]
    add edx, edi
    
    mov edx, [res+edx*4]
    
    push edx
    push fmt
    call printf
    add esp, 8




    inc edi
    cmp edi, dword[res_size]
    jne .for_
    push new_l
    call printf
    add esp, 4
    
    xor edi, edi    

    inc esi
    cmp esi, dword[res_size]
    jne .for_
        
    
    
.end:    
    
    



    mov esp, ebp
    pop ebp    
    xor eax, eax
    ret