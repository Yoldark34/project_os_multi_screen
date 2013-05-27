

#ifndef PROCESSUS_H
#define	PROCESSUS_H
#include "type.h"
#include "Descripteurs.h"

#define DEBUG_PROCESS



typedef enum {MORT=0,BLOQUE, ACTIF} T_ETAT_PROCESS;


#pragma pack(1)
typedef struct {
      //------------------ voir IRQ.ASM
         UINT32 GS;  //0
         UINT32 FS;  //1  +2
         UINT32 ES; // 2  +4 
         UINT32 DS; // 3  +6
        //------------- par PUSHAD
        UINT32 EDI;  //4  +8
        UINT32 ESI;  //5  +12
        UINT32 EBP;  //6  +16
        UINT32 ESP_Noyau;  //7  +20
        UINT32 EBX;  //8  +24   
        UINT32 EDX;  //9  +28 
        UINT32 ECX;  //10 +32
        UINT32 EAX;  //11 +36
         //------------ par l'interruption
        UINT32 EIP;  //12
        UINT32 CS;  //13
        UINT32 Eflags;   //14
        UINT32 ESP; //15
        UINT32 SS; //16    
        //................    
        UINT32 SS0;
    UINT32 ESP0;  
    UINT32 CR3;
}T_CONTEXTE_REGISTRES;
#pragma pack()

#define TAILLE_CONTEXTE_REGISTRE 48
#pragma pack(1)
typedef struct {
    // possibilité de rajouter des infos (nom, pid, ...)
    union {
      T_CONTEXTE_REGISTRES Registres;
      UINT32 Contexte_Registres[sizeof(T_CONTEXTE_REGISTRES)>>2];
    };

    T_ETAT_PROCESS Etat;
 }T_INFO_PROCESSUS;
#pragma pack()

//############################################################################## 
void Initialisation_Info_Processus();
T_INFO_PROCESSUS* Donne_Info_Processus(UINT32 P_Numero);
void Copier_Memoire_Process(UINT32 P_Numero_Process,BYTE* P_Destination, BYTE* P_Source, UINT32 P_Taille);
void Charge_Processus(UINT32 P_Numero_Process, UINT32 P_Adresse_Code, UINT32 P_Taille_Code);

 
 
#endif	/* PROCESSUS_H */


