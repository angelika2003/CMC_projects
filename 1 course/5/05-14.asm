%include "io.inc"
section .rodata
    filename_from   db `input.txt`, 0
    filename_to   db `output.txt`, 0
    read_mode       db `r`,0
    write_mode      db `w`,0 
    fmt db `%d `, 0
        
section .bss   
    x resd 1
    prev_node resd 1
    root resd 1
    len resd 1
    
extern fopen
extern fscanf
extern fprintf
extern fclose
extern malloc

section .text  
global CMAIN
CMAIN: 
    push ebp
    mov ebp, esp
    and esp, 0xfffffff0
  
    sub esp, 8  
    push read_mode      
    push filename_from           
    call fopen     
    add esp, 16
    
    mov esi, eax
    
;первый node
    sub esp, 4
    push x
    push fmt
    push esi
    call fscanf
    add esp, 16
    
    sub esp, 12
    push dword[x]
    call create_new_node
    add esp, 16    
    inc dword[len]
    
    mov dword[root], eax
    mov edi, eax
            
.get_list: 
    sub esp, 4                                
    push x
    push fmt
    push esi
    call fscanf
    add esp, 16       
    
    cmp eax, -1
    je .end
    
    sub esp, 12
    push dword[x]
    call create_new_node
    add esp, 16
    inc dword[len]
        
    mov dword[edi+4], eax
    mov edi, eax    

    jmp .get_list    
.end:       
;сортировка
    sub esp, 8
    push dword[len]
    push dword[root]
    call list_sort
    add esp, 16
        
;открываем для записи   
    sub esp, 8 
    push write_mode      
    push filename_to            
    call fopen       
    add esp, 16
                             
    mov esi, eax  
    mov edi, dword[root]                                                                   
    
.print_list: 
    sub esp, 4                                                                                                                                                                                                                                                                                               
    push dword[edi]
    push fmt
    push esi                 
    call fprintf                                                                                                                                                 
    add esp, 16 
    mov ecx, dword[edi]

    mov edi, dword[edi+4]
    cmp edi, 0
    jne .print_list 

    sub esp, 12                                                                                                                                    
    push esi
    call fclose
    add esp, 16
       
    mov esp, ebp
    pop ebp
    
    xor eax, eax
    ret
                        
create_new_node:
    push ebp
    mov ebp, esp
    push esi
    push edi
       
    sub esp, 12    
    push 8
    call malloc
    add esp, 16
    mov esi, dword[ebp+8]    
    mov dword[eax], esi
    mov dword[eax+4], 0
    
    pop edi
    pop esi
    
    mov esp, ebp
    pop ebp
    
    ret
    
    
list_sort:
    push ebp 
    mov ebp, esp
    push ebx
    push esi
    push edi
    
    mov ecx, dword[ebp+12]
    cmp ecx, 1
    je .end
.for:
    mov eax, dword[ebp+8]

.while:        
    mov esi, dword[eax]
    
    mov ebx, dword[eax+4]
    mov edi, dword[ebx]
    
    cmp esi, edi
    jle .wo_swap
    
    mov dword[ebx], esi
    mov dword[eax], edi

.wo_swap:
    mov eax, ebx
    
    cmp dword[eax+4], 0
    jne .while

    dec ecx
    cmp ecx, 0
    jg .for    
    
.end:    
    pop edi
    pop esi
    pop ebx 
    mov esp, ebp
    pop ebp
    ret    
    
            
    
    
    
    
    
    
    
    