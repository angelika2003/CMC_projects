section .rodata
    filename_from   db `/home/angelika/Desktop/5/input.txt`, 0
    filename_to   db `/home/angelika/Desktop/5/output.txt`, 0
    read_mode       db `r`,0
    write_mode      db `w`,0 
    fmt db `%d `, 0
        
section .bss   
    x resd 1
    prev_node resd 1
    root resd 1
    

extern fopen
extern fscanf
extern fprintf
extern fclose
extern malloc

section .text  
global main
main:   
    push ebp
    mov ebp, esp

;открыли и рады    
    push read_mode      
    push filename_from           
    call fopen     
    add esp, 8
    
    mov esi, eax
    
;первый node
    push x
    push fmt
    push esi
    call fscanf
    add esp, 12 
    
    push dword[x]
    call create_new_node
    add esp, 4    
    
    mov dword[root], eax
    mov edi, eax
    
        
.get_list:                                 
    push x
    push fmt
    push esi
    call fscanf
    add esp, 12       
    
    cmp eax, -1
    je .end
    
    push dword[x]
    call create_new_node
    add esp, 4
    
    mov dword[edi+4], eax
    mov edi, eax    

    jmp .get_list
    
.end:       

    
           

;открываем для записи    
    push write_mode      
    push filename_to            
    call fopen       
    add esp, 8
                             
    mov esi, eax  
    mov edi, dword[root]                                                                   
    
.print_list:                                                                                                                                                                                                                                                                                                
    push dword[edi]
    push fmt
    push esi                 
    call fprintf                                                                                                                                                 
    add esp, 12 

    mov edi, dword[edi+4]
    cmp edi, 0
    jne .print_list 

;закрыли и рады                                                                   
    push esi
    call fclose
    add esp, 4
       
    mov esp, ebp
    pop ebp
    
    xor eax, eax
    ret
    
    
    
    
create_new_node:
    push esi
    push edi
    push ebp
    mov ebp, esp
    
    push 8
    call malloc
    add esp, 4
    mov esi, dword[ebp+8]    
    mov dword[eax], esi
    mov dword[eax+4], 0
    
    mov esp, ebp
    pop ebp
    pop edi
    pop esi
    
    ret
    
    
    
    
    
    