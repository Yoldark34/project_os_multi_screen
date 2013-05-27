#include "Processus.h"
#include "PLAN_MEMOIRE.h"
#include "Outils.h"
#include "MACRO.h"
#include "Ecran.h"

//##############################################################################
//  VARIABLE GLOBALE
//##############################################################################
/*
T_INFO_PROCESSUS* Liste_Processus_Actifs=0;
UINT32 Nombre_Processus_Actifs=0;


*/

//##############################################################################





void Initialisation_Info_Processus()
{
UINT16 L_Index;    
    for (L_Index=0; L_Index <NOMBRE_MAXI_PROCESSUS; L_Index++){
       // ((T_INFO_PROCESSUS*)ADRESSE_BASE_INFO_PROCESS)[L_Index].Nom[0]=0;
       // ((T_INFO_PROCESSUS*)ADRESSE_BASE_INFO_PROCESS)[L_Index].PID=0;
        ((T_INFO_PROCESSUS*)ADRESSE_INFO_PROCESS)[L_Index].Etat=MORT;
        ((T_INFO_PROCESSUS*)ADRESSE_INFO_PROCESS)[L_Index].Registres.CR3=Donne_Adresse_Tables_Pages_Process(L_Index);       
    }


}
//------------------------------------------------------------------------------
T_INFO_PROCESSUS* Donne_Info_Processus(UINT32 P_Numero_Process)
{
    return ( (T_INFO_PROCESSUS*)(ADRESSE_INFO_PROCESS+(P_Numero_Process *sizeof(T_INFO_PROCESSUS))) ); 
}
//------------------------------------------------------------------------------



//=============================================================================
void Charge_Processus(UINT32 P_Numero_Process, UINT32 P_Adresse_Code, UINT32 P_Taille_Code)
{
T_INFO_PROCESSUS* L_Info_Processus=(T_INFO_PROCESSUS*) (ADRESSE_INFO_PROCESS + (P_Numero_Process*sizeof(T_INFO_PROCESSUS)) );
UINT32 L_Adresse_Tables_Process = Donne_Adresse_Tables_Pages_Process(P_Numero_Process);  


   Allouer_Pages(L_Adresse_Tables_Process,ADRESSE_CONTEXTE_PROCESS, P_Taille_Code );   
   Allouer_Pages(L_Adresse_Tables_Process,HAUT_STACK_USER - ((NOMBRE_PAGE_STACK_USER-1)<<12) , NOMBRE_PAGE_STACK_USER ); 
  
    L_Info_Processus->Registres.SS=(SELECTEUR_STACK_USER+RING_3); 
    L_Info_Processus->Registres.ESP=HAUT_STACK_USER-4;  
    L_Info_Processus->Registres.Eflags =0x200;
    L_Info_Processus->Registres.CS=(SELECTEUR_CODE_USER+RING_3);   
    // Attention l'adresse du code EIP est relative au début du segment code de l'application
    L_Info_Processus->Registres.EIP=ADRESSE_CODE_PROCESS-BASE_CODE_USER ;   

    L_Info_Processus->Registres.EAX=0; 
    L_Info_Processus->Registres.ECX=0;   
    L_Info_Processus->Registres.EDX=0;   
    L_Info_Processus->Registres.EBX=0;
    L_Info_Processus->Registres.ESP_Noyau=0;
    L_Info_Processus->Registres.EBP=HAUT_STACK_USER-4;   
    L_Info_Processus->Registres.ESI=0;
    L_Info_Processus->Registres.EDI=0;

    L_Info_Processus->Registres.DS=(SELECTEUR_DATA_USER+RING_3); 
    L_Info_Processus->Registres.ES=(SELECTEUR_DATA_USER+RING_3); 
    L_Info_Processus->Registres.FS=(SELECTEUR_DATA_USER+RING_3); 
    L_Info_Processus->Registres.GS=(SELECTEUR_DATA_USER+RING_3); 

    L_Info_Processus->Registres.SS0  = SELECTEUR_STACK_NOYAU;
    L_Info_Processus->Registres.ESP0 =  HAUT_STACK_NOYAU_TACHE_0 - (1024*P_Numero_Process);

    L_Info_Processus->Etat=BLOQUE;
    L_Info_Processus->Registres.CR3 = L_Adresse_Tables_Process;  

   INITIALISER_REGISTRE_CR3_VAR(L_Adresse_Tables_Process);    
     Copier_Memoire((BYTE*)ADRESSE_CONTEXTE_PROCESS, (BYTE*)P_Adresse_Code, (P_Taille_Code<<12) );    
   INITIALISER_REGISTRE_CR3_CONST(ADRESSE_REPERTOIRE_PAGES_OS);        
}

//=============================================================================

void Copier_Memoire_Process(UINT32 P_Numero_Process,BYTE* P_Destination, BYTE* P_Source, UINT32 P_Taille)
{
 UINT32 L_Adresse_Tables_Process = Donne_Adresse_Tables_Pages_Process(P_Numero_Process);  
  INITIALISER_REGISTRE_CR3_VAR(L_Adresse_Tables_Process);    
     Copier_Memoire(P_Destination, P_Source, P_Taille );    
   INITIALISER_REGISTRE_CR3_CONST(ADRESSE_REPERTOIRE_PAGES_OS);   
}
