.8086
.MODEL SMALL
.DATA
   P82530 EQU 220H ;  8253端口
   P82531 EQU 222H 
   P82532 EQU 224H 
   P82533 EQU 226H
   P82590 EQU 210H  ; 8259端口
   P82591 EQU 212H  
   P82550 EQU 200H  ; 8255端口
   P82553 EQU 206H  
   STATEF DB  0AH      ; 状态字， 其中 S0-S3:当前计数次数（计数次数不会超过16）; S4,S5: 当前状态，从状态0-3; S6:黄灯是否亮 0表示不亮 ;S7无效
.CODE
START: MOV AX ,@DATA
       MOV DS ,AX
       CLI          ; 关中断
       MOV AX,0           ; 写中断向量表, 由于模拟器有问题，需要把所有中断向量表都写上
       MOV ES, AX 
       MOV CX,255 
       MOV SI , 0 
L0:    MOV AX, OFFSET SERVICE
       MOV ES:[SI], AX
       MOV AX ,SEG SERVICE
       MOV ES:[SI+2], AX
       ADD SI, 4 
       LOOP L0
INIT0: MOV DX, P82533   ;8253芯片初始化
       MOV AL, 00110110B ; TC0 方式3 先写低再写高
       OUT DX, AL
       MOV AX ,1000       ;计数初值为1000
       MOV DX , P82530
       OUT DX, AL
       MOV AL, AH
       OUT DX, AL
       MOV DX, P82533
       MOV AL, 01110110B ; TC1 方式3 先写低再写高
       OUT DX, AL
       MOV AX ,1000       ;计数初值为1000
       MOV DX , P82531
       OUT DX, AL
       MOV AL, AH
       OUT DX, AL
INIT1: MOV DX,P82553     ;8255芯片初始化
       MOV AL,10000000B  ; PA口方式0 输出
       OUT DX, AL 
       MOV DX, P82550    ; PA口初始化
       MOV AL, 10000001B  ; 初始状态为S0 南北方向绿灯亮，东西方向红灯亮
       OUT DX, AL
INIT2: MOV DX, P82590    ; 8259芯片初始化
       MOV AL, 00010011B  ; ICW1 边沿触发，单片使用 需要ICW4
       OUT DX, AL
       MOV DX, P82591
       MOV AL, 60H        ; ICW2 60H 中断向量号为 60H + 0 = 60H
       OUT DX, AL
       MOV AL, 00000001B;   ICW4全嵌套，非自动结束 非缓冲方式
       OUT DX ,AL 
       STI              ;开中断
       JMP $             ;无限循环
SERVICE PROC FAR          ;中断服务子程序,统计计数的次数，完成状态的转化， 使用了 DX AX  DI BX寄存器
       PUSH AX
       PUSH DX
       PUSH DI
       PUSH BX
       MOV BL,STATEF     ; 取出状态字
       MOV AL,BL
       AND AL, 00110000B
       CMP AL, 00000000B
       JZ S0
       CMP AL, 00010000B
        JZ S1
         CMP AL, 00100000B
       JZ S2
       CMP AL, 00110000B
        JZ S3       
S0:    TEST BL , 0FH      ;  if count>0
       JNZ DONES          ;  不为0 就正常操作
       MOV BL, 00010100B           ;  为 0 的话状态转为 S1 , 计数初值为4 , 跳转到 S1
S1:    TEST BL , 0FH
       JZ  CHANGES1                ; 如果值为 0 改变S1状态
       TEST BL, 01000000B                            ; 如果值不为0 ,查看当前黄灯状态
       JNZ  OFFS1                                 ;如果黄灯是亮的
       MOV DX,P82550
       MOV AL,01000001B                ; 让黄灯亮,和其它交通灯状态
       OUT DX, AL
       OR BL, 01000000B         ;改控制字黄灯位
       JMP DONES
OFFS1:  MOV DX, P82550                  ;让黄灯灭
        MOV AL, 00000001B  
        OUT DX,AL 
        AND BL, 10111111B               ;改控制字黄灯位
        JMP DONES
CHANGES1 : MOV BL,00101010B           ; 如果count = 0 就将状态从 S2变为 S3 , 状态2 计数初值为10
           MOV DX, P82550             ;设置 S2的交通等状态
           MOV AL , 00100100B         
           OUT DX , AL  
S2:    TEST BL , 0FH      ;  if count>0
       JNZ DONES          ;  不为0 就正常操作
       MOV BL, 00110100B           ;  为 0 的话状态转为 S3 , 计数初值为4 , 跳转到 S3                                 
S3:    TEST BL , 0FH
       JZ  CHANGES3                ; 如果值为 0 改变S3状态
       TEST BL, 01000000B                            ; 如果值不为0 ,查看当前黄灯状态
       JNZ  OFFS3                                ;如果黄灯是亮的
       MOV DX,P82550
       MOV AL,00100010B                ; 让黄灯亮,和其它交通灯状态
       OUT DX, AL
       OR BL, 01000000B         ;改控制字黄灯位
       JMP DONES
OFFS3:  MOV DX, P82550                  ;让黄灯灭
        MOV AL, 00100000B   
        OUT DX,AL 
        AND BL, 10111111B               ;改控制字黄灯位
        JMP DONES
CHANGES3 : MOV BL,00001010B           ; 如果count = 0 就将状态从 S3变为 S0 , 状态0 计数初值为10
           MOV DX, P82550             ;设置 S0的交通等状态
           MOV AL , 10000001B         
           OUT DX , AL  
        JMP S0                       ; 跳转到S0状态
DONES:  SUB BL,1                   ;计数值 -1
        MOV STATEF, BL             ;保存
        MOV AL,20H                 ;发送EOI
        MOV DX,P82590
        OUT DX,AL
        POP BX
        pop DI
        POP DX
        POP AX
        IRET
SERVICE ENDP
END START
          
          
          
          
          