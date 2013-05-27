#include "Outils.h"
#include "MACRO.h"


/*
 *
  RAPPEL :
 *
 *
 *  Maitre :Port 0X20- 0X21
--------------------
IRQ 0 (INT 20h) → Horloge             Esclave : port 0xA0-0xA1
IRQ 1 (INT 21h) → Clavier          -------------------------------
IRQ 2 ────────────────────────────	IRQ 8 (INT 70h) CMOS
IRQ 3 (INT 23h) → COM 2		    	IRQ 9 (INT 71h) Remplace IRQ 2
IRQ 4 (INT 24h) → COM 1             IRQ A (INT 72h) Synchro verticale
IRQ 5 (INT 25h) → LPT 2             IRQ B (INT 73h) -
IRQ 6 (INT 26h) → Disquette         IRQ C (INT 74h) Réseau
IRQ 7 (INT 27h) → LPT 1             IRQ D (INT 75h) Coprocesseur Math.
                                    IRQ E (INT 76h) Disque Dur
                                    IRQ F (INT 77h) –

 *
 *  ICW1
 *    D7                   D0
     +--+--+--+--+--+--+--+--+
     | 0| 0| 0| 1| A| 0| B| C|
     +--+--+--+--+--+--+--+--+
                   ^
debut de           |
sequence ----------+
A = 1 : declenchement par niveau; 0: par front
B = 1 : seul ; 0: cascade
C = 1 : présence du registre ICW4 ; 0:sans

ICW2
         D7                   D0
        +--+--+--+--+--+--+--+--+
        |              | 0| 0| 0|
        +--+--+--+--+--+--+--+--+
                 ^
                 |
                 |
       valeurs du vecteur

ICW3 Maitre :
     D7                   D0
    +--+--+--+--+--+--+--+--+
    |                       |
    +--+--+--+--+--+--+--+--+
                ^
       1 : entree esclave 0: non

ICW3 Esclave :
     D7                   D0
    +--+--+--+--+--+--+--+--+
    | ------------ |        |
    +--+--+--+--+--+--+--+--+
                       ^
        1 : entree esclave 0: non


ICW4
    D7                   D0
    +--+--+--+--+--+--+--+--+
    | -------| A| B| C| D| E|
    +--+--+--+--+--+--+--+--+

A = 1 : interruption emboitables complet;  0: partiel
B = 1 : pilote un transmetteur  0: mode maitre/esclave
C = 1 : maitre   0: esclave
D = 1 : EOI automatique 0 : EOI normale
E = 1 : famille x86

 */

#define CTRL_8258A_Maitre  0x20  // registre 0x20 et 0x21
#define CTRL_8258A_Esclave 0xA0  // registre 0xA0 et 0xA1


#define  Configure_ICW_8258A(P_Port, P_ICW1, P_ICW2, P_ICW3, P_ICW4 ) \
                                OUT_PAUSE(P_Port, P_ICW1); \
                                OUT_PAUSE(P_Port+1, P_ICW2); \
                                OUT_PAUSE(P_Port+1, P_ICW3); \
                                OUT_PAUSE(P_Port+1, P_ICW4);  


void Inititialisation_8259A()
{
    Configure_ICW_8258A(CTRL_8258A_Maitre, 
                        0x11, // Il existe un registre ICW4
                        0x20, // les IRQ du maitre génèreront des INT de 20h à int 27h 
                        0X04, // un esclave est connecté sur le bit 2
                        0X01);// en mode Intel

    Configure_ICW_8258A(CTRL_8258A_Esclave,  
                        0x11, // Il existe un registre ICW4
                        0x70, // les IRQ du maitre génèreront des INT de 70h à int 77h 
                        0X02, // un esclave est connecté sur le bit 2
                        0X01);// en mode Intel
   
  OUT(CTRL_8258A_Maitre+1,  0x0);  // aucune interruption n'est masquée
  OUT(CTRL_8258A_Esclave+1, 0x0);
}

