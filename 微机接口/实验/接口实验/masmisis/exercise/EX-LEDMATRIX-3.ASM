.8086
.MODEL SMALL
.STACK
.DATA
W0 BYTE 000H, 020H  ;       @  @       我
   BYTE 008H, 024H  ;      @@@ @ @     
   BYTE 048H, 024H  ;   @@@@   @  @    
   BYTE 084H, 024H  ;      @   @  @    
   BYTE 07FH, 0FEH  ;      @   @    @  
   BYTE 002H, 023H  ;  @@@@@@@@@@@@@@@ 
   BYTE 021H, 022H  ;      @   @       
   BYTE 010H, 020H  ;      @   @  @    
   BYTE 009H, 0FFH  ;      @ @ @  @    
   BYTE 006H, 020H  ;      @@   @@     
   BYTE 01AH, 022H  ;     @@    @      
   BYTE 061H, 0ACH  ;   @@ @   @ @     
   BYTE 080H, 020H  ;      @  @  @     
   BYTE 0E0H, 030H  ;      @ @    @ @  
   BYTE 000H, 020H  ;    @ @      @ @  
   BYTE 000H, 000H  ;     @        @@  
W1 BYTE 040H, 020H  ;         @        太
   BYTE 040H, 020H  ;         @        
   BYTE 020H, 020H  ;         @        
   BYTE 020H, 020H  ;         @        
   BYTE 010H, 020H  ;         @     @  
   BYTE 00CH, 020H  ;  @@@@@@@@@@@@@@@ 
   BYTE 00BH, 020H  ;         @        
   BYTE 030H, 0FFH  ;         @        
   BYTE 003H, 020H  ;        @ @       
   BYTE 00CH, 020H  ;        @ @       
   BYTE 010H, 020H  ;       @   @      
   BYTE 010H, 020H  ;       @@  @      
   BYTE 020H, 020H  ;      @  @  @@    
   BYTE 060H, 030H  ;    @@   @    @@@ 
   BYTE 020H, 020H  ;  @@           @  
   BYTE 000H, 000H  ;                  
W2 BYTE 020H, 004H  ;           @@     难
   BYTE 010H, 034H  ;       @   @ @    
   BYTE 00CH, 0C4H  ;  @@@@@@@  @   @  
   BYTE 003H, 004H  ;       @  @@@@@@@ 
   BYTE 004H, 0C4H  ;   @   @  @  @    
   BYTE 018H, 03EH  ;   @   @ @@  @    
   BYTE 000H, 044H  ;    @ @ @ @@@@@@  
   BYTE 000H, 020H  ;    @ @   @  @    
   BYTE 0FFH, 0F8H  ;     @    @  @    
   BYTE 022H, 04FH  ;     @    @@@@@@  
   BYTE 022H, 049H  ;    @ @   @  @    
   BYTE 03FH, 0FAH  ;    @  @  @  @    
   BYTE 022H, 048H  ;   @   @  @  @ @  
   BYTE 032H, 04CH  ;  @       @@@@@@@ 
   BYTE 020H, 008H  ;          @       
   BYTE 000H, 000H  ;          @       
W3 BYTE 000H, 000H  ;                  了
   BYTE 000H, 002H  ;   @@@@@@@@@@@@   
   BYTE 000H, 002H  ;             @    
   BYTE 000H, 002H  ;            @     
   BYTE 000H, 002H  ;           @      
   BYTE 040H, 002H  ;         @@       
   BYTE 080H, 002H  ;         @        
   BYTE 07FH, 0E2H  ;         @        
   BYTE 000H, 022H  ;         @        
   BYTE 000H, 012H  ;         @        
   BYTE 000H, 00AH  ;         @        
   BYTE 000H, 006H  ;         @        
   BYTE 000H, 002H  ;         @        
   BYTE 000H, 000H  ;         @        
   BYTE 000H, 000H  ;       @ @        
   BYTE 000H, 000H  ;        @         
WOFFSET DW  0                ;用于滚动的变量
P82530 EQU 220H ;  8253端口
P82531 EQU 222H 
P82532 EQU 224H 
P82533 EQU 226H
P82590 EQU 210H  ; 8259端口
P82591 EQU 212H  
P82550 EQU 200H  ; 8255端口
P82551 EQU 202H
P82552 EQU 204H
P82553 EQU 206H      
.CODE
START: MOV AX, @DATA        
       MOV DS , AX 
       CLI
       MOV AX,0            ;写中断向量表
       MOV ES,AX
       MOV SI , 0
       MOV CX, 255
