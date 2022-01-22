.MODEL SMALL

.DATA
pswd        DB      1Fh, 23h, 17h, 1Fh, 14h, 0Fh, 0Eh, 41h, '$' ; Password: S, H, I, S, T, Tab, Backspace, F7
inputmsg    DB      "Enter your password$"
successmsg  DB      "Password confirmed. You are welcome!$"
errmsg      DB      "The password is incorrect, try again...$"
errcount    DB      0 ; <-- This is error counter
endl        DB      0AH, 0DH, '$'

.CODE

UU:

MOV AX, @DATA
MOV DS, AX
MOV AH, 9
LEA DX, inputmsg
INT 21H
LEA DX, endl
INT	21H
MOV CX, 8 ; <-- The whole count of symbols (keys) in the password (for cycle iterations)
LEA SI, pswd
MOV DH, 1

VERIFY:

LODSB
MOV BH, AL
MOV AH, 0H
INT 16H
CMP AH, BH ; <-- Symbols comparison
JE TRUESYMB ; <-- In case of correct symbol
ADD errcount, 1 ; <-- In case of wrong symbol

TRUESYMB:

LOOP VERIFY ; <-- Go through the loop until the number of iterations ends 
MOV AH, errcount
CMP AH, 0 ; <-- Check if error count is null or not
JNE FAILURE ; <-- In case when error count is not null
MOV	AH, 9
LEA DX, successmsg
INT 21H
JMP SUCCESS

FAILURE:

MOV	AH, 9
LEA DX, errmsg
INT 21H

SUCCESS:

MOV AH, 4CH 
INT 21h
END UU
