@256
D=A
@SP
M=D
//push constant 7
@7
D=A
@SP
A=M
M=D
@SP
M=M+1
//call FibonacciElement.fibonacci 1
//PUSH RETURN ADDRESS (using line n)
@$10
D=A
@SP
A=M
M=D
@SP
M=M+1
//PUSH LCL
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
//PUSH ARG
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
//PUSH THIS
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
//PUSH THAT
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
//ARG=S-n-5
@SP
D=M
@5
D=D-A
@1
D=D-A
@ARG
M=D
//LCL=SP
@SP
D=M
@LCL
M=D
//GOTO F
@FibonacciElement.fibonacci
0;JMP
//(RETURN ADDRESS)
($10)
//label WHILE
(WHILE)
//goto WHILE
@WHILE
0;JMP
//function FibonacciElement.fibonacci 0
(FibonacciElement.fibonacci)

//push argument 0
@2
D=M
@0
A=A+D
D=M
@SP
A=M
M=D
@SP
M=M+1
//push constant 2
@2
D=A
@SP
A=M
M=D
@SP
M=M+1
//lt
@SP
A=M-1
A=A-1
D=M
@SP
A=M
A=A-1
D=D-M
@IF17
D;JLT
D=0
@END17
0;JMP
(IF17)
D=-1
(END17)
@SP  
A=M  
A=A-1  
A=A-1  
M=D  
@SP  
M=M-1 
//if-goto IF_TRUE
@SP
AM=M-1
D=M
@IF_TRUE
D;JNE
//goto IF_FALSE
@IF_FALSE
0;JMP
//label IF_TRUE
(IF_TRUE)
//push argument 0        
@2
D=M
@0
A=A+D
D=M
@SP
A=M
M=D
@SP
M=M+1
//return
//FRAME = LCL
@LCL
D=M
@FRAME
M=D
//RET = *(FRAME-5)
@5
D=A
@FRAME
A=M-D
D=M
@RET
M=D

//*ARG=pop()
@ARG
D=M
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
//SP = ARG+1
@ARG
D=M+1
@SP
M=D
//THAT = *(FRAME-1)
@FRAME
D=M
@1
A=D-A
D=M
@THAT
M=D
//THIS = *(FRAME-2)
@FRAME
D=M
@2
A=D-A
D=M
@THIS
M=D
//ARG = *(FRAME-3)
@FRAME
D=M
@3
A=D-A
D=M
@ARG
M=D
//LCL = *(FRAME-4)
@FRAME
D=M
@4
A=D-A
D=M
@LCL
M=D
//goto RET
@RET
A=M
0;JMP
//label IF_FALSE
(IF_FALSE)
//push argument 0
@2
D=M
@0
A=A+D
D=M
@SP
A=M
M=D
@SP
M=M+1
//push constant 2
@2
D=A
@SP
A=M
M=D
@SP
M=M+1
//sub
@SP
A=M-1
A=A-1
D=M
@SP
A=M
A=A-1
D=D-M
@SP  
A=M  
A=A-1  
A=A-1  
M=D  
@SP  
M=M-1 
//call FibonacciElement.fibonacci 1
//PUSH RETURN ADDRESS (using line n)
@$27
D=A
@SP
A=M
M=D
@SP
M=M+1
//PUSH LCL
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
//PUSH ARG
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
//PUSH THIS
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
//PUSH THAT
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
//ARG=S-n-5
@SP
D=M
@5
D=D-A
@1
D=D-A
@ARG
M=D
//LCL=SP
@SP
D=M
@LCL
M=D
//GOTO F
@FibonacciElement.fibonacci
0;JMP
//(RETURN ADDRESS)
($27)
//push argument 0
@2
D=M
@0
A=A+D
D=M
@SP
A=M
M=D
@SP
M=M+1
//push constant 1
@1
D=A
@SP
A=M
M=D
@SP
M=M+1
//sub
@SP
A=M-1
A=A-1
D=M
@SP
A=M
A=A-1
D=D-M
@SP  
A=M  
A=A-1  
A=A-1  
M=D  
@SP  
M=M-1 
//call FibonacciElement.fibonacci 1
//PUSH RETURN ADDRESS (using line n)
@$31
D=A
@SP
A=M
M=D
@SP
M=M+1
//PUSH LCL
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
//PUSH ARG
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
//PUSH THIS
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
//PUSH THAT
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
//ARG=S-n-5
@SP
D=M
@5
D=D-A
@1
D=D-A
@ARG
M=D
//LCL=SP
@SP
D=M
@LCL
M=D
//GOTO F
@FibonacciElement.fibonacci
0;JMP
//(RETURN ADDRESS)
($31)
//add
@SP
A=M-1
A=A-1
D=M
@SP
A=M
A=A-1
D=D+M
@SP  
A=M  
A=A-1  
A=A-1  
M=D  
@SP  
M=M-1 
//return
//FRAME = LCL
@LCL
D=M
@FRAME
M=D
//RET = *(FRAME-5)
@5
D=A
@FRAME
A=M-D
D=M
@RET
M=D

//*ARG=pop()
@ARG
D=M
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
//SP = ARG+1
@ARG
D=M+1
@SP
M=D
//THAT = *(FRAME-1)
@FRAME
D=M
@1
A=D-A
D=M
@THAT
M=D
//THIS = *(FRAME-2)
@FRAME
D=M
@2
A=D-A
D=M
@THIS
M=D
//ARG = *(FRAME-3)
@FRAME
D=M
@3
A=D-A
D=M
@ARG
M=D
//LCL = *(FRAME-4)
@FRAME
D=M
@4
A=D-A
D=M
@LCL
M=D
//goto RET
@RET
A=M
0;JMP
