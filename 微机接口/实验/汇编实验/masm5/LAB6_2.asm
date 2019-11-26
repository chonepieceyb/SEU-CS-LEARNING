.286
.MODEL SMALL
.DATA
    ARRAY DB 1,2,3,4,5,6,7,8,9,10,11,12    ;该数组假设为无符号数的数组
.STACK
.CODE
SEARCH PROC NEAR
    MOV AX,@DATA 
    MOV DS,AX             
    PUSH AX           ; 入口参数 SI(存放A_HEAD),DI(存放A_END)，DL存放N ,  出口参数， SI和DI存放新的数组的 头尾， CF, 采用二分查找法  用到了 AX,DS,ES DX,BX,CX
    PUSH DS
    PUSH ES
    PUSH DX
    PUSH BX
    PUSH CX
    PUSH SI
    PUSH DI       ;DI最后PUSH
AGAIN : CMP SI,DI ; 比较首尾指针
        JG FAIL;  如果首偏移大于尾偏移失败了 这里编译假设是有符号数
        MOV AX,DI     ;计算数组的长度
        SUB AX,SI   
        MOV DH , AL ; DH存放数组的长度
        SHR DH,1; 
        MOV BX,SI;   BX存放中间点的位置
        ADD BL,DH   ;计算BX的值
        ADC BL,0;
        MOV AL, [BX] ; 中间的数
        CMP DL, AL
        JZ SUS       ;相等则成功 
        JA GREAT      ; 如果小于
        JB LESS       ; 如果小于
GREAT: MOV SI,BX ;    把起点设为中间值
       INC SI
       JMP AGAIN
LESS:  MOV DI,BX ;    把终点设为中间值
       DEC DI;
       JMP AGAIN
SUS:   CLD        ; BX存放的是当前元素的偏移量
       MOV AX,DS;
       MOV ES,AX
       POP CX;
       PUSH CX;
       SUB CX,BX;   计算循环次数        
       MOV SI,BX
       MOV DI,BX
       INC SI 
       REP MOVSB
       POP DI
       POP SI
       MOV AH ,0FFH
       ADD AH, 1 ; 置CF为1
       JMP DONE
FAIL:
       MOV AH,0H
       ADD AH,1;  置CF为0
       POP DI
       POP SI
DONE:
       POP CX
       POP BX
       POP DX
       POP ES
       POP DX
       POP AX
       RET
SEARCH ENDP
MAIN PROC FAR
    LEA SI,ARRAY
    MOV DI,SI 
    ADD DI, 11
    MOV DL,4
    CALL SEARCH
    MOV AH, 4CH
    INT 21H
MAIN ENDP
END MAIN
    
    