%include "io.inc"

extern scanf
extern printf
extern malloc
extern free

SIZE_OF_NODE EQU 8
    
section .data
    fmt db '%d ', 0
    
section .bss
    root resd 1
    cur resd 1
    x resd 1

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp
    
;first 
    push x
    push fmt
    call scanf
    add esp, 8
    
    push dword[x]
    call create_new_node
    add esp, 4 
    
    mov dword[root], eax

.input_while:
    push x
    push fmt
    call scanf
    add esp, 8
    
    cmp dword[x], 0
    je .end_input
    
    push dword[x]
    call create_new_node
    add esp, 4
    
    push eax
    call add_back
    add esp, 4
    
    jmp .input_while
      
.end_input: 
    push dword[root]
    call reverse
    add esp, 4
    
    mov dword[root], eax
        
    push dword[root]
    call print_list
    add esp, 4 
    
    
    mov esp, ebp
    pop ebp
    xor eax, eax
    ret

;**********************************************************************

;head   +8    /////////////////////////////// 
reverse:
    push ebp
    mov ebp, esp
    
    mov esi, 0               ;prev
    mov eax, dword[ebp+8]    ;cur
    
.while_r:
    mov ebx, dword[eax+4]      ;save
    mov dword[eax+4], esi
    
    mov esi, eax               ; next
    mov eax, ebx               ; next 
    
    cmp eax, 0
    jne .while_r
    
    mov eax, esi         ; new head
    
    mov esp, ebp
    pop ebp
    ret    

    
        
                
;head +8///////////////////////////////////////////   
print_list:
    push ebp
    mov ebp, esp
    
    mov edi, dword[ebp+8]
    
.while_print:    
    cmp edi, 0
    je .end_print
    
    push dword[edi]
    push fmt
    call printf
    add esp, 8
    
    mov edi, dword[edi+4]
    jmp .while_print
            
.end_print:    
    mov esp, ebp
    pop ebp
    ret    

    
            
;ptr on new node  +8////////////////////////////////////    
add_back:
    push ebp
    mov ebp, esp
    
    mov edi, dword[root]

.search_place:    
    cmp dword[edi+4], 0
    je .adding
    mov edi, dword[edi+4]
    jmp .search_place
    
.adding:    
    mov esi, dword[ebp+8]
    mov dword[edi+4], esi
                                                   
    mov esp, ebp
    pop ebp
    ret    



;number +8/////////////////////////////////////////////////     
create_new_node:
    push ebp
    mov ebp, esp
    
    push SIZE_OF_NODE
    call malloc
    add esp, 4
    
    mov ecx, dword[ebp+8]
    mov dword[eax], ecx
    
    mov esp, ebp
    pop ebp
    ret    