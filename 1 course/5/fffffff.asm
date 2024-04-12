;закрыть файлы
;free

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
    root resd 1
    x resd 1
    n resd 1
    p resd 1
    number resd 1
    fp resd 1
    fp_to resd 1
    
section .text
    filename_from db `input.txt`, 0
    filename_to   db `output.txt`, 0
    read_mode db `r`, 0
    write_mode db 'w', 0
    fmt db `%s %u`, 0
    s db `%s`, 0   
    fmt_d db `%d\n`, 0
    fmt_u db `%u\n`, 0
    fmt_no db `-1\n`, 0
    for_find db 'asdf',0 

section .text
global CMAIN
CMAIN:

    push ebp
    mov ebp, esp
    
    push read_mode
    push filename_from
    call fopen
    add esp, 8
    
    mov dword[fp], eax
 
    push n
    push fmt_d
    push dword[fp]
    call fscanf
    add esp, 12
    
    
    
;первый элемент   
    push 102
    call malloc
    add esp, 4
    
    mov dword[p], eax

; fp %s %u eax x
    push x        
    push eax
    push fmt
    push dword[fp]
    call fscanf
    add esp, 16

    
    push dword[x]
    push dword[p]
    call create_new_node
    add esp, 8
    
    dec dword[n]
    
    mov [root], eax
    
;     <-  | ptr on str | ->  | number
;     0        +4        +8       +12
    cmp dword[n], 0
    je .wo_while
    
.while:
    push 102
    call malloc
    add esp, 4
    
    mov dword[p], eax
    
    push x        
    push eax
    push fmt
    push dword[fp]
    call fscanf
    add esp, 16
    
    push dword[x]
    push dword[p]
    push dword[root]
    call add_new_node
    add esp, 8
    
    dec dword[n]
    cmp dword[n], 0
    jne .while
.wo_while:
;    push dword[root]
;    call print_tree
;    add esp, 4
;    NEWLINE
    
    push n
    push fmt_d
    push dword[fp]
    call fscanf
    add esp, 12
    
    
;открываем на запись     
    push write_mode
    push filename_to
    call fopen
    add esp, 8
    
    mov dword[fp_to], eax

.while_for_find:  
    push 102
    call malloc
    add esp, 4
    
    mov dword[p], eax
    
    push eax
    push s
    push dword[fp]
    call fscanf
    add esp, 12  
   
    push dword[p]
    push dword[root]
    call find
    add esp, 8
    
       
    dec dword[n]
    cmp dword[n], 0
    jne .while_for_find    
    
    push dword[fp_to]
    call fclose
    add esp, 4

    mov esp, ebp
    pop ebp
    
    xor eax, eax
    ret


;ptr on str +20
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
    
    push dword[ebx+4]
    push edx   ;new
    call strcmp
    add esp, 8
    cmp eax, 0
    je .end_yes
    
    cmp eax, 0     ;;
    jl .find_left
    
;    PRINT_CHAR 'r'

    push dword[ebp+20]
    push dword[ebx+8]
    call find
    add esp, 8
    jmp .endd
   
.find_left:
;    PRINT_CHAR 'l'
    push dword[ebp+20]
    push dword[ebx]
    call find
    add esp, 8
    jmp .endd
             
.end_no:
    push fmt_no
    push dword[fp_to]
    call fprintf
    add esp, 8
    jmp .endd    
    
.end_yes:
    push dword[ebx+12]
    push fmt_u
    push dword[fp_to]
    call fprintf
    add esp, 12

;    PRINT_CHAR 'f'
;    PRINT_UDEC 4, eax
.endd:    
    mov esp, ebp
    pop ebp
    pop ebx
    pop edx
    
    ret
    
    







;+16    push dword[x]
;+12    push dword[p]
;+8     push dword[root]
add_new_node:
    push ebp
    mov ebp, esp
    
    mov ebx, [ebp+8]
    mov ecx, [ebx+4]
    
    push ecx      ;old
    push dword[ebp+12] ;new
    call strcmp  ;new or old
    add esp, 8
    
    cmp eax, 0
    je .end
    
    cmp eax, 0
    jl .left
    
    cmp dword[ebx+8], 0
    jne .not_null_right
    
    push dword[ebp+16]
    push dword[ebp+12]
    call create_new_node
    add esp, 8
    mov [ebx+8], eax
    jmp .end
.not_null_right:  

    push dword[ebp+16]
    push dword[ebp+12]
    push dword[ebx+8]
    call add_new_node
    add esp, 12
    jmp .end                       
.left:       
    cmp dword[ebx], 0
    jne .not_null_left
    push dword[ebp+16]
    push dword[ebp+12]
    call create_new_node
    add esp, 8
    mov [ebx], eax
    jmp .end
.not_null_left:  
    push dword[ebp+16]
    push dword[ebp+12]
    push dword[ebx]
    call add_new_node
    add esp, 12
    jmp .end                  

.end:         
    mov esp, ebp
    pop ebp    
    ret     
        
            
                
                        
;+12 number
;+8 ptr on str    
create_new_node:
    push ebp
    mov ebp, esp
    
    push 16
    call malloc
    mov ecx,[ebp+8] 
    mov [eax+4], ecx
    
    mov ecx, [ebp+12]
    mov [eax+12], ecx
         
    mov esp, ebp
    pop ebp
    ret    