L0:    MOV AX , OFFSET SERVICE
       MOV ES:[SI] , AX 
       MOV AX , SEG SERVICE
       MOV ES:[SI+2] , AX
       ADD SI,4
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
       MOV AL, 01010110B ; TC1 方式3 只写低 （计数值为100）1khz / 10 hz = 100
       OUT DX, AL
       MOV AL ,100      ;计数初值为100
       MOV DX , P82531
       OUT DX, AL
INIT1: MOV DX,P82553     ;8255芯片初始化
       MOV AL,10000000B  ; PA PB PC口方式0 输出
       OUT DX, AL 
INIT2: MOV DX, P82590    ; 8259芯片初始化
       MOV AL, 00010011B  ; ICW1 边沿触发，单片使用 需要ICW4
       OUT DX, AL
       MOV DX, P82591
       MOV AL, 60H        ; ICW2 60H 中断向量号为 60H + 0 = 60H
       OUT DX, AL
       MOV AL, 00000001B;   ICW4全嵌套，非自动结束 非缓冲方式
       OUT DX ,AL
INIT3: MOV BX, WOFFSET         ;基址寄存器，存放最开始的基地址，在滚动的时候用来控制最左边的数据，随着字的滚动基址发生变化                     ;字模打印代码初始化部分        
       MOV DI ,0        ;变址寄存器，用来存放相对与基址的偏移，在一次滚动的时候，控制不同的数据,DI是字模索引
       MOV CL,0         ;CL存放列号, 同时由于寄存器有限， CL也用来存放锁存器的脉冲，在循环过程中使用堆栈
       MOV CH,0         ;CH 控制锁存器输出的循环变量 
       STI              ;开中断
PRINT: MOV DX, P82552   ; C口输出列号
       MOV AL, CL 
       OUT DX , AL 
       PUSH CX                        ;保存循环变量 CL
       MOV CL ,00000001B               ; 锁存脉冲
L1:    MOV SI , DI                     ; 当前字节地址
       ADD SI , BX 
       AND SI , 07FH                 ;模运算 只取低8位，确保 BX + DI <128
       MOV DX , P82550                  ; 循环将数据锁存到寄存器
       MOV AL, W0[SI]              
       OUT DX, AL
       MOV DX, P82551                 ;发出高电平（对应锁存器）
       MOV AL , CL      
       OUT DX, AL                         
       MOV AL,0
       OUT DX,  AL                    ;发出低电平           
       SHL CL,1                      ;脉冲左移，（下一个锁存器的脉冲）
       MOV DX , P82550                  ; 循环将数据锁存到寄存器
       MOV AL, W0[SI+1]              
       OUT DX, AL
       MOV DX, P82551                 ;发出高电平（对应锁存器）
       MOV AL , CL      
       OUT DX, AL                        
       MOV AL,0
       OUT DX,  AL                    ;发出低电平          
       SHL CL,1                      ;脉冲左移，（下一个锁存器的脉冲）
       INC CH    
       ADD BX ,32                    ;下一个字
       CMP CH,4
       JNZ L1                       ;四个字的字模都输出完了
       MOV BX,WOFFSET  
       POP CX                       ;取出列循环变量
       MOV CH,0
       INC CL                       ;列+1
       ADD DI,2            
       CMP CL , 16
       PUSH CX
       MOV CX, 60
	   LOOP $         ;延迟16个指令周期  ，因为之前在输入下一个led字的行数据之后都有延时（从一个到下一个之间的间隔时间，但最后一个没有，所以最后一个手动增加延时
	   POP CX
       JNZ PRINT                     ;16列还没输出完
       MOV DI,0
       MOV CL,0
       JMP PRINT                      ;输出完了
SERVICE PROC FAR                 ;使用的寄存器 AX , DS  DX
    PUSH AX
    PUSH DS
    PUSH DX
    MOV AX,@DATA
    MOV DS, AX 
    MOV AX,WOFFSET 
    ADD AX,2            ;每次+2
    AND AX , 07FH       ; WOFFSET<128
    MOV WOFFSET, AX
    MOV DX, P82590       ;发送eoi
    MOV AL,20H
    OUT DX ,AL
    POP DX
    POP DS
    POP AX
    IRET
SERVICE ENDP
END START