#include "Processus.h"
#include "PLAN_MEMOIRE.h"
#include "MACRO.h"
#include "HARD_8042_Clavier.h"
#include "Outils.h"
#include "Init_TSS.h"
#include "Ordonnanceur.h"
#include "Ecran.h"

volatile UINT32 Periode_Ordonnanceur = 100L;
UINT32 Numero_Process_Courrant=0;
UINT32 Compteur_Tic_Ordonnanceur=0;



  
 void Ordonnanceur()
{ 
  UINT32* L_Pile=0;   
 asm volatile("mov %%ebp, %%eax; mov %%eax, %0" : "=m" (L_Pile) : );
 L_Pile +=2;  // Ignorer le EBP et le EIP générés par l'appel à cette fonction
 
 Compteur_Tic_Ordonnanceur++;
	if (Compteur_Tic_Ordonnanceur > Periode_Ordonnanceur) {
     Compteur_Tic_Ordonnanceur=0;
 //   
  T_INFO_PROCESSUS* L_Process_Actuel=(T_INFO_PROCESSUS*) (ADRESSE_INFO_PROCESS + (Numero_Process_Courrant*sizeof(T_INFO_PROCESSUS)) );
 

  
 #ifdef DEBUG_ORDONNANCEUR
  Efface_Ecran();
  Regle_Couleur(ROUGE); 
  Affiche_Chaine("[ORDONNANCEUR] ");
  Regle_Couleur(BLANC); 
  Affiche_Chaine("Proc: ");
  Affiche_Chaine(Entier_Vers_Chaine(Numero_Process_Courrant));
  Affiche_Chaine(" @Info Proc: ");
  Affiche_Chaine(Entier_Vers_Chaine_Hexa((UINT32)L_Process_Actuel,4));
  
  Affiche_Chaine(" Rep: ");
  Affiche_Chaine(Entier_Vers_Chaine_Hexa((UINT32)(L_Process_Actuel->Registres.CR3),4));  
  
  Affiche_Chaine(" Pile: ");
  Affiche_Chaine(Entier_Vers_Chaine_Hexa((UINT32)L_Pile,4)); 
  
  Affiche_Chaine(" Taille: ");
  Affiche_Chaine(Entier_Vers_Chaine(sizeof(T_CONTEXTE_REGISTRES))); 
  
/*
  if (L_Pile[12]==SELECTEUR_CODE_NOYAU) {
       Affiche_Chaine("\n Process Systeme ");
  } else {
      Affiche_Chaine("\n Process User ");
  }
*/
  
 Affiche_Chaine("\nPile: GS, FS, ES, DS, EDI, ESI, EBP, ESP_N, EBX, EDX, ECX, EAX, EIP, CS, flags, ESP, SS \n");
#endif



  Copier_Memoire((BYTE*)L_Process_Actuel->Contexte_Registres, (BYTE*)L_Pile, TAILLE_CONTEXTE_REGISTRE);//18*sizeof(UINT32));
  
  
      // si c'est un process du noyau, l'int n'a pas alimenté la pile avec SS et ESP
    // les valeurs stockées dans le contexte sont donc fausses


  if (L_Process_Actuel->Registres.CS == SELECTEUR_CODE_NOYAU){
      L_Process_Actuel->Registres.ESP=L_Process_Actuel->Registres.ESP_Noyau;
      L_Process_Actuel->Registres.SS=Le_TSS.SS0;
   }  
  
   L_Process_Actuel->Registres.SS0 = Le_TSS.SS0;
   L_Process_Actuel->Registres.ESP0 = Le_TSS.ESP0;
  
 #ifdef DEBUG_ORDONNANCEUR
Affiche_Caractere('\n');
int L_Index;
 for (L_Index=0; L_Index<20; L_Index++) {
  Affiche_Chaine(Entier_Vers_Chaine(L_Index));
  Affiche_Chaine(": ");
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(((UINT32*)&L_Process_Actuel->Registres)[L_Index],4));
  Affiche_Chaine(";  ");
 }
  Affiche_Chaine("\nEIP : "); 
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Process_Actuel->Registres.EIP ,4)); 
  Affiche_Chaine("\nDS : "); 
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Process_Actuel->Registres.DS ,4)); 
  Affiche_Chaine("   ES : "); 
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Process_Actuel->Registres.ES ,4)); 
  Affiche_Chaine("   FS : "); 
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Process_Actuel->Registres.FS ,4)); 
  Affiche_Chaine("  GS : "); 
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Process_Actuel->Registres.GS ,4)); 
  Affiche_Chaine("\nEAX : "); 
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Process_Actuel->Registres.EAX ,4));   
  Affiche_Chaine("\nESP0 : "); 
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Process_Actuel->Registres.ESP ,4));   
  Affiche_Chaine("  SS : "); 
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Process_Actuel->Registres.SS ,4)); 
  
  
 #endif


L_Process_Actuel->Etat=BLOQUE;

  do {    
      Numero_Process_Courrant++;
      L_Process_Actuel++;
      if (Numero_Process_Courrant>=NOMBRE_MAXI_PROCESSUS){
          Numero_Process_Courrant=0;
         L_Process_Actuel=(T_INFO_PROCESSUS*) (ADRESSE_INFO_PROCESS); 
      }    
  } while (L_Process_Actuel->Etat !=BLOQUE);
  
 
  #ifdef DEBUG_ORDONNANCEUR
      Affiche_Chaine("\n\n\nProchain proc: ");
      Affiche_Chaine(Entier_Vers_Chaine(Numero_Process_Courrant));
      Affiche_Chaine(" Rep: ");
      Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Process_Actuel->Registres.CR3,4)); 
      Affiche_Caractere('\n');
 
  Affiche_Caractere('\n');
 for (L_Index=0; L_Index<20; L_Index++) {
  Affiche_Chaine(Entier_Vers_Chaine(L_Index));
  Affiche_Chaine(": ");
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(((UINT32*)&L_Process_Actuel->Registres)[L_Index],4));
  Affiche_Chaine(";  ");
 }

   Affiche_Chaine("\nEIP : "); 
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Process_Actuel->Registres.EIP ,4)); 
  Affiche_Chaine("\nDS : "); 
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Process_Actuel->Registres.DS ,4)); 
  Affiche_Chaine("   ES : "); 
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Process_Actuel->Registres.ES ,4)); 
  Affiche_Chaine("   FS : "); 
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Process_Actuel->Registres.FS ,4)); 
  Affiche_Chaine("  GS : "); 
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Process_Actuel->Registres.GS ,4)); 
  Affiche_Chaine("\nEAX : "); 
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Process_Actuel->Registres.EAX ,4));   
  Affiche_Chaine("\nESP0 : "); 
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Process_Actuel->Registres.ESP ,4));   
  Affiche_Chaine("  SS : "); 
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Process_Actuel->Registres.SS ,4)); 
   
 #endif
      UINT32* L_Repertoire_Page=(UINT32*)L_Process_Actuel->Registres.CR3;
      UINT32* L_Contexte =(UINT32*)(L_Process_Actuel->Contexte_Registres);
      
    L_Process_Actuel->Etat=ACTIF;
    
     Le_TSS.SS0 =L_Process_Actuel->Registres.SS0 ;
     Le_TSS.ESP0=L_Process_Actuel->Registres.ESP0;
 
 
//si c'est un code noyau ss et esp doivent être ss0 et esp0
//     
     UINT32 L_ESP =Le_TSS.ESP0;
     UINT32 L_SS  = Le_TSS.SS0;
     if (L_Process_Actuel->Registres.CS == SELECTEUR_CODE_NOYAU) {
         L_ESP = L_Process_Actuel->Registres.ESP;
         L_SS  = L_Process_Actuel->Registres.SS;               
     }

     asm volatile ("mov %0, %%esp"::"m"(L_ESP));
     asm volatile ("mov %0, %%ss"::"m"(L_SS));
       asm volatile ("push %0"::"m"(L_Repertoire_Page));
      asm volatile ("push %0"::"m"(L_Contexte));   
      
      asm volatile (" ljmp $0x08, $Commuter_Processus");//::"i"(SELECTEUR_CODE_NOYAU));
     
 } // if Compteur_Tic_Ordonnanceur
}
//-----------------------------------------------------------------------------

 
//------------------------------------------------------------------------------
void Donne_La_Main_Au_Processus(UINT16 P_Numero)
{
 T_INFO_PROCESSUS* L_Process=(T_INFO_PROCESSUS*) (ADRESSE_INFO_PROCESS + (P_Numero*sizeof(T_INFO_PROCESSUS)) );
 UINT32* L_Repertoire_Page=(UINT32*)L_Process->Registres.CR3;
 UINT32* L_Contexte =(UINT32*)(&L_Process->Registres);
 
#ifdef DEBUG_ORDONNANCEUR
  Efface_Ecran();
  Regle_Couleur(ROUGE); 
  Affiche_Chaine("[ORDONNANCEUR] ");
  Regle_Couleur(BLANC); 
  Affiche_Chaine("CPU au process: ");
  Affiche_Chaine(Entier_Vers_Chaine(P_Numero));
  Affiche_Chaine(" @Info Proc: ");
  Affiche_Chaine(Entier_Vers_Chaine_Hexa((UINT32)L_Process,4)); 
  Affiche_Chaine(" Rep: ");
  Affiche_Chaine(Entier_Vers_Chaine_Hexa((UINT32)(L_Process->Registres.CR3),4)); 
  Affiche_Chaine(" Taille: ");
  Affiche_Chaine(Entier_Vers_Chaine(sizeof(T_CONTEXTE_REGISTRES))); 

 Affiche_Chaine("\nPile: GS, FS, ES, DS, EDI, ESI, EBP, ESP_N, EBX, EDX, ECX, EAX, EIP, CS, flags, ESP, SS \n");
 UINT16 L_Index;
 for (L_Index=0; L_Index<20; L_Index++) {
    Affiche_Chaine(Entier_Vers_Chaine(L_Index));
    Affiche_Chaine(": ");
    Affiche_Chaine(Entier_Vers_Chaine_Hexa(((UINT32*)&L_Process->Registres)[L_Index],4));
    Affiche_Chaine(";  ");
 }

  Affiche_Chaine("\nDS : "); 
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Process->Registres.DS ,4)); 
  Affiche_Chaine("   ES : "); 
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Process->Registres.ES ,4)); 
  Affiche_Chaine("   FS : "); 
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Process->Registres.FS ,4)); 
  Affiche_Chaine("  GS : "); 
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Process->Registres.GS ,4)); 
  Affiche_Chaine("\nEAX : "); 
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Process->Registres.EAX ,4));   
  Affiche_Chaine("\nESP0 : "); 
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Process->Registres.ESP0 ,4));   
  Affiche_Chaine("  SS0 : "); 
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Process->Registres.SS0 ,4)); 
#endif

//-------------------- 
  Le_TSS.ESP0 = L_Process->Registres.ESP0;
  Le_TSS.SS0  = L_Process->Registres.SS0;
  Le_TSS.CR3  = L_Process->Registres.CR3;
  L_Process->Etat=ACTIF;
 //---------------------- 
  asm volatile ("cli \n push %0\n \
                  push %1 \n \
                 ljmp %2, $Commuter_Processus"
                 ::"m"(L_Repertoire_Page),
                   "m"(L_Contexte),
                   "i"(SELECTEUR_CODE_NOYAU));       



}
//#############################################################################

