.MODEL SMALL
.8086
.stack
.data
	WO BYTE 000H, 020H  ;       @  @       我
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
	
	TAI BYTE 040H, 020H  ;         @        太
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
	
	NAN BYTE 020H, 004H  ;           @@     难
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
	   
	HZ BYTE 000H, 000H  ;                  了
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
	
.code
start:
	mov ax, @data
	mov ds, ax
	mov al, 10000000b      ;8255设置工作方式
	mov dx, 206h
	out dx, al
	mov cl, 0              ; 循环变量
	mov si, 0
l:
	mov al, cl
	mov dx, 204h           ; C口， C口存列线
	out dx, al
	lea bx, WO
	mov ah, 1
	mov ch, 0
l1:
	mov al, [bx+si]
	mov dx, 200h           ; PA
	out dx, al
	mov al, ah             ;锁存
	mov dx, 202h
	out dx, al
	mov al, 00h 
	out dx, al
	shl ah, 1              ;锁存第二个寄存器
	mov al, [bx+si+1]      
	mov dx, 200h
	out dx, al
	mov al, ah             ;锁存第二个寄存器
	mov dx, 202h
	out dx, al
	mov al, 00h
	out dx, al
	shl ah, 1              
	add bx, 32
	inc ch
	cmp ch,4
	jnz l1
	push cx
	mov cx, 16
	loop $         ;延迟20个指令周期  ，因为之前在输入下一个led字的行数据之后都有延时（从一个到下一个之间的间隔时间，但最后一个没有，所以最后一个手动增加延时
	pop cx
	inc cl
	add si, 2
	cmp cl, 16
	jnz l
	mov cl, 0
	mov si, 0
	jmp l
end start