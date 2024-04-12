section .data
    const1 dq 2
    
    const2 dq -1
    
    const3_1 dq 1
    const3_2 dq -2
    const3_3 dq 3

section .text
   
global f1     
f1: ; e^x + 2
    push ebp
    mov ebp, esp
    
    finit
    
    fld qword[ebp + 8]
    fldl2e
    fmulp
    
    fld1
    fld st1
    fprem
    f2xm1
    faddp
    fscale
    fstp st1
    
    fild qword[const1]
    faddp
    
    mov esp, ebp
    pop ebp
    ret 
    
global f2
f2: ; -1/x
    push ebp
    mov ebp, esp
    
    finit
    
    fild qword [const2]
    fld qword [ebp + 8]
    fdivp
    
    mov esp, ebp
    pop ebp
    ret
 
global f3       
f3: ; -2*(x+1)/3
    push ebp
    mov ebp, esp
    
    finit
    
    fild qword [const3_1]
    fld qword [ebp + 8]
    faddp
    
    fild qword [const3_2]
    fmulp
    
    fild qword [const3_3]
    fdivp
    
    mov esp, ebp
    pop ebp
    ret  

global t1    
t1: ; (e^x + 2)' = e^x
    push ebp
    mov ebp, esp
    
    finit
    
    fld qword[ebp + 8]
    fldl2e
    fmulp
    
    fld1
    fld st1
    fprem
    f2xm1
    faddp
    fscale
    fstp st1
    
    mov esp, ebp
    pop ebp
    ret 

global t2
t2: ; (-1/x)' = 1/x^2
    push ebp
    mov ebp, esp
    
    finit
    
    fld1
    fld qword [ebp + 8]
    fld qword [ebp + 8]
    fmulp
    fdivp
    
    mov esp, ebp
    pop ebp
    ret

global t3
t3: ; (-2*(x+1)/3)' = -2/3
    push ebp
    mov ebp, esp
    
    finit
    
    fild qword [const3_2]
    fild qword [const3_3]
    fdivp
    
    mov esp, ebp
    pop ebp
    ret  
