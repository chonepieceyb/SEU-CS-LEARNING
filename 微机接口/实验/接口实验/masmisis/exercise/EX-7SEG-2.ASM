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
       MOV AL, 10001001B ;  PA 方式0输出 PB方式0输出 PC方式0 输入
       OUT DX, AL 
       MOV CL,4
       MOV AH,0
L1:    MOV DX, P82552 ;     查询C口    
       IN AL,DX       
       MOV BL, AL          ;保存到BL中
       AND AL, 0F0H         ; 屏蔽低四位
       SHR AL,CL           ; 逻辑右移            
       MOV DI, AX 
       MOV AL, TABLE[DI]   ; 变址寻址查表
       MOV DX , P82550     ; PA输出十位数的段码
       OUT DX, AL
       MOV AL , 00000010B   ; 选中S1位
       MOV DX , P82551
       OUT DX , AL          
       NOP 
       NOP 
       MOV AL , 00000011B    
       OUT DX , AL
       MOV AL , BL 
       AND AL, 0FH  ;      屏蔽高四位
       MOV DI, AX
       MOV AL, TABLE[DI]   ; 变址寻址查表
       MOV DX , P82550     ; PA输出个位数的段码
       OUT DX, AL
       MOV AL, 00000001B     ; 选中S2
       MOV DX, P82551
       OUT DX, AL
       NOP
       NOP
       MOV AL, 00000011B
       OUT DX ,AL
       JMP L1
END START