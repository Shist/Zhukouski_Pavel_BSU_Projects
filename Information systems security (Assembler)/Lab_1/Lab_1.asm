.Model Small
.Data
CONST16 DB  16
HEXSYM  DB  '0123456789ABCDEF'
PATTERN DB  'XX-$'
CODSYM  DB  ?
ENDL    DB  0ah,0dh,'$'


.CODE
.STARTUP

    MOV     AL, 40h
    MOV     ES, AX

    MOV     CODSYM, 0
    MOV     CX, 16

PRTABLE:
    PUSH    CX
    MOV     CX, 16
POVT:

    MOV     AL, CODSYM

    MOV     AH, 0
    DIV     CONST16
    MOV     BX, Offset HEXSYM
    XLAT
    MOV     PATTERN, AL
    MOV     AL, AH
    XLAT
    MOV     PATTERN + 1, AL
    MOV     AH, 9
    LEA     DX, PATTERN
    INT     21h

    MOV     BH, ES: [ 62h ]
    MOV     BL, 0
    MOV     AH, 10
    MOV     AL, CODSYM 
    PUSH    CX 
    MOV     CX, 1
    INT     10h

    MOV     AH, 03
    INT     10h
    MOV     AH, 02
    ADD     DL, 2
    INT     10h
    ADD     CODSYM, 16

    POP     CX
    LOOP    POVT   
    MOV     AH, 9
    LEA     DX, ENDL
    INT     21h 
    POP     CX
    INC     CODSYM
    LOOP    PRTABLE

    MOV     AH, 4ch
    INT     21h
    END