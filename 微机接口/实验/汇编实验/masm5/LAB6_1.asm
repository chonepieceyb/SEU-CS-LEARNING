.286
.MODEL SMALL
.DATA
STRING DB 'ABCDEFGHHGFEDCBA$' ; 16个字节的字符串（不包括$)
YESSTRING DB 'yes$'
NOSTRING DB 'no$'
.STACK
.CODE
MAIN PROC FAR
    MOV AX,@DATA
    MOV DS,AX
    MOV CX,8  
AGAIN:  MOV BX,8  ; 首指针
        MOV DI,7;  尾指针
        SUB BX,CX
        ADD DI,CX
        MOV DL,STRING[BX]  ;首字符
        CMP DL,STRING[DI]  ;
        LOOPZ AGAIN        ; 相等的时候才继续
        JNZ NO             ;  最后一个字符必须相等
        CMP CX, 0          ; CX的值必须为0
        JZ YES             ; 如果CX为0且前面没有跳转证明判断到最后一个字符了，是回文字符串
NO: MOV AH,09H
    LEA DX,NOSTRING 
    JMP DONE
YES: MOV AH,09H
    LEA DX,YESSTRING
DONE: INT 21H
      MOV AH,4CH ;返回Dos
      INT 21H
MAIN ENDP
END MAIN
        