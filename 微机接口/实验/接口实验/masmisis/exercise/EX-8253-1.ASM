.286
.MODEL SMALL
.CODE
START:   MOV AL, 00010000B ; TC0，只写低位 ， 方式 0  , 端口地址是 220 - 226H
    MOV DX, 226H
    OUT DX , AL 
    MOV DX, 220H
    MOV AL,5             ;计数 5 次
    OUT DX , AL
END START