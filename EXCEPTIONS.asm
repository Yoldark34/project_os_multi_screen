global Exception_Erreur_Division
global Exception_Mise_Au_Point
global Exception_INT3
global Exception_Debordement
global Exception_Limite
global Exception_CodeOP_Invalide
global Exception_DNA
global Exception_Double_Faute
global Exception_Depassement
global Exception_TSS_Invalide
global Exception_Segment_Non_Present
global Exception_Segment_Pile
global Exception_Violation_Protection
global Exception_Defaut_De_Page
global Exception_CoProcesseur

global Exception_Par_Defaut

;-------------------------------------------------------------------------------
extern CallBack_Erreur_Division
extern CallBack_Mise_Au_Point
extern CallBack_INT3
extern CallBack_Debordement
extern CallBack_Limite
extern CallBack_CodeOP_Invalide
extern CallBack_DNA
extern CallBack_Double_Faute
extern CallBack_Depassement
extern CallBack_TSS_Invalide
extern CallBack_Segment_Non_Present
extern CallBack_Segment_Pile
extern CallBack_Violation_Protection
extern CallBack_Defaut_De_Page
extern CallBack_CoProcesseur


extern CallBack_Exception_Par_Defaut


;###############################################################################
%macro	SAUVEGARDE_REGISTRES 0
	pushad 
	push ds
	push es
	push fs
	push gs 
%endmacro
;-------------------------------------------------------------------------------
%macro	RESTAURE_REGISTRES 0
	pop gs
	pop fs
	pop es
	pop ds
	popad
%endmacro
;-------------------------------------------------------------------------------



;###############################################################################
Exception_Erreur_Division: ; EXCEPTION TYPE ERREUR
  SAUVEGARDE_REGISTRES  
  mov ebx,esp    ; ebx contient la valeur de esp courante. Les push ont empilés 48 octets
  add ebx,48    ; Mettre dans ebx le pointeur de pile contenant l'adresse de l'instruction en ERREUR
  push ebx 
    call CallBack_Erreur_Division
  pop ebx
  RESTAURE_REGISTRES
  iret

;-------------------------------------------------------------------------------
Exception_Mise_Au_Point:    ; EXCEPTION TYPE "Trap"
 SAUVEGARDE_REGISTRES  
  mov ebx,esp    ; ebx contient la valeur de esp courante. Les push ont empilés 48 octets
  add ebx,48    ; Mettre dans ebx le pointeur de pile contenant l'adresse de l'instruction APRES le trap
  push ebx 
    call CallBack_Mise_Au_Point
  pop ebx
  RESTAURE_REGISTRES
  iret

;-------------------------------------------------------------------------------
Exception_INT3:  ; EXCEPTION TYPE "Trap"
SAUVEGARDE_REGISTRES  
  mov ebx,esp    ; ebx contient la valeur de esp courante. Les push ont empilés 48 octets
  add ebx,48    ; Mettre dans ebx le pointeur de pile contenant l'adresse de l'instruction APRES le trap
  push ebx 
    call CallBack_INT3
  pop ebx
  RESTAURE_REGISTRES
  iret

;-------------------------------------------------------------------------------
Exception_Debordement:  ; EXCEPTION TYPE "Trap"
SAUVEGARDE_REGISTRES  
  mov ebx,esp    ; ebx contient la valeur de esp courante. Les push ont empilés 48 octets
  add ebx,48    ; Mettre dans ebx le pointeur de pile contenant l'adresse de l'instruction APRES le trap
  push ebx 
    call CallBack_Debordement
  pop ebx
  RESTAURE_REGISTRES
  iret

;-------------------------------------------------------------------------------
Exception_Limite: ; EXCEPTION TYPE ERREUR
  SAUVEGARDE_REGISTRES  
  mov ebx,esp    ; ebx contient la valeur de esp courante. Les push ont empilés 48 octets
  add ebx,48    ; Mettre dans ebx le pointeur de pile contenant l'adresse de l'instruction en ERREUR
  push ebx 
    call CallBack_Limite
  pop ebx
  RESTAURE_REGISTRES
  iret

;-------------------------------------------------------------------------------
Exception_CodeOP_Invalide: ; EXCEPTION TYPE ERREUR
  SAUVEGARDE_REGISTRES  
  mov ebx,esp    ; ebx contient la valeur de esp courante. Les push ont empilés 48 octets
  add ebx,48    ; Mettre dans ebx le pointeur de pile contenant l'adresse de l'instruction en ERREUR
  push ebx 
    call CallBack_CodeOP_Invalide
  pop ebx
  RESTAURE_REGISTRES
  iret

;-------------------------------------------------------------------------------
Exception_DNA: ; EXCEPTION TYPE ERREUR
  SAUVEGARDE_REGISTRES  
  mov ebx,esp    ; ebx contient la valeur de esp courante. Les push ont empilés 48 octets
  add ebx,48    ; Mettre dans ebx le pointeur de pile contenant l'adresse de l'instruction en ERREUR
  push ebx 
    call CallBack_DNA
  pop ebx
  RESTAURE_REGISTRES
  iret

;-------------------------------------------------------------------------------
Exception_Double_Faute:   ; EXCEPTION TYPE "Trap"
  SAUVEGARDE_REGISTRES  
  mov ebx,esp    ; ebx contient la valeur de esp courante. Les push ont empilés 48 octets
  add ebx,48    ; Mettre dans ebx le pointeur de pile contenant l'adresse de l'instruction APRES le trap
  push ebx 
    call CallBack_Double_Faute
  pop ebx
  RESTAURE_REGISTRES
  iret

;-------------------------------------------------------------------------------
Exception_Depassement: ; EXCEPTION TYPE ERREUR
  SAUVEGARDE_REGISTRES  
  mov ebx,esp    ; ebx contient la valeur de esp courante. Les push ont empilés 48 octets
  add ebx,48    ; Mettre dans ebx le pointeur de pile contenant l'adresse de l'instruction en ERREUR
  push ebx 
    call CallBack_Depassement
  pop ebx
  RESTAURE_REGISTRES
  iret

;-------------------------------------------------------------------------------
Exception_TSS_Invalide: ; EXCEPTION TYPE ERREUR
  SAUVEGARDE_REGISTRES  
  mov ebx,esp    ; ebx contient la valeur de esp courante. Les push ont empilés 48 octets
  add ebx,48    ; Mettre dans ebx le pointeur de pile contenant l'adresse de l'instruction en ERREUR
  push ebx 
    call CallBack_TSS_Invalide
  pop ebx
  RESTAURE_REGISTRES
  iret

;-------------------------------------------------------------------------------
Exception_Segment_Non_Present: ; EXCEPTION TYPE ERREUR
  SAUVEGARDE_REGISTRES  
  mov ebx,esp    ; ebx contient la valeur de esp courante. Les push ont empilés 48 octets
  add ebx,48    ; Mettre dans ebx le pointeur de pile contenant l'adresse de l'instruction en ERREUR
  push ebx 
    call CallBack_Segment_Non_Present
  pop ebx
  RESTAURE_REGISTRES
  iret

;-------------------------------------------------------------------------------
Exception_Segment_Pile: ; EXCEPTION TYPE ERREUR
  SAUVEGARDE_REGISTRES  
  mov ebx,esp    ; ebx contient la valeur de esp courante. Les push ont empilés 48 octets
  add ebx,48    ; Mettre dans ebx le pointeur de pile contenant l'adresse de l'instruction en ERREUR
  push ebx 
    call CallBack_Segment_Pile
  pop ebx
  RESTAURE_REGISTRES
  iret

;-------------------------------------------------------------------------------
Exception_Violation_Protection: ; EXCEPTION TYPE ERREUR
  SAUVEGARDE_REGISTRES  
  mov ebx,esp    ; ebx contient la valeur de esp courante. Les push ont empilés 48 octets
  add ebx,48    ; Mettre dans ebx le pointeur de pile contenant l'adresse de l'instruction en ERREUR
  push ebx 
    call CallBack_Violation_Protection
  pop ebx
  RESTAURE_REGISTRES
  iret

;-------------------------------------------------------------------------------
Exception_Defaut_De_Page: ; EXCEPTION TYPE ERREUR
  SAUVEGARDE_REGISTRES  
  mov ebx,esp    ; ebx contient la valeur de esp courante. Les push ont empilés 48 octets
  add ebx,48    ; Mettre dans ebx le pointeur de pile contenant l'adresse de l'instruction en ERREUR
  push ebx 
    call CallBack_Defaut_De_Page
  pop ebx
  RESTAURE_REGISTRES
  iret

;-------------------------------------------------------------------------------
Exception_CoProcesseur: 
 SAUVEGARDE_REGISTRES  
  mov ebx,esp    ; ebx contient la valeur de esp courante. Les push ont empilés 48 octets
  add ebx,48    ; Mettre dans ebx le pointeur de pile contenant l'adresse de l'instruction en ERREUR
  push ebx 
    call CallBack_CoProcesseur
  pop ebx
  RESTAURE_REGISTRES
  iret

;-------------------------------------------------------------------------------
Exception_Par_Defaut:
  SAUVEGARDE_REGISTRES  
  mov ebx,esp    ; ebx contient la valeur de esp courante. Les push ont empilés 48 octets
  add ebx,48    ; Mettre dans ebx le pointeur de pile contenant l'adresse de l'instruction en ERREUR
  push ebx 
    call CallBack_Exception_Par_Defaut
  pop ebx
  RESTAURE_REGISTRES
  iret

