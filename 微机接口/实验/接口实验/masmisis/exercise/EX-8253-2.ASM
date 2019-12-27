.286
.MODEL SMALL
.CODE
START: MOV AL ,00110110B ;  TC0 先写低字节再写高字节，方式3 ， 端口地址是从 220H - 226H
       MOV DX, 226H
       OUT DX,AL 
       MOV AX,1000 ; 计数初值是1000  tc0产生1khz的方波
       MOV DX,220H
       OUT DX, AL
       MOV AL,AH
       OUT DX,AL
       MOV AL , 01110110B ; TC1 先写低字节再写高字节，方式3 
       MOV DX,226H
       OUT DX , AL
       MOV AX,1000 ; 计数初值是1000  tc1产生1hz的方波
       MOV DX,222H
       OUT DX, AL
       MOV AL,AH
       OUT DX,AL
       MOV AL, 10010110B ; TC2 只写低字节，方式3
       MOV DX ,226H
       OUT DX, AL
       MOV AL,5        ;计数初值是5， tc2产生 周期为5 占空比为3 : 2的方波
       MOV DX,224H
       OUT DX,AL
END START