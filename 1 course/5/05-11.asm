%include "io.inc"
section .data
    filename_from   db `/home/angelika/Desktop/contests/5/input.txt`, 0
    filename_to   db `/home/angelika/Desktop/contests/5/output.txt`, 0
    read_mode       db `r`,0
    write_mode      db `w`,0 
    fmt db `%d %d`, 0
    fmt_1 db `%d `, 0
section .bss
    n resd 1
    m resd 1
    a resd 1
    b resd 1   
    arr resd 1 
    head resd 1
    fp resd 1
    
extern fopen
extern fscanf   
extern malloc
extern fclose
extern fprintf
     
section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp
    and esp, 0xfffffff0
    
;открыли файл     
    sub esp, 8
    push read_mode      
    push filename_from           
    call fopen     
    add esp, 16
    
    mov dword[fp], eax    
;считываем n m    
    push m
    push n
    push fmt
    push dword[fp]
    call fscanf
    add esp, 16

;массив указателей         
    mov ecx, dword[n]
    inc ecx
    imul ecx, 4
    
    sub esp, 12
    push ecx
    call malloc
    add esp, 16
    
    mov dword[arr], eax
    
;первый элемент
    sub esp, 12
    push 1
    call create_new_node
    add esp, 16  
                 
    mov edi, dword[arr]
    mov dword[edi+4], eax
    
    mov dword[head], eax 
    
    cmp dword[n], 1
    je .end
           
    mov ecx, 2
    
.for: 
    mov edi, dword[arr]

    sub esp, 8
    push ecx   
    push ecx
    call create_new_node
    add esp, 4
    pop ecx
    add esp, 8

    lea esi, [edi+(ecx-1)*4] ; указатель на а[i-1]
    lea edi, [edi+ecx*4]      ; указатель на а[i]
 
    mov dword[edi], eax   ;a[i]=eax

    mov ebx, dword[esi]  ;ebx=а[i-1]
    mov dword[eax+4], ebx  ;prev=а[i-1]
    mov dword[ebx+8], eax
    
    mov eax, dword[head]
    mov eax, dword[eax]
      
    inc ecx
    cmp ecx, dword[n]
    jle .for
    
    cmp dword[m], 0
    je .end


    xor ecx, ecx    
.for_a_b:
    push ecx
    sub esp, 12
    push b
    push a
    push fmt
    push dword[fp]
    call fscanf
    add esp, 28
    pop ecx
    
    push ecx
    sub esp, 12
    push dword[arr]
    push dword[b]
    push dword[a]
    push dword[head]
    call shift
    add esp, 28
    pop ecx
    
    mov dword[head], eax
    
    inc ecx
    cmp ecx, dword[m]
    jne .for_a_b    
          
.end:  
    sub esp, 8  
    push write_mode      
    push filename_to           
    call fopen     
    add esp, 16
    
    mov dword[fp], eax

;печать листа 
    sub esp, 8 
    push eax
    push dword[head]
    call print_list
    add esp, 16

    sub esp, 12
    push dword[fp]
    call fclose
    add esp, 16

    mov esp, ebp
    pop ebp
    
    xor eax, eax
    ret

shift:
    push ebp
    mov ebp, esp
    push ebx
    push edi
    push esi

;                          dword[ebp+8] +12    +16         +20
;struct Node* shift(struct Node *head, int a, int b, struct Node **arr) {
;    if (head->value == a) {
;        return head;
;    }


    mov esi, dword[ebp+8]
    mov esi, dword[esi]
    cmp esi, dword[ebp+12] 
    jne .not_head
    mov eax, dword[ebp+8]
    jmp .sh_end
    
.not_head:   

;    esi := arr[a];
;    eax = esi;
;    edi = arr[b];
    mov esi, dword[ebp+20]
    mov edi, dword[ebp+12]
    lea esi, [esi+4*edi]
    mov esi, dword[esi]           ;esi = arr[a]
    
    mov eax, esi
    
    mov edi, dword[ebp+20]
    mov edx, dword[ebp+16]
    lea edi, [edi+4*edx]
    mov edi, dword[edi]           ;edi = arr[b]
    
;    if (edi->next != NULL) {
    cmp dword[edi+8], 0
    je .else
    push esi
    
;   cur1->prev->next = cur2->next;    
    mov ebx, dword[edi+8]
    mov esi, dword[esi+4]
    mov dword[esi+8], ebx
    
    pop esi

;        cur2->next->prev = cur1->prev;         
    push edi
    mov ebx, dword[esi+4]
    mov edi, dword[edi+8]
    mov dword[edi+4], ebx
    pop edi
    
    jmp .if_end
.else:
;        cur1->prev->next = NULL;
    push esi  

    mov esi, dword[esi+4]
    mov dword[esi+8], 0
    
    pop esi

.if_end:
;    cur2->next = head;
    mov ebx, dword[ebp+8]
    mov dword[edi+8], ebx
;    head->prev = cur2;
    mov dword[ebx+4], edi

;    cur1->prev = NULL;
    mov dword[esi+4], 0

.sh_end:
    pop esi
    pop edi
    pop ebx
    mov esp, ebp
    pop ebp

    ret

print_list:
    push ebp
    mov ebp, esp
    sub esp, 8

    mov ecx, dword[ebp+8]
.print:   
    mov eax, dword[ecx]   
    
    push ecx
        
    push eax
    push fmt_1
    push dword[ebp+12]
    call fprintf
    add esp, 12
    
    pop ecx
    
    mov ecx, dword[ecx+8]
    cmp ecx, 0
    jne .print
        
    mov esp, ebp
    pop ebp
    
    ret  

create_new_node:
    push ebp
    mov ebp, esp
    push esi
    push edi
        
    sub esp, 12    
    push 12
    call malloc
    add esp, 16
    
    mov esi, dword[ebp+8]    
    mov dword[eax], esi
    mov dword[eax+4], 0
    mov dword[eax+8], 0
    
    pop edi
    pop esi    
    mov esp, ebp
    pop ebp
    
    ret   