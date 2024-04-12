%include "io.inc"

extern malloc
extern scanf
extern strcmp
extern printf 
extern fopen
extern fclose
extern fscanf
extern fprintf
extern free

section .bss
    string resb 102
    root resd 1
    p resd 1
    x resd 1
    n resd 1
    number resd 1
    fp resd 1
    fp_to resd 1
    
section .text
    filename_from db `input.txt`, 0
    filename_to   db `output.txt`, 0
    read_mode db `r`, 0
    write_mode db 'w', 0
    fmt db `%100s %u`, 0
    s db `%100s`, 0   
    fmt_d db `%d\n`, 0
    fmt_u db `%u\n`, 0
    fmt_no db `-1\n`, 0
    for_find db 'asdf',0 

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
    
    mov dword[fp], eax

    sub esp, 4 
    push n
    push fmt_d
    push dword[fp]
    call fscanf
    add esp, 16
    
;первый элемент   
    sub esp, 12
    push 102
    call malloc
    add esp, 16
    
    mov dword[p], eax

; fp %s %u eax x
    push x        
    push eax
    push fmt
    push dword[fp]
    call fscanf
    add esp, 16

    sub esp, 8
    push dword[x]
    push dword[p]
    call create_new_node
    add esp, 16
    
    dec dword[n]
    
    mov [root], eax
    
;     <-  | ptr on str | ->  | number
;     0        +4        +8       +12
    cmp dword[n], 0
    je .wo_while
    
.while:
    sub esp, 12
    push 102    
    call malloc
    add esp, 16
    
    mov dword[p], eax
    
    push x        
    push eax
    push fmt
    push dword[fp]
    call fscanf
    add esp, 16
    
    sub esp, 4
    push dword[x]
    push dword[p]
    push dword[root]
    call add_new_node
    add esp, 16
    
    dec dword[n]
    cmp dword[n], 0
    jne .while
.wo_while:
    sub esp, 4    
    push n
    push fmt_d
    push dword[fp]
    call fscanf
    add esp, 16
        
;открываем на запись 
    sub esp, 8    
    push write_mode
    push filename_to
    call fopen
    add esp, 16
    
    mov dword[fp_to], eax

.while_for_find:          
    sub esp, 4
    push string
    push s
    push dword[fp]
    call fscanf
    add esp, 16  
    
    sub esp, 8
    push string
    push dword[root]
    call find
    add esp, 16
    
    dec dword[n]
    cmp dword[n], 0
    jne .while_for_find   
    
    sub esp, 12
    push dword[root]
    call free_tree
    add esp, 16
    
    sub esp, 12
    push dword[fp_to]
    call fclose
    add esp, 16
    
    sub esp, 12
    push dword[fp]
    call fclose
    add esp, 16

    mov esp, ebp
    pop ebp
    
    xor eax, eax
    ret
    
;root +8   
free_tree:
    push ebp
    mov ebp, esp
    push ebx
    push esi
    push edi
    sub esp, 12
    
    cmp dword[ebp+8], 0
    je .end_free
    
    mov esi, dword[ebp+8]    
    
    sub esp, 12
    push dword[esi]
    call free_tree
    add esp, 16
   
    add esi, 4  
    
    sub esp, 12
    push dword[esi]
    call free
    add esp, 16

    add esi, 4
      
    sub esp, 12  
    push dword[esi]    
    call free_tree
    add esp, 16

    sub esp, 12    
    push dword[ebp+8]
    call free
    add esp, 16   
    
.end_free:
    add esp, 12
    pop edi
    pop esi  
    pop ebx  
    mov esp, ebp
    pop ebp
    ret
        


;ptr on str +12
;fp    +8
find:
    push ebp
    mov ebp, esp
    push ebx
    sub esp, 8
    
    mov ebx, dword[ebp+8]
    
    cmp ebx, 0
    je .end_no
    
    sub esp, 8
    push dword[ebx+4]
    push dword[ebp+12]  ;new
    call strcmp
    add esp, 16
    cmp eax, 0
    je .end_yes
    
    cmp eax, 0     
    jl .find_left
    
    sub esp, 8
    push dword[ebp+12]
    push dword[ebx+8]
    call find
    add esp, 16
    jmp .endd
   
.find_left:
    sub esp, 8
    push dword[ebp+12]
    push dword[ebx]
    call find
    add esp, 16
    jmp .endd
             
.end_no:
    sub esp, 8
    push fmt_no
    push dword[fp_to]
    call fprintf
    add esp, 16
    jmp .endd    
    
.end_yes:
    sub esp, 4
    push dword[ebx+12]
    push fmt_u
    push dword[fp_to]
    call fprintf
    add esp, 16

.endd:   
    add esp, 8
    pop ebx 
    mov esp, ebp
    pop ebp
    
    ret

;+16    push dword[x]
;+12    push dword[p]
;+8     push dword[root]
add_new_node:
    push ebp
    mov ebp, esp
    push ebx
    sub esp, 4
    
    mov ebx, [ebp+8]
    mov ecx, [ebx+4]
    
    sub esp, 8
    push ecx      ;old
    push dword[ebp+12] ;new
    call strcmp  ;new or old
    add esp, 16
    
    cmp eax, 0
    je .end
    
    cmp eax, 0
    jl .left
    
    cmp dword[ebx+8], 0
    jne .not_null_right
    
    sub esp, 8
    push dword[ebp+16]
    push dword[ebp+12]
    call create_new_node
    add esp, 16
    mov [ebx+8], eax
    jmp .end
.not_null_right:  
    sub esp, 4
    push dword[ebp+16]
    push dword[ebp+12]
    push dword[ebx+8]
    call add_new_node
    add esp, 16
    jmp .end                       
.left:       
    cmp dword[ebx], 0
    jne .not_null_left
    sub esp, 8
    push dword[ebp+16]
    push dword[ebp+12]
    call create_new_node
    add esp, 16
    mov [ebx], eax
    jmp .end
.not_null_left: 
    sub esp, 4 
    push dword[ebp+16]
    push dword[ebp+12]
    push dword[ebx]
    call add_new_node
    add esp, 16
    jmp .end                  

.end: 
    add esp, 4
    pop ebx        
    mov esp, ebp
    pop ebp    
    ret     
                            
;+12 number
;+8 ptr on str    
create_new_node:
    push ebp
    mov ebp, esp
    sub esp, 8
    
    
    sub esp, 12
    push 16
    call malloc
    add esp, 16
    
    mov ecx,[ebp+8] 
    mov [eax+4], ecx
    
    mov ecx, [ebp+12]
    mov [eax+12], ecx
         
    mov esp, ebp
    pop ebp
    ret  