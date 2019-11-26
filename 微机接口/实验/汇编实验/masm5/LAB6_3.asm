.286
.MODEL SMALL 
.DATA
ATTENTION DB 'You must input 0~129$'
TABLE DB '0000000100100011010001010110011110001001101010111100110111101111$'
OUTPUT DB '00000000$'        ;输出是8位
INPUT DB 6     ; 由于是从 0-129所以预留4位内存（包括$)
      DB ?
      DB 6 DUP(?)
.STACK
.CODE
LINE PROC NEAR          ; 换行输入输出子程序, 使用了 AX ， DX寄存器
    PUSH AX
    PUSH DX
    MOV AH,02H
    MOV DL,0AH
    INT 21H
    MOV DL, 0DH 
    INT 21H
    POP DX
    POP AX
    RET
LINE ENDP
GETINPUT PROC NEAR ;  从键盘获取十进制数，并且将其储存在BL中 出口参数BL， 使用的寄存器 AX,DS ,DX ,DI ,CX
    PUSH AX
    PUSH DS
    PUSH DX
    PUSH DI
    PUSH CX
    MOV AX,@DATA
    MOV DS,AX 
    MOV AH,0AH  ;   从键盘获取输入
    LEA DX,INPUT
    INT 21H  
    LEA DI ,INPUT
    ADD DI ,2;  
    MOV CX ,0;   用来计算位数
    MOV BL ,0             
GETINPUTAGAIN:  CMP BL,129
        JA GETINPUTERROR      ;如果大于129那么报错
        MOV DL, [DI]  ; 获取当前字符
        CMP DL,0DH
        JZ GETINPUTNEXT       ;判断是否是回车，如果是的话跳转
        SUB DL,30H    ; 将ASCII 码转化为数字
        CMP DL,0      ;必须大于0
        JL GETINPUTERROR      ; 小于0 ERROR
        CMP DL,9      ;必须小于9
        JG GETINPUTERROR      ;大于9 跳走  采用无符号数的判断 因为字符可能小于 30H
        MOV AL,10     ;将字符转化为数值 
        MUL BL  
        MOV BL,AL     ;保存乘法结果
        CMP AH,0      ; 因为结果存在BL中，所以 AH一定是为0的，防止溢出，而字节乘法存在AX中，无法用OF来判断
        JNZ GETINPUTERROR     
        ADD BL,DL     ; 防止加法溢出
        JC GETINPUTERROR    ;无符号数溢出用CF判断
        INC CX        ;计数器
        INC DI
        JMP GETINPUTAGAIN
GETINPUTERROR: MOV AH,09H   ;如果出错打印错误信息
       LEA DX, ATTENTION 
       INT 21H
       CALL LINE
       CALL GETINPUT     ;再次输入         
       JMP  GETINPUTDONE                           
GETINPUTNEXT:  CMP CX ,0           ;如果BL的值为129的话先不管
       JZ GETINPUTERROR ;  防止无输入
GETINPUTDONE:  POP CX         ;保护现场
       POP DI
       POP DX
       POP DS
       POP AX
       RET
GETINPUT ENDP     

PRINTBINARY PROC NEAR ;  将BL中的值以二进制的形式打印出去,入口参数BL, 输出字符串是 STRING 要预先设置好DS , 由于BL中的数是16进制数， 16进制转二进制1为代表2进制4为，采用查表法，用空间换时间十分容易，不采用10进制转二进制的方法
        PUSHA         ;没有出口参数 所以直接全部入栈
        LEA DI, OUTPUT 
        LEA SI,TABLE     ;转化表基址
        MOV AL,BL             ; 先查高四位
        MOV AH,0
        MOV CL,4
        SHR AL,CL             ; 右移4位
        MOV CL,2
        SHL AL,CL             ;左移两位
        ADD SI,AX         
        MOV CX,4    ;传送高4个字节的字符
        REP MOVSB
        MOV AL,BL
        AND AL,0FH        ; 屏蔽高四位
        MOV CL,2
        SHL AL,CL          ; 左移两位，因为字节单位是4 
        LEA SI,TABLE
        ADD SI,AX       
        MOV CX,4
        REP MOVSB             ;传送第四个字节的字符
        JMP PRINTBINARYDONE
PRINTBINARYDONE:   LEA DX, OUTPUT
                   MOV AH ,09H
                   INT 21H      ;将字符串输出
                   POPA
                   RET
PRINTBINARY ENDP
MAIN PROC FAR       ;主函数
AGAIN:    MOV AX,@DATA
          MOV DS,AX
          MOV ES,AX
          CALL GETINPUT   ;获得输入
          CMP BL,129      ;如果是129 返回DOS
          JZ EXIT
          CALL LINE      ;换行
          CALL PRINTBINARY ;输出
          CALL LINE      ;换行
          JMP AGAIN
EXIT:  MOV AH,4CH      ; 返回DOS
       INT 21H
       RET
MAIN ENDP
END MAIN