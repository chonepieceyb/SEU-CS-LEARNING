.286
.MODEL SMALL
.DATA
    NUM DW 6553
    STRING DB 5 DUP(20H),'$'
.STACK
.CODE
START: MOV AX,@DATA
       MOV DS,AX
       MOV DI,4
       MOV AX,NUM 
       MOV CX,10; 每次除以10
AGAIN: MOV DX,0   ;装入被除数NUM
       DIV CX ; 取最低位
       ADD DL,30H;  余数为最低位，余数一定小于10取DL，且转化为ASSIC码
       MOV STRING[DI],DL ; 把余数保存下来
       DEC DI;  DI -- 
       CMP AX,0 ; 判断商是否为0
       JNZ AGAIN ;  不为0返回开头重新执行      
PRINT: MOV AH,09H   ;打印STRING的内容
	   ADD DI ,1 ;
       LEA DX,STRING
	   ADD DX,DI 
       INT 21H
       MOV AH,4CH
       INT 21H  ;   返回DOS
END START