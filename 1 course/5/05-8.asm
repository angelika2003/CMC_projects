section .rodata
    filename_from   db `input.txt`, 0
    filename_to   db `output.txt`, 0
    read_mode       db `r`,0
    write_mode      db `w`,0 
    fmt db `%d `, 0
        
section .bss   
    x resd 1000
    fp resd 1
    len resd 1
    pt resd 1
    

extern qsort
extern fopen
extern fscanf
extern fprintf
extern fclose

SIZE_OF_INT equ 4

section .text
comparator:
    push ebp
    mov ebp, esp
    
    push esi
    push edi
    
    mov esi, [ebp + 8]     
    mov edi, [ebp + 12]     
    
    mov esi, dword[esi]   
    mov edi, dword[edi]                   
       
    cmp esi, 0
    jg .a_pos
    jmp .a_neg
.a_pos:    
    cmp edi, 0
    jge .simple_case
    mov eax, 1
    jmp .end1  
.a_neg:
    cmp edi, 0
    jle .simple_case
    mov eax, -1
    jmp .end1
.simple_case:
    mov eax, esi
    sub eax, edi    
.end1:    
    pop edi
    pop esi     
                                        
    mov esp, ebp
    pop ebp
   
    ret
    
global main
main:  
    push ebp
    mov ebp, esp
    and esp, 0xfffffff0
    
    sub esp, 8
    push read_mode      
    push filename_from           
    call fopen     
    add esp, 16
    
    mov dword[fp], eax
    mov dword[pt], x
    
.while:  
    sub esp, 4                
    push dword[pt]
    push fmt
    push dword[fp]
    call fscanf
    add esp, 16      
    
    cmp eax, 0
    jle .end
    inc dword[len]
    add dword[pt], 4
    jmp .while
    
.end:       
    push comparator
    push SIZE_OF_INT
    push dword[len]
    push x        
    call qsort    
    add esp, 16
    
    sub esp, 4              
    push write_mode      
    push filename_to            
    call fopen       
    add esp, 16
                             
    mov esi, eax                                                                    
    
    mov ecx, 0
.l:    
    push ecx                                                                                                                                                                                                                                                                                                
    push dword[x+ecx*4]
    push fmt
    push esi                 
    call fprintf                                                                                                                                                 
    add esp, 12 
    pop ecx
    
    inc ecx
    cmp ecx, dword[len]
    jne .l   
    
    sub esp, 12                                                                                                                             
    push esi
    call fclose
    add esp, 16
       
    mov esp, ebp
    pop ebp
    
    xor eax, eax
    ret