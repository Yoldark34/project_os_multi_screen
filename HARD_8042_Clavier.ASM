global Lecture_Scan_Code
global Attendre_Scan_Code
global Attendre_Touche_Relache
;-------------------------------------------------------------------------------
Lecture_Scan_Code:
    in  AL,0x60 ;Scan code dans le port 0x60 et vide le buffer
    ret

;-------------------------------------------------------------------------------
Attendre_Scan_Code:
    in  AL,0x60
.Repeter:
    in  AL,0x64
    and AL,0x01
    jz .Repeter; Jusqu'à Port(0x64) & 0x01 <> 0
    in AL,0x60
    ret


;-------------------------------------------------------------------------------
Attendre_Touche_Relache:
    in  AL,0x60
.Repeter:
    in  AL,0x64
    and AL,0x01
    jz .Repeter; Jusqu'à Port(0x64) & 0x01 <> 0
    in AL,0x60
    mov bx,ax
    and bl,0x80
    cmp bl,0x80
    jne .Repeter; et jusqu'à touche relachée
    ret





