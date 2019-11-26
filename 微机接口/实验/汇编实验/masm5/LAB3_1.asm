.286
.MODEL SMALL
.DATA
MON DB 'Monday$'
TUE DB 'Tuesday$'
WED DB 'Wednesday$'
THU DB 'Thursday$'
FRI DB 'Friday$'
SAT DB 'Saturday$'
SUN DB 'Sunday$'
LINE DB 0AH,0DH,'$'  ; 换行符号组成一个字符串
TABLE DW MONDAY  ; 跳转表
      DW TUESDAY
      DW WEDNESDAY
      DW THURSDAY
      DW FRIDAY
      DW SATURDAY
      DW SUNDAY
.STACK
.CODE
START:MOV AX,@DATA
      MOV DS,AX ; 段地址
      MOV AH,01H ; 从键盘上输入字符
      INT 21H
      AND AL,0FH; 屏蔽掉高四位获取数字
      LEA DX,LINE ;换行
      MOV AH,09H
      INT 21H
      SUB AL,1;    下标从0开始所以减1  1-7分别代表周一-周日
      SHL AL,1 ;   间隔两个单位，左移1位
      MOV BL,AL   ; 设置 BX的值，采用变址寻址方式
      MOV BH,0
      JMP WORD PTR TABLE[BX] ; 
MONDAY: LEA DX,MON   ;周一，AH前面已经指定过了
        JMP DONE
TUESDAY: LEA DX,TUE   ;周二
        JMP DONE
WEDNESDAY: LEA DX,WED  ;周三
        JMP DONE
THURSDAY: LEA DX,THU   ;周四
        JMP DONE
FRIDAY: LEA DX,FRI   ;周五
        JMP DONE
SATURDAY: LEA DX,SAT    ;周六
        JMP DONE
SUNDAY: LEA DX,SUN   ;周日，最后一个不用JMP
DONE: INT 21H
MOV AH,4CH
      INT 21H
      END START