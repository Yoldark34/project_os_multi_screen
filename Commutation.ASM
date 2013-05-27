global Commuter_Processus

; dans process-> contexte : GS, FS, ES, DS, EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX,
; EIP, CS, Eflags, ESP_OS, SS

Commuter_Processus :
    
    pop esi   ;adresse du contexte
    pop ebx   ; repertoire de tables de pages
    ; 0008:00x0100833
  ;---------- pour la communtation de tache

; si on est en mode noyau, il ne faut pas empiller SS et ESP
   mov eax,[esi+52]
   cmp eax, 0x08
   je .FIN_SI 
    push dword [esi+64] ; SS
    push dword [esi+60];  ESP
.FIN_SI : 

    pushf
    pop eax
    or eax,0x200 ;
    and eax, 0xffffbfff
    push eax
    push dword [esi+52] ; CS
    push dword [esi+48]; EIP
 
   
;----------------- pour restituer le contexte processeur
   push dword [esi]   ; GS
   push dword [esi+4] ; FS
   push dword [esi+8] ; ES
   push dword [esi+12] ; DS
   push dword [esi+16] ; EDI
   push dword [esi+20] ; ESI
   push dword [esi+24] ; EBP
   push dword [esi+32] ; EBX
   push dword [esi+36] ; EDX
   push dword [esi+40] ;ECX
   push dword [esi+44]; EAX
;--------------------------------
    mov al, 0x20           
    out 0x20, al
 
    mov cr3, ebx

;------- restaurer le contexte
     pop eax
     pop ecx
     pop edx
     pop ebx
     pop ebp
     pop esi
     pop edi
     pop ds
     pop ES
     pop FS
     pop GS
 
;-- en pile il doit rester : 
;   eip, selecteur stack noyau, flags
    iret



