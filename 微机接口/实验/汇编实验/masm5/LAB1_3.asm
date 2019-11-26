.8086
.MODEL SMALL
.STACK
.DATA
LINE DB 0AH,0DH,'$'
INPUT DB 100
      DB ?
      DB 100 DUP('$')
.CODE
START: MOV AX,@DATA
	   MOV DS,AX
	   LEA DX,INPUT     
       MOV AH,0AH       ;ÊäÈë×Ö·û´® 
       INT 21H  
       LEA DX,LINE
       MOV AH,09H
       INT 21H
	   LEA DX, INPUT
	   ADD DX,2
       MOV AH,09H
       INT 21H
	   MOV AH,4CH
	   INT 21H
END START
