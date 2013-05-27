
#ifndef MACRO_H
#define	MACRO_H

#define VALEUR_DE(P_Valeur) #P_Valeur

#define SAUT_ALIGNE(Selecteur) asm volatile  (".intel_syntax noprefix "); \
                               asm volatile  ("jmp "VALEUR_DE(Selecteur)":Suivant"); \
                               asm volatile  ( "Suivant: "); \
                               asm volatile  (".att_syntax noprefix \n");
 
#define INITIALISER_REGISTRE_GDTR(ADRESSE_GDT) \
                               asm volatile (".intel_syntax noprefix "); \
                               asm volatile ("lgdt "VALEUR_DE(ADRESSE_GDT));\
                               asm volatile (".att_syntax noprefix \n");




#define INITIALISER_REGISTRE_IDTR(ADRESSE_IDT) asm volatile  (".intel_syntax noprefix"); \
                                               asm volatile  ("lidt "VALEUR_DE(ADRESSE_IDT));\
                                               asm volatile  (".att_syntax noprefix");


#define INITIALISER_REGISTRE_LDTR(Selecteur_TSS) asm volatile  (".intel_syntax noprefix "); \
                                    asm volatile  ("mov ax,"VALEUR_DE(Selecteur_TSS)); \
                                    asm volatile  ("ltr ax"); \
                                    asm volatile  (".att_syntax noprefix \n");


#define INITIALISER_REGISTRES_SEGMENTS_DATA(Selecteur) \
                                 asm volatile  (".intel_syntax noprefix "); \
                                 asm volatile  (" mov AX,"VALEUR_DE(Selecteur));    \
                                 asm volatile  (" mov DS,AX"); \
                                 asm volatile  (" mov ES,AX"); \
                                 asm volatile  (" mov FS,AX"); \
                                 asm volatile  (" mov GS,AX"); \
                                 asm volatile  (".att_syntax noprefix \n");

#define INITIALISE_SS_ESP(Selecteur, Limite) \
                                 asm volatile  (".intel_syntax noprefix"); \
                                 asm volatile  (" mov AX,"VALEUR_DE(Selecteur));    \
                                 asm volatile  (" mov SS,AX");     \
                                 asm volatile  (" mov ESP,"VALEUR_DE(Limite)); \
                                 asm volatile  (".att_syntax noprefix");

#define INITIALISER_DS(Selecteur) asm volatile  (".intel_syntax noprefix "); \
                                  asm volatile  (" mov AX,"VALEUR_DE(Selecteur));    \
                                  asm volatile  (" mov DS,AX"); \
                                  asm volatile  (".att_syntax noprefix \n");

#define INITIALISER_REGISTRE_CR3_CONST(Adresse_Repertoire_Table) \
                                 asm volatile  (".intel_syntax noprefix "); \
                                 asm volatile ( "mov eax,"VALEUR_DE(Adresse_Repertoire_Table)); \
                                 asm volatile  ("mov cr3, eax"); \
                                 asm volatile  (".att_syntax noprefix \n");

#define INITIALISER_REGISTRE_CR3_VAR(Adresse_Repertoire_Table) \
                                 asm volatile ( "mov %0,%%eax"::"m"(Adresse_Repertoire_Table)); \
                                 asm volatile  ("mov %eax,%cr3"); 



#define ACTIVER_PAGINATION       asm volatile  (".intel_syntax noprefix "); \
                                 asm volatile  (" mov eax,cr0"); \
                                 asm volatile  ("or eax, 0x80000000"); \
                                 asm volatile  ("mov cr0,eax"); \
                                 asm volatile  (".att_syntax noprefix \n");



#define MOV(Registre, Valeur)  asm volatile  (".intel_syntax noprefix "); \
                               asm volatile  (" mov " VALEUR_DE(Registre) "," VALEUR_DE(Valeur) ); \
                               asm volatile  (".att_syntax noprefix \n");
 
#define OUT(Port, Valeur)      asm volatile  (".intel_syntax noprefix "); \
                               asm volatile  (" mov dx," VALEUR_DE(Port)); \
                               asm volatile  (" mov al," VALEUR_DE(Valeur)); \
                               asm volatile  (" out dx,al"); \
                               asm volatile  (".att_syntax noprefix \n");

#define OUT_PAUSE(Port,Valeur) asm volatile  (".intel_syntax noprefix"); \
                               asm volatile  ("mov al," VALEUR_DE(Valeur)); \
                               asm volatile  ("out " VALEUR_DE(Port) ",al"); \
                               asm volatile  ("jmp  $+2 "); \
                               asm volatile  (" .att_syntax noprefix \n");
 
#define PUSHALL               asm volatile  (".intel_syntax noprefix "); \
                              asm volatile  ("pushad "); \
                              asm volatile  ("push DS"); \
                              asm volatile  ("push ES"); \
                              asm volatile  ("push FS"); \
                              asm volatile  ("push GS"); \
                              asm volatile  (".att_syntax noprefix \n");
 
#define POPALL                asm volatile  (".intel_syntax noprefix"); \
                              asm volatile  ("pop GS "); \
                              asm volatile  ("pop FS "); \
                              asm volatile  ("pop ES "); \
                              asm volatile  ("pop DS "); \
                              asm volatile  ("popad "); \
                              asm volatile  (".att_syntax noprefix \n");  

#define HALT     asm volatile  (".intel_syntax noprefix ");   \
                 asm volatile ("hlt"); \
                 asm volatile  (".att_syntax noprefix \n"); 

#define STI      asm volatile  (".intel_syntax noprefix ");   \
                 asm volatile ("sti"); \
                 asm volatile  (".att_syntax noprefix \n"); 
#define AUTORISE_INTERRUPTION STI


#define CLI      asm volatile  (".intel_syntax noprefix ");   \
                 asm volatile ("cli"); \
                 asm volatile  (".att_syntax noprefix \n"); 
#define INTERDIRE_INTERRUPTION CLI


#endif	/* MACRO_H */

