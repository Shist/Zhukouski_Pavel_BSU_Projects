.model small
.data
Zu	db	"ЯД"
ZuZU	dw	255 dup (?)
.code
POISON:
	MOV 	AX, @data
    	MOV 	DS, AX
	LEA	DX, Zu
	MOV	ah, 10
	INT	21h
	end	POISON