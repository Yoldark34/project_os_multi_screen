
#include "TYPE.h"
#include "Descripteurs.h"
#include "Ecran.h"
#include "Outils.h"

//##############################################################################
void Configure_Descripteur_Segment(T_DESCRIPTEUR_SEGMENT* P_Descripteur,
                                  UINT32 P_Base, UINT32 P_Limite,
                                  BYTE P_Type, BYTE P_DT, BYTE P_Privilege, BYTE P_Present,
                                  BYTE P_AVL, BYTE P_O, BYTE P_D, BYTE P_G)
{
    P_Descripteur->Base_Segment_0_15 =  (P_Base & 0xffff);           // copie de 16 bits
    P_Descripteur->Base_Segment_16_23 = (P_Base & 0xff0000) >> 16;   // copie de 8 bits
    P_Descripteur->Base_Segment_24_31 = (P_Base & 0xff000000) >> 24; // copie de 8 bits

    
    P_Descripteur->Limite_Segment_0_15  = (P_Limite & 0xFFFF);        // copie de 16 bits
    P_Descripteur->Limite_Segment_16_19 = (P_Limite & 0xF0000) >> 16;  // copie de 4 bits


    P_Descripteur->Type = P_Type & 0xF; // copie de 4 bits
    P_Descripteur->Bit_DT = P_DT & 0x1;
    P_Descripteur->Privilege = P_Privilege &0x3;
    P_Descripteur->Bit_P = P_Present & 0x1;
    P_Descripteur->Bit_AVL =P_AVL & 0x1 ;
    P_Descripteur->Bit_O =P_O & 0x1;
    P_Descripteur->Bit_D = P_D & 0x1;
    P_Descripteur->Bit_G = P_G & 0x1;
    
#ifdef _DEBUG_SEGMENT
  Regle_Couleur(ROUGE); 
  Affiche_Chaine("[GDT]");
  Regle_Couleur(BLANC); 
  Affiche_Chaine(" Descripteur (");
  Affiche_Chaine(Entier_Vers_Chaine((UINT32)P_Descripteur/8));
  Affiche_Chaine(") : ");
  CHAR L_Index;

  for (L_Index=7; L_Index>=0; L_Index--){
      Affiche_Chaine(Entier_Vers_Chaine_Hexa(*((BYTE*)P_Descripteur+L_Index) ,1) );
      Affiche_Caractere(' ');
  }
  Affiche_Caractere(' ');

  
  Affiche_Chaine(Entier_Vers_Chaine_Hexa((UINT32)P_Base,4));
  Affiche_Chaine("->");
  if ((P_Descripteur->Type & 0x04) ==0x04) {        
        Affiche_Chaine( Entier_Vers_Chaine_Hexa( (UINT32) (P_D&0x1==0x1)?0xFFFFFFFF:0x0000FFFF ,4) );
        Affiche_Chaine("(Inv.)");
  } else  Affiche_Chaine( Entier_Vers_Chaine_Hexa( (UINT32) (P_Limite+1)*( (P_G&0x1==0x1)?4096:1)-1 ,4) );
  Affiche_Chaine(" Ring: ");
  Affiche_Chaine(Entier_Vers_Chaine(P_Descripteur->Privilege));
  Affiche_Caractere('\n');
 #endif
    
}


//##############################################################################
void Configure_Descripteur_Guichet(T_DESCRIPTEUR_GUICHET* P_Descripteur, UINT16 P_Selecteur, UINT32 P_Offset,
                                   BYTE P_Type, BYTE P_DPL, BYTE P_P)
{
    P_Descripteur->Offset_0_15  = (P_Offset & 0xFFFF);
    P_Descripteur->Offset_16_31 = (P_Offset & 0xFFFF0000) >> 16;
    P_Descripteur->Selecteur = P_Selecteur;

    P_Descripteur->Type = P_Type;
    P_Descripteur->Bit_DT= 0;
    P_Descripteur->Bit_DPL=P_DPL;
    P_Descripteur->Bit_P=P_P;
    P_Descripteur->Non_Utilise=0;
    
 #ifdef _DEBUG_GUICHET
  Regle_Couleur(ROUGE); 
  Affiche_Chaine("[IDT]");
  Regle_Couleur(BLANC); 
  Affiche_Chaine(" Creation descripteur (");
  Affiche_Chaine(Entier_Vers_Chaine((UINT32)P_Descripteur/8));
  Affiche_Chaine(") : ");
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(P_Selecteur,2));
  Affiche_Chaine(":");
  Affiche_Chaine( Entier_Vers_Chaine_Hexa( P_Offset ,4) );
  Affiche_Caractere('\n');
#endif
    
}


//##############################################################################

void Configure_TSS(T_SEGMENT_TSS* P_TSS,  UINT16 P_Segment_Code, UINT32 P_Adresse_Code, BYTE P_Debug)
{
    Initialise_Memoire((BYTE*)P_TSS,0,sizeof(T_SEGMENT_TSS));
    P_TSS->SS0=P_Segment_Code;
    P_TSS->ESP0=P_Adresse_Code;
    P_TSS->Mode_Debug= P_Debug & 0x01;  // copier 1 bit
    P_TSS->Autorisation_E_S=0x0;
}



