.286
.MODEL SMALL
.DATA
    STRING DB 5 DUP(20H),'$'
.STACK ; 默认堆栈段的长度为 1024
.CODE
FAC PROC NEAR ; 求阶层函数，入口参数AL(存放N),出口参数DX(存放结果）
    MOV AH,0   ;初始化参数
    MOV DX,0
    CMP AL,1 ; 1是出口条件,如果满足跳出
    JZ OUTP
    PUSH AX  ; 把 N的值保存在堆栈中 DX的值应该不需要保存
    DEC AL; AL减1
    CALL NEAR PTR FAC ; 递归调用 计算 (N-1)! 结果存放在DX中
    POP AX;    获取之前保存的AX
    MUL DX;       计算结果保存在 DX:AX中
    MOV DX,AX ;   把计算结果保存在DX里
    RET
OUTP: MOV DX,1
    RET
FAC ENDP
PRINT PROC NEAR ; 入口参数DX，把DX中的值转为为十进制数打印在屏幕上
    MOV AX,@DATA
    MOV DS,AX
    MOV DI,4
    MOV CX,10; 每次除以10
    MOV AX,DX ;  把DX中的值移到AX里，因为之后要做除法，DX是入口参数
    AGAIN: MOV DX,0   ;装入被除数NUM
           DIV CX ; 取最低位
           ADD DL,30H;  余数为最低位，余数一定小于10取DL，且转化为ASSIC码
           MOV STRING[DI],DL ; 把余数保存下来
           DEC DI;  DI -- 
           CMP AX,0 ; 判断商是否为0
          JNZ AGAIN ;  不为0返回开头重新执行      
    MOV AH,09H   ;打印STRING的内容
	ADD DI,1
    LEA DX,STRING
	ADD DX,DI
    INT 21H
    RET
PRINT ENDP
MAIN PROC NEAR;   主程序
    MOV AH,01H
    INT 21H
    MOV BL,AL
    MOV AH,2  ;换行
    MOV DL,0AH
    INT 21H 
    MOV DL,0DH
    INT 21H 
    MOV AL,BL
    AND AL, 0FH;  将ASCII码转化为数字,屏蔽高四位
    CALL NEAR PTR FAC ; 计算机阶层，结果放在DX中
    MOV AX,DX
    CALL NEAR PTR PRINT ; 打印到屏幕上
    RET
MAIN ENDP
START:CALL NEAR PTR MAIN  ;主程序调用
      MOV AH,4CH
      INT 21H
END START
