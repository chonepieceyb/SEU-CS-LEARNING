.MODEL SMALL
.8086
.DATA
P82550 EQU 200H     ;端口号
P82551 EQU 202H
P82552 EQU 204H
P82553 EQU 206H
P82590 EQU 210H
P82591 EQU 212H 
CTROL DB 00000001B  
.CODE 
START:  MOV AX,@DATA
        MOV DS, AX
        CLI                ; 关中断
        MOV AX,0           ; 写中断向量表, 由于模拟器有问题，需要把所有中断向量表都写上
        MOV ES, AX 
        MOV CX,255 
        MOV SI , 0 
L0:     MOV AX, OFFSET SERVICE
        MOV ES:[SI], AX
        MOV AX ,SEG SERVICE
        MOV ES:[SI+2], AX
        ADD SI, 4 
        LOOP L0
INIT0: MOV DX , P82590     ; ICW1     8259初始化    
    MOV AL , 00010011B     ; 单片使用，边沿触发，需要ICW4
    OUT DX , AL  
    MOV DX , P82591     
    MOV AL ,60H         ;  ICW2 中断向量号为 60H+2 = 62H
    OUT DX, AL;
    MOV AL , 00000101B  ;  ICW4 全嵌套，非缓冲，非自动结束
    OUT DX, AL
INIT1: MOV DX , P82553      ;8255初始化   
    MOV AL , 10000000B  ; 设置 PA方式0 输出
    OUT DX, AL   
    MOV AL, CTROL       ; PA初始化
    MOV DX, P82550    
    OUT DX,AL
    STI                  ;开中断
JMP $                    ;无限循环
SERVICE PROC FAR         ;中断服务子程序, 每进入一次子程序，将CTROL向右循环移位一次, 使用了 AX ，DS寄存器
    PUSH AX           ; 保护现场
    PUSH DX
    PUSH DS
    MOV AX, @DATA
    MOV DS,AX
    MOV AL, CTROL     ; 取控制变量
    ROL AL ,1                   ;循环移位，不带进位
    MOV DX , P82550 
    OUT DX, AL         ;输出
    MOV CTROL , AL     ;写回内存
    MOV AL ,20H        ; 结束 20送20, 发EOI命令
    MOV DX, P82590  
    OUT DX , AL 
    POP DS
    POP DX
    POP AX
    IRET
SERVICE ENDP
END START