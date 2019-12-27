.8086
.MODEL SMALL
.DATA
    TABLE DB 3FH,06H,5BH,4FH,66H,6DH,7DH,07H,7FH,6FH,77H,7CH,39H,5EH,79H,71H
    P82550 EQU 200H     ;端口号
    P82551 EQU 202H
    P82552 EQU 204H
    P82553 EQU 206H
.CODE
START: MOV AX,@DATA
       MOV DS , AX
INIT:  MOV DX, P82553 ;8255初始化
       MOV AL, 10001001B ;  PA 方式0输出 PC方式0 输入
       OUT DX, AL 
L1:    MOV DX, P82552 ;     查询C口    
       IN AL,DX       
       AND AL, 0FH         ; 屏蔽高四位
       MOV AH,0      
       MOV DI, AX 
       MOV AL, TABLE[DI]   ; 变址寻址查表
       MOV DX , P82550     ; PA输出
       OUT DX, AL
       NOP
       JMP L1
END START
       