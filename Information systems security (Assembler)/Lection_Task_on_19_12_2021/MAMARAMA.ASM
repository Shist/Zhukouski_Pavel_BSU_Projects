.MODEL SMALL
.DATA
TEXT DB 'Mama', 10, 'mila', 13, 'ramu', '10', 13, "$"
.CODE
START:
    MOV AX, @DATA
    MOV DS, AX
    MOV AH, 09h
    MOV DX, OFFSET TEXT
    INT 21h
    MOV AX, 4C00h
    INT 21h 
END START
