s_s segment

s_s ends


d_s segment

d_s ends


c_s segment
assume ss:s_s, ds:d_s, cs:c_s
begin:
mov ax, d_s
mov ds, ax
mov ax, 0


    ; Your code needs to be here


mov ah, 4ch
int 21h
c_s ends
end begin