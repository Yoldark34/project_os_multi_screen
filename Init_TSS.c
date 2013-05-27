#include "Descripteurs.h"
#include "PLAN_MEMOIRE.h"
#include "MACRO.h"

//------------------------------------------------------------------------------
// Variables globale
//------------------------------------------------------------------------------
T_SEGMENT_TSS Le_TSS;
//------------------------------------------------------------------------------

void Initialisation_TSS()
{
T_DESCRIPTEUR_SEGMENT* L_Descripteurs_Segment=(T_DESCRIPTEUR_SEGMENT*)ADRESSE_DESCRIPTEURS_SEGMENTS;

   Initialise_Memoire((BYTE*)&Le_TSS,0,sizeof(T_SEGMENT_TSS)); 
   Le_TSS.SS0=SELECTEUR_STACK_NOYAU;
   Le_TSS.ESP0=HAUT_STACK_NOYAU_TACHE_0;
   
   Le_TSS.SS=SELECTEUR_STACK_USER;
   Le_TSS.CS=SELECTEUR_CODE_USER;
   Le_TSS.DS=SELECTEUR_DATA_USER;
   Le_TSS.Mode_Debug= 0x00;  
   Le_TSS.Autorisation_E_S=0x000;
   
 
   Configure_Descripteur_Segment(&L_Descripteurs_Segment[INDEX_DESCRIPTEUR_TSS],           // Segment du TSS
                                  (UINT32)&Le_TSS,sizeof(T_SEGMENT_TSS)-1,          // Base :son adresse Limite : sa taille -1
                                  SYSTEM_TSS_386_DISPONIBLE,      // Type : TSS 386
                                  0,                         // bit DT Segment system donc DT =0
                                  RING_3,                         // Privilege 
                                  1,                         // bit P est présent donc valide pour la translation d'adresses
                                  1,                         // bit AVL à usage privé ... donc ne sert à rien sauf si on veut ...
                                  0,                         // bit O à 0
                                  1,                         // bit D  toujours à 1 (instruction par défaut sur 32 bits) les i286 pêuvent mettre à 0
                                  0);                        // bit G granularité de la limite à 4Ko (et non pas 1 octet)
  
    
   INITIALISER_REGISTRE_LDTR(SELECTEUR_TSS);
   

}

