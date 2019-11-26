.286
.MODEL SMALL
.DATA
    STRING DB 'stringstrin$'
	OUTPUT DB 5 DUP(20H),'$'
.STACK
.CODE
START: MOV AX,@DATA
       MOV DS,AX
       MOV BX,-1
AGAIN: INC BX
       MOV CX ,65535; 字符串的最大长度，防止越界溢出
       CMP STRING[BX],'$'
       LOOPNZ AGAIN;  和'$'号不同继续
	
DONE:  MOV DX,BX
	   CALL PRINT
       MOV AH,4CH ;完成的时候 BX的下标是 '$'的下标，所以BX就是字符串的长度(排除$)
       INT 21H
PRINT PROC NEAR ; 入口参数DX，把DX中的值转为为十进制数打印在屏幕上
    MOV AX,@DATA
    MOV DS,AX
    MOV DI,4
    MOV CX,10; 每次除以10
    MOV AX,DX ;  把DX中的值移到AX里，因为之后要做除法，DX是入口参数
    PRINTAGAIN: MOV DX,0   ;装入被除数NUM
           DIV CX ; 取最低位
           ADD DL,30H;  余数为最低位，余数一定小于10取DL，且转化为ASSIC码
           MOV OUTPUT[DI],DL ; 把余数保存下来
           DEC DI;  DI -- 
           CMP AX,0 ; 判断商是否为0
          JNZ PRINTAGAIN ;  不为0返回开头重新执行      
    MOV AH,09H   ;打印STRING的内容
	ADD DI,1
    LEA DX,OUTPUT
	ADD DX,DI
    INT 21H
    RET
PRINT ENDP	   
END START