.MODEL SMALL
.286
.stack
.data
LED     byte 00000001B
.code
start:
    cli
    mov ax,0        ; init interrupt vector TABLE
    mov es,ax
;   mov si,61h*4     ; init INT2 interrupt vector
    mov si,0         ; init all INT interrupt vector to the same
    mov cx,255
l:  mov ax,offset int0
    mov es:[si],ax
    mov ax,seg int0
    mov es:[si+2],ax
    add si,4
    loop l
    mov ax,@data
    mov ds,ax
    mov dx,206h    ; init 8255
    mov al,10000000b
    out dx,al
    mov al,LED
    mov dx,200h
    out dx,al
    mov al,00010011b  ;  init  8259
    mov dx,210h
    out dx,al         ; ICW1
    mov al,60h
    mov dx,212h
    out dx,al         ; ICW2
    mov ax,00000001h
    out dx,al         ; ICW4
    mov ax,0
    out dx,al         ; OCW1
    mov dx,226h    ; init 8253 ctc0
    mov al,00110111b
    out dx,al
    mov ax,2000h
    mov dx,220h
    out dx,al
    mov al,ah
    out dx,al
    sti
    jmp $
int0  proc
    push ds
    push ax
    push dx
    sti
    mov ax,@data
    mov ds,ax
    mov al, LED
    rol  al, 1
    mov LED, al
    mov dx, 200h
    out   dx, al
    mov al,20h
    mov dx,210h
    out dx,al
    cli
    pop dx
    pop ax
    pop ds
    iret
int0 endp
END start
