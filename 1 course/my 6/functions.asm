section .data
    fmt_f db `%lf`, 0
    n_neg1 dq -1.0
    n_neg2 dq -2.0
    n_2 dq 2.0
    n_6 dq 6.0
    n_14 dq 14.0
    
section .text

global f1
global f2
global f3
global df1
global df2
global df3

f1:  ; ln(x)
    push ebp
    mov ebp, esp
    
    finit
    fldln2
    fld qword[ebp+8]
    fyl2x    ; log2(x)*ln2=lnx
                     
    mov esp, ebp
    pop ebp
    ret 
                
df1:  ; 1 / x
    push ebp
    mov ebp, esp
    
    finit
    fld1
    fld qword[ebp+8]
    fdivp
                     
    mov esp, ebp
    pop ebp
    ret     
                                          
   
f2:  ; -2x+14
    push ebp
    mov ebp, esp
    
    finit 
    fld qword[ebp+8]
    fld qword[n_neg2]
    fmulp 
    fld qword[n_14]
    faddp
          
    mov esp, ebp
    pop ebp
    ret   
    
df2:  ; -2     
    push ebp
    mov ebp, esp
    
    finit 
    fld qword[n_neg2]
          
    mov esp, ebp
    pop ebp
    ret          
    
f3:  ;1 / (2 − x) + 6 
    push ebp
    mov ebp, esp
    
    finit
    fld qword[n_6]
    fld1
    fld qword[n_2]
    fld qword[ebp+8]
    fsubp
    fdivp
    faddp

    mov esp, ebp
    pop ebp
    ret
    
df3:  ;1 / (2 − x)^2 
    push ebp
    mov ebp, esp
    
    finit
    fld1
    fld qword[n_2]
    fld qword[ebp+8]
    fsubp
    fld qword[n_2]
    fld qword[ebp+8]
    fsubp
    fmulp
    fdivp

    mov esp, ebp
    pop ebp
    ret 