.MODEL SMALL
.STACK 400h
.DATA
	BinFile db "VICTDATA.BIN", 0
	ErrMessage db "Error with the file$"
	ErrMessageLen = $ - ErrMessage
	KeyCodes db 29h, 02h, 03h, 04h, 05h, 06h, 07h, 08h
	db 09h, 0Ah, 0Bh, 0Ch, 0Dh, 2Bh, 10h, 11h
	db 12h, 13h, 14h, 15h, 16h, 17h, 18h, 19h
	db 1Ah, 1Bh, 1Eh, 1Fh, 20h, 21h, 22h
	db 23h, 24h, 25h, 26h, 27h, 28h, 2Ch, 2Dh
	db 2Eh, 2Fh, 30h, 31h, 32h, 33h, 34h, 35h
	db 39h
	KeyCodesLen = $ - KeyCodes
	KeySymbs db "`1234567890-=\qwertyuiop[]asdfghjkl;'zxcvbnm,./ "
	ShiftKeySymbs db '~!@#$%^&*()_+|QWERTYUIOP{}ASDFGHJKL:"ZXCVBNM<>? '		  
	ShiftPushed db 0
	Buffer db 100h dup(?) 
	Handle dw 0
	CRLF db 0Dh, 0Ah, "$"
.CODE
ScanCodeFix:
		cmp		al, bl
		je		.Fit
		clc
		ret
.Fit: stc
		ret
ShiftPushedCheck:
		mov		bl, 2Ah
		call	ScanCodeFix
		jnc		.RightShiftPushedCheck
		ret
.RightShiftPushedCheck:		
		mov		bl, 36h
		jmp		ScanCodeFix
ShiftFreeCheck:      
		mov		bl, 0AAh
		call	ScanCodeFix
		jnc		.RightShiftFreeCheck
		ret
.RightShiftFreeCheck:
		mov		bl, 0B6h
		jmp		ScanCodeFix
EnterPushedCheck:
		mov		bl, 1Ch
		jmp		ScanCodeFix
SpecSymbsCheck:
		call 	ShiftPushedCheck
		jnc		.ShiftIsFree
		inc		ShiftPushed
		jmp		.EndCheck
.ShiftIsFree:
		call 	ShiftFreeCheck
		jnc		.EnterCheck		
		dec 	ShiftPushed
		jmp		.EndCheck
.EnterCheck:
		call	EnterPushedCheck
		jnc		.EndCheck
		mov		ah, 09h
		lea		dx,	CRLF
		int		21h					
.EndCheck:
		ret		
HandleSymb:
		push	cx
		push	bx
		push	si
		push 	dx
		call	SpecSymbsCheck
		jc		.HandleSymbExit
.PrintingAttempt:		          		
		lea		si, KeyCodes
		mov		cx, KeyCodesLen
		mov		dl, al
.PrintingAttemptInCycle:
		lodsb
		cmp		dl, al
		je		.AfterCycleCheck
		loop	.PrintingAttemptInCycle
.AfterCycleCheck:
		jcxz	.HandleSymbExit
		mov		al, cl
		neg		al
		add		al, KeyCodesLen
		cmp		ShiftPushed, 0
		jnz		.GetCharsWithShift
		lea		bx, KeySymbs
		jmp 	.PrintSymb
.GetCharsWithShift:
		lea		bx, ShiftKeySymbs
.PrintSymb:
		xlatb
		mov 	dl, al
		mov		ah, 02h
		int		21h				      	
.HandleSymbExit:
		pop		dx
		pop		si
		pop		bx	     
		pop		cx
		ret

start:	mov		ax, @DATA
		mov		ds, ax
	
		mov		ax, 3D80h
		lea		dx, BinFile
		int		21h
		jc		.Error
		mov		Handle, ax
.ReadData:
		mov		ah, 3Fh	                    
		mov		bx, Handle
		mov		cx, 100h
		lea		dx, Buffer
		int		21h
		jc		.error
		lea 	si, Buffer
		mov		cx, ax
		jcxz	.finish
.Cycle:	lodsb
		call 	HandleSymb
		loop 	.Cycle	
		jmp 	.ReadData

.finish:       	      	
		mov 	bx, Handle
		mov 	ah, 3Eh
		int 	21h
		mov 	ax, 4C00h
		int 	21h
	
.Error:	cmp 	Handle, 0
		je 		.ErrorCaseExit
		mov 	bx, Handle
		mov 	ah, 3Eh
		int		21h
.ErrorCaseExit:	
		lea 	dx, ErrMessage
		mov 	ah, 09h
		int 	21h
		mov 	ax, 4C01h
		int 	21h
end start
