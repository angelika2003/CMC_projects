%include "io.inc"

section .data
    const_2 dd 2
section .bss
    n resd 1
    m resd 1
    a resd 100
    b resd 100
    c resd 100
    

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    push ebp
    mov ebp, esp
    
    GET_DEC 4, n
    
    mov ecx, 0   
.while_input:      
    GET_DEC 4, [a+ecx*4]
    inc ecx
    cmp ecx, dword[n]
    jne .while_input
    
    GET_DEC 4, m
    
    mov ecx, 0    
.while_input1:      
    GET_DEC 4, [b+ecx*4]
    inc ecx
    cmp ecx, dword[m]
    jne .while_input1

    call merge
    
    mov eax, dword[m]
    add dword[n], eax
    
    xor ecx, ecx
.while_print1:
    PRINT_DEC 4, [c+ecx*4]
    PRINT_CHAR ' '
    inc ecx
    cmp ecx, dword[n]
    jne .while_print1    
    
    mov esp, ebp
    pop ebp
    xor eax, eax
    ret
    
merge:
    mov edx, 0
    mov esi, 0
    mov edi, 0

.loop:    
    mov eax, dword[a+esi*4]
    mov ebx, dword[b+edi*4]
    
    
    cmp eax, ebx
    jge .b
    
    mov dword[c+edx*4], eax
    inc esi
    inc edx
    cmp esi, dword[n]    
    jne .loop
.for_a:
    mov ebx, dword[b+edi*4]
    mov dword[c+edx*4], ebx
    
    inc edi
    inc edx
    cmp edi, dword[m]
    jne .for_a   
    
    jmp .end_merge
.b:   
    mov dword[c+edx*4], ebx
    inc edi
    inc edx 
    cmp edi, dword[m]    
    jne .loop
    
.for_b:
    mov eax, dword[a+esi*4]
    mov dword[c+edx*4], eax
    
    inc esi
    inc edx
   cmp esi, dword[n]
   jne .for_b   
.end_merge:    

    ret    
    
    
    
    
shift:
    dec dword[n]
    mov eax, dword[a]
    mov esi, 0
.for_shift:
    mov ebx, dword[a+esi*4+ 4]
    mov dword[a+esi*4], ebx
    
    inc esi
    cmp esi, dword[n]
    jl .for_shift
    
    mov dword[a+esi*4], eax
    
    inc dword[n]

    ret
        
reverse:
    mov eax, dword[n]
    xor edx, edx
    div dword[const_2]
    mov ecx, eax
    add ecx, edx
    dec ecx
    
    
    mov esi, 0
    mov edi, dword[n]
    dec edi
    
.for:
    PRINT_DEC 4, esi
    PRINT_DEC 4, edi
    NEWLINE
    mov eax, dword[a+esi*4]
    mov ebx, dword[a+edi*4]
    
    mov dword[a+edi*4], eax
    mov dword[a+esi*4], ebx

    dec edi
    inc esi
    cmp esi, ecx
    jle .for    

    ret
      
bubble:
    push ebp
    mov ebp, esp
    
    dec dword[n]
    
    mov esi, 0   
.for_1:   
    mov edi, 0 

.for_2:
    mov eax, dword[a+edi*4]
    mov ebx, dword[a+edi*4 +4]
    PRINT_DEC 4, eax
    PRINT_DEC 4, ebx
    
    cmp eax, ebx
    jle .endd
    PRINT_CHAR 's'
    mov dword[a+edi*4], ebx
    mov dword[a+edi*4 +4], eax
    

.endd:
    NEWLINE
    inc edi
    cmp edi, dword[n]
    jne .for_2

    inc esi
    cmp esi, dword[n]
    jne .for_1
    
    inc dword[n]

    mov esp, ebp
    pop ebp
    ret  
    
select:
    push ebp
    mov ebp, esp
    
    dec dword[n]
    
    
    mov esi, 0   
.for_1:   
    mov edi, esi 
    inc edi

    mov eax, dword[a+esi*4]

.for_2:
    mov ebx, dword[a+edi*4]
    PRINT_DEC 4, esi
    PRINT_DEC 4, edi
    
    cmp eax, ebx
    jle .endd
    PRINT_CHAR 's'
    mov dword[a+esi*4], ebx
    mov dword[a+edi*4], eax
    

.endd:
    NEWLINE
    inc edi
    cmp edi, dword[n]
    jle .for_2

    inc esi
    cmp esi, dword[n]
    jne .for_1
    
    inc dword[n]
    


    mov esp, ebp
    pop ebp
    ret       
      
       
        
         
           