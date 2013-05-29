#include "Buffer_Manager.h"
#include "Outils.h"
#include "PLAN_MEMOIRE.h"
#include "Descripteurs.h"
#include "MACRO.h"
#include "Processus.h"
#include "Ordonnanceur.h"



/*
 EAX :
 * 0 : effacer l'écran
 *     BH : caractère, BL : attribut
 * 1 : positionner le curseur
 *    BH : X, BL : Y
 * 2 : Affiche un Caractère
 *       BH : caractère, BL : attribut
 * 3 : Affiche Une Chaine
 *      EBX : adresse de la chaine
 * 4 : affiche une serie de caractères
 *      EBX : caractere
 *      ECX : répétition
 */


//##############################################################################
void CallBack_INT_Video(UINT32 P_EAX, UINT32 P_EBX, UINT32 P_ECX) // lecture dans la pile
{  
 INITIALISER_DS(SELECTEUR_DATA_NOYAU);
 
UINT16 L_DS;
UINT32 L_Base_Segment_Data;
T_DESCRIPTEUR_SEGMENT* L_Descripteur_Data;



   asm (".intel_syntax noprefix ");
     asm ("mov AX, [EBP+24]");     // dans la pile le registre DS est stocké 24 octets plus haut
     asm ("and AX,0xF8");        // seuls les 13 bits de poids fort représentent un l'index
     asm ("mov %0, AX": "=r" (L_DS));
   asm (".att_syntax noprefix "); 
  
//   asm ("movl 24(%%ebp), %%ax;"
//        "and $0XF8, %%ax;"
//        "mov %%ax,%0": "=m"(L_DS) );



   
    L_Descripteur_Data= (T_DESCRIPTEUR_SEGMENT*)(ADRESSE_DESCRIPTEURS_SEGMENTS + L_DS);
     L_Base_Segment_Data = L_Descripteur_Data->Base_Segment_0_15 + 
                          (L_Descripteur_Data->Base_Segment_16_23 << 16) + 
                          (L_Descripteur_Data->Base_Segment_24_31 << 24);
    
         
#ifdef DEBUG_APPEL_SYSTEM
    Affiche_Chaine("-- CallBack_INT_Video --> EAX: ");
    Affiche_Chaine(Entier_Vers_Chaine(P_EAX));
    Affiche_Chaine("    EBX: ");
    Affiche_Chaine(Entier_Vers_Chaine(P_EBX));
     Affiche_Chaine("    ECX: ");
    Affiche_Chaine(Entier_Vers_Chaine(P_ECX));
    
    Affiche_Caractere('\n');
#endif    

	T_INFO_PROCESSUS* L_Process_Actuel = (T_INFO_PROCESSUS*) (ADRESSE_INFO_PROCESS + (Numero_Process_Courrant * sizeof (T_INFO_PROCESSUS)));
	switchWritingContextFromPid(L_Process_Actuel->Pid);
	INTERDIRE_INTERRUPTION;
	switch (P_EAX) {
		case 0: Buf_Remplir_Ecran((P_EBX >> 8)&0xFF, P_EBX & 0xFF);
			break;
		case 1: Buf_Positionne_Curseur((P_EBX >> 8)&0xFF, P_EBX & 0xFF);
			break;
		case 2: Buf_Regle_Couleur(P_EBX & 0xFF);
			Buf_Affiche_Chaine((P_EBX >> 8)&0xFF);
			break;
		case 3: Buf_Regle_Couleur(P_ECX & 0xFF);

			Buf_Affiche_Chaine((UCHAR*) (L_Base_Segment_Data + P_EBX));
			break;

		case 4: Affiche_Liste_Caracteres(P_EBX & 0XFF, P_ECX & 0xFFFF);
			break;

	}
	AUTORISE_INTERRUPTION;



}
