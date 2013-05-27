global Interruption_IRQ0;
global Interruption_IRQ1;
global Interruption_IRQ3;
global Interruption_IRQ4;
global Interruption_IRQ5;
global Interruption_IRQ6;
global Interruption_IRQ7;
global Interruption_IRQ8;
global Interruption_IRQ9;
global Interruption_IRQ10;
global Interruption_IRQ11;
global Interruption_IRQ12;
global Interruption_IRQ13;
global Interruption_IRQ14;
global Interruption_IRQ15;

global Interruption_IRQ_Defaut;

extern CallBack_IRQ0
extern CallBack_IRQ1
extern CallBack_IRQ3
extern CallBack_IRQ4
extern CallBack_IRQ5
extern CallBack_IRQ6
extern CallBack_IRQ7
extern CallBack_IRQ8
extern CallBack_IRQ9
extern CallBack_IRQ10
extern CallBack_IRQ11
extern CallBack_IRQ12
extern CallBack_IRQ13
extern CallBack_IRQ14
extern CallBack_IRQ15

extern CallBack_Defaut

;###############################################################################

%macro SAUVEGARDE_AVANT_INTERRUPTION 0
    pushad
    push DS
    push ES
    push FS
    push GS
%endmacro

;--------------------------------------

%macro RESTITUTION_APRES_INTERRUPTION 0
    pop GS
    pop FS
    pop ES
    pop DS
    popad
%endmacro

;-----------------------------------------
%macro FIN_INTERRUPTION 0
    mov al,0x20
    out 0x20,al
%endmacro

;###############################################################################
Interruption_IRQ0:
        SAUVEGARDE_AVANT_INTERRUPTION
        call CallBack_IRQ0
        FIN_INTERRUPTION
        RESTITUTION_APRES_INTERRUPTION 
        iret

;-----------------------------------------------------------------------------
Interruption_IRQ1:
       
        SAUVEGARDE_AVANT_INTERRUPTION
        call CallBack_IRQ1
        FIN_INTERRUPTION
        RESTITUTION_APRES_INTERRUPTION 
        iret
;----------------------------------------------------------
Interruption_IRQ3:
        SAUVEGARDE_AVANT_INTERRUPTION
        call CallBack_IRQ3
        FIN_INTERRUPTION
        RESTITUTION_APRES_INTERRUPTION 
        iret

;-----------------------------------------------------------------------------
Interruption_IRQ4:
        SAUVEGARDE_AVANT_INTERRUPTION
	call CallBack_IRQ4
        FIN_INTERRUPTION
        RESTITUTION_APRES_INTERRUPTION 
        iret

;-----------------------------------------------------------------------------
Interruption_IRQ5:
        SAUVEGARDE_AVANT_INTERRUPTION
	call CallBack_IRQ5
        FIN_INTERRUPTION
        RESTITUTION_APRES_INTERRUPTION 
        iret

;-----------------------------------------------------------------------------
Interruption_IRQ6:
        SAUVEGARDE_AVANT_INTERRUPTION
	call CallBack_IRQ6
        FIN_INTERRUPTION
        RESTITUTION_APRES_INTERRUPTION 
        iret
;-----------------------------------------------------------------------------
Interruption_IRQ7:
        SAUVEGARDE_AVANT_INTERRUPTION
	call CallBack_IRQ7
        FIN_INTERRUPTION
        RESTITUTION_APRES_INTERRUPTION 
        iret
;-----------------------------------------------------------------------------
Interruption_IRQ8:
        SAUVEGARDE_AVANT_INTERRUPTION
	call CallBack_IRQ8
        FIN_INTERRUPTION
        RESTITUTION_APRES_INTERRUPTION 
        iret

;-----------------------------------------------------------------------------
Interruption_IRQ9:
  SAUVEGARDE_AVANT_INTERRUPTION
	call CallBack_IRQ9
        FIN_INTERRUPTION
        RESTITUTION_APRES_INTERRUPTION 
        iret

;-----------------------------------------------------------------------------
Interruption_IRQ10:
        SAUVEGARDE_AVANT_INTERRUPTION
	call CallBack_IRQ10
        FIN_INTERRUPTION
        RESTITUTION_APRES_INTERRUPTION 
        iret

;-----------------------------------------------------------------------------
Interruption_IRQ11:
        SAUVEGARDE_AVANT_INTERRUPTION
	call CallBack_IRQ11
        FIN_INTERRUPTION
        RESTITUTION_APRES_INTERRUPTION 
        iret

;-----------------------------------------------------------------------------
Interruption_IRQ12:
        SAUVEGARDE_AVANT_INTERRUPTION
	call CallBack_IRQ12
        FIN_INTERRUPTION
        RESTITUTION_APRES_INTERRUPTION 
        iret

;-----------------------------------------------------------------------------
Interruption_IRQ13:
        SAUVEGARDE_AVANT_INTERRUPTION
	call CallBack_IRQ13
        FIN_INTERRUPTION
        RESTITUTION_APRES_INTERRUPTION 
        iret

;-----------------------------------------------------------------------------
Interruption_IRQ14:
        SAUVEGARDE_AVANT_INTERRUPTION
	call CallBack_IRQ14
        FIN_INTERRUPTION
        RESTITUTION_APRES_INTERRUPTION 
        iret

;-----------------------------------------------------------------------------
Interruption_IRQ15:
        SAUVEGARDE_AVANT_INTERRUPTION
	call CallBack_IRQ15
        FIN_INTERRUPTION
        RESTITUTION_APRES_INTERRUPTION 
        iret


;-----------------------------------------------------------------------------
Interruption_Defaut:
        SAUVEGARDE_AVANT_INTERRUPTION
        call CallBack_Defaut
        FIN_INTERRUPTION
        RESTITUTION_APRES_INTERRUPTION 
        iret











