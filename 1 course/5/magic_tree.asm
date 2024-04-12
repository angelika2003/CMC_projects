%include "io.inc"

extern malloc
section .bss
    root resd 1
    x resd 1
    n resd 1
    p resd 1
    number resd 1

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp
    
    GET_DEC 4, n
    
    GET_DEC 4, x
    push dword[x]
    call create_new_node
    add esp, 4
    
    dec dword[n]
    
    mov [root], eax
    
.while: 
    GET_DEC 4, x
    
    push dword[x]
    push dword[root]
    call add_new_node
    add esp, 8
    
    dec dword[n]
    cmp dword[n], 0
    jne .while

    push dword[root]
    call print_tree
    add esp, 4
    
    push 5
    push dword[root]
    call find
    add esp, 8
    NEWLINE
    PRINT_DEC 4, eax

    mov esp, ebp
    pop ebp
    
    xor eax, eax
    ret
    
;number +20
;fp    +16
find:
    push edx
    push ebx
    push ebp
    mov ebp, esp
    
    mov edx, dword[ebp+20]
    mov ebx, dword[ebp+16]
    
    cmp ebx, 0
    je .end_no
    
    cmp dword[ebx+4], edx
    je .end_yes
    
    cmp edx, dword[ebx+4]  ;;
    jl .find_left

    push dword[ebp+20]
    push dword[ebx+8]
    call find
    add esp, 8
    jmp .endd
   
.find_left:
    push dword[ebp+20]
    push dword[ebx]
    call find
    add esp, 8
    jmp .endd
             
.end_no:
    xor eax, eax
    jmp .endd    
    
.end_yes:
    mov eax, 1
.endd:    
    mov esp, ebp
    pop ebp
    pop ebx
    pop edx
    
    ret
    
    

; fp +8
print_tree:
    push ebp
    mov ebp, esp
    
    cmp dword[ebp+8], 0
    je .end1
    
    mov ebx, dword[ebp+8]
    
    push ebx
    push dword[ebx]
    call print_tree
    add esp, 4
    pop ebx
    
    PRINT_DEC 4, [ebx+4]
    PRINT_CHAR ' '
   
    push dword[ebx+8]
    call print_tree
    add esp, 4 
    
.end1:   
    mov esp, ebp
    pop ebp
    ret
    
                                                                                                         
                                                                                                                                                                                                                                                                                                                   
    
;фрейм:
;    число     +12
;    указатель  +8
add_new_node:
    push ebp
    mov ebp, esp
    
    mov ebx, [ebp+8]
    mov ecx, [ebx+4]
    cmp [ebp+12], ecx
    jl .left
    
    cmp dword[ebx+8], 0
    jne .not_null_right
    push dword[ebp+12]
    call create_new_node
    add esp, 4
    mov [ebx+8], eax
    jmp .end
.not_null_right:  
    push dword[ebp+12]
    push dword[ebx+8]
    call add_new_node
    add esp, 8
    jmp .end                       
.left:       
    cmp dword[ebx], 0
    jne .not_null_left
    push dword[ebp+12]
    call create_new_node
    add esp, 4
    mov [ebx], eax
    jmp .end
.not_null_left:  
    push dword[ebp+12]
    push dword[ebx]
    call add_new_node
    add esp, 8
    jmp .end                  

.end:         
    mov esp, ebp
    pop ebp                    
     
     
     
     
create_new_node:
    push ebp
    mov ebp, esp
    
    push 16
    call malloc
    mov ecx,[ebp+8] 
    mov [eax+4], ecx
         
    mov esp, ebp
    pop ebp
    ret    