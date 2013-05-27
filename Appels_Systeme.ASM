


global Appel_Systeme_Video
global Appel_Systeme_Clavier

extern CallBack_INT_Video
extern CallBack_INT_Clavier

;-------------------------------------------------------------------------------
%macro SAUVEGARDE_AVANT_APPEL 0
    pushad    ;Push EAX, ECX, EDX, EBX, original ESP, EBP, ESI, and EDI
    push DS
    push ES
    push FS
    push GS
%endmacro

;-------------------------------------------------------------------------------
%macro RESTITUTION_APRES_APPEL 0
    pop GS
    pop FS
    pop ES
    pop DS
    popad
%endmacro
;-------------------------------------------------------------------------------

Appel_Systeme_Video:
SAUVEGARDE_AVANT_APPEL

  push ecx
  push ebx
  push eax  
  call CallBack_INT_Video
  pop eax
  pop ebx
  pop ecx


RESTITUTION_APRES_APPEL
  iret


Appel_Systeme_Clavier:

  push ebx  ; sauvegarde de ebx
  push eax  ; on empile le paramètre
  call CallBack_INT_Clavier  ; le code scan sera stocké dans al
  pop ebx  ; on dépile le paramètre
  pop ebx  ; restitution de ebx
  iret  ; dans al il y a le code scan

