.286
.MODEL SMALL
.DATA
.STACK
.CODE
START: MOV BL,6
       MOV BH,8
       MOV CL,3
       MOV CH,4
       MOV DI,0
       MOV AL,1   ; 计算最后一位
       MUL BL
       ADD DI,AX
       MOV AL,10
       MUL BH     ; 计算倒数第二位
       ADD DI,AX
       MOV AL,100 ; 计算倒数第三位
       MUL CL
       ADD DI,AX
       MOV CL,CH
       MOV CH,0    ;计算第四位        
       MOV AX,1000
       MUL CX;
       ADD DI,AX
END START