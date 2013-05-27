; /*
;
; Fréquence à programmer =  1193 180 / Fréquence souhaitée
;

;
;
;
;PORT 43h :
;  bit 7,6 = (00) timer counter 0
; bit 5,4 = (11) write LSB then MSB
; bit 3-1 = (011) generate square wave
; bit 0 = (0) binary counter
;*/



 global Initialisation_8253




Initialisation_8253:
    push EBP
    MOV  EBP,ESP
    cli
    mov	AL,0x36
    out	0x43,AL
    jmp	Initialisation_8253_Suite_1

Initialisation_8253_Suite_1:
   MOV  CX,[EBP+0x08]
;//mov cx,65535
    mov	AL,CL	    
    out	0x40,AL
    jmp	Initialisation_8253_Suite_2

Initialisation_8253_Suite_2:
    mov	AL,CH	     
    out	0x40,AL
    jmp	Initialisation_8253_Suite_3

Initialisation_8253_Suite_3:

    pop EBP
 ;   sti

    ret






