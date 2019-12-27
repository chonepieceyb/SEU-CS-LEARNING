.286
.MODEL SMALL
.CODE
    ; 端口地址 从200H - 206H
START:    MOV DX,206H              ;  控制口地址
    MOV AL, 10001001B        ;  A口输出（0） C口输入（1）都是方式0
    OUT DX, AL               ;  写控制字
L1: MOV DX , 204H             ;C口地址
    IN  AL, DX
    NOT AL                   ;取反
    MOV DX,  200H          ;A口地址
    OUT DX, AL 
    JMP L1          
END START