#include "Ecran.h" 
#include "PLAN_MEMOIRE.h"
#include "MACRO.h"
#include "Outils.h"

void Affiche_Message_Exception(UCHAR* P_Message, UINT32 P_ESP)
{
  Regle_Couleur(ROUGE); 
  Affiche_Chaine("\nEXCEPTION ");
  Affiche_Chaine(P_Message);
  Regle_Couleur(VERT); 
  Affiche_Caractere('[');
   Affiche_Chaine(Entier_Vers_Chaine_Hexa(*(UINT32*)(P_ESP+8),4));
  Affiche_Caractere(':');
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(*(UINT32*)(P_ESP+4),4));
  Affiche_Caractere(':');
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(*(UINT32*)P_ESP,4));
  Affiche_Chaine("]\n");
  Regle_Couleur(BLANC);
  
}

//------------------------------------------------------------------------------
void  CallBack_Erreur_Division(UINT32 P_ESP)  // EXCEPTION TYPE ERREUR
{  
  INITIALISER_DS(SELECTEUR_DATA_NOYAU);  // L'interruption doit manipuler des données du noyau.  
                                         // on positionne donc DS avec le bon selecteur
  Affiche_Message_Exception("erreur de division : ", P_ESP);
 
  // P_ESP Contient la valeur de ESP au moment de l'exception c'est à dire la valeur de EIP.
  // EIP est le numéro de case mémoire de l'instruction qui a causée l'exception. 
  // lors de la sortie de de l'exception on dépilera pour ré-alimenter EIP.
  // Modifions dés maintenant cette valeur afin de pointer vers l'instruction suivante. 
  // puisque DIV occupe 2 octets :
  *((UINT32*)P_ESP) +=2;

}

//------------------------------------------------------------------------------
void CallBack_Mise_Au_Point(UINT32 P_ESP)
{
    INITIALISER_DS(SELECTEUR_DATA_NOYAU);     
    Affiche_Message_Exception("mise au point : ", P_ESP);
    HALT;  // Arret du processeur
}

//------------------------------------------------------------------------------
void CallBack_INT3(UINT32 P_ESP)
{
    INITIALISER_DS(SELECTEUR_DATA_NOYAU);                  
   Affiche_Message_Exception("INT3 Debug : ", P_ESP);
    
}

//------------------------------------------------------------------------------
void CallBack_Debordement(UINT32 P_ESP)
{
    INITIALISER_DS(SELECTEUR_DATA_NOYAU);                  
    Affiche_Message_Exception("Debordement : ", P_ESP);
    HALT;
}

//------------------------------------------------------------------------------
void CallBack_Limite(UINT32 P_ESP) // EXCEPTION TYPE ERREUR
{
    INITIALISER_DS(SELECTEUR_DATA_NOYAU);                   
    Affiche_Message_Exception("Limitye : ", P_ESP);
    HALT;
}


//------------------------------------------------------------------------------
void CallBack_CodeOP_Invalide(UINT32 P_ESP)
{
    INITIALISER_DS(SELECTEUR_DATA_NOYAU);                    
    Affiche_Message_Exception("CodeOP invalide : ", P_ESP);
    HALT;
 }

//------------------------------------------------------------------------------
void CallBack_DNA(UINT32 P_ESP)
{
    INITIALISER_DS(SELECTEUR_DATA_NOYAU);                   
    Affiche_Message_Exception("DNA : ", P_ESP);
    HALT;
}

//------------------------------------------------------------------------------
void CallBack_Double_Faute(UINT32 P_ESP)
{
    INITIALISER_DS(SELECTEUR_DATA_NOYAU);                  
    Affiche_Message_Exception("Double faute : ", P_ESP);
    HALT;
}

//------------------------------------------------------------------------------
void CallBack_Depassement(UINT32 P_ESP)
{
    INITIALISER_DS(SELECTEUR_DATA_NOYAU);                  
    Affiche_Message_Exception("Depassement : ", P_ESP);
    HALT;
}

//------------------------------------------------------------------------------
void CallBack_TSS_Invalide(UINT32 P_ESP)
{
    INITIALISER_DS(SELECTEUR_DATA_NOYAU);                   
    Affiche_Message_Exception("TSS invalide : ", P_ESP);
    HALT;
}

//------------------------------------------------------------------------------
void CallBack_Segment_Non_Present(UINT32 P_ESP)
{
    MOV(ax,SELECTEUR_DATA_NOYAU);  
    MOV(ds,ax);                  
    Affiche_Message_Exception("Segment non present : ", P_ESP);
    HALT;
}

//------------------------------------------------------------------------------
void CallBack_Segment_Pile(UINT32 P_ESP)
{
    INITIALISER_DS(SELECTEUR_DATA_NOYAU);                   
    Affiche_Message_Exception("Segment pile : ", P_ESP);
    HALT;
}

//------------------------------------------------------------------------------
void CallBack_Violation_Protection(UINT32 P_ESP)
{
    INITIALISER_DS(SELECTEUR_DATA_NOYAU);                    
    Affiche_Message_Exception("violation de protection : ", P_ESP);
    HALT;
}

//------------------------------------------------------------------------------
void CallBack_Defaut_De_Page(UINT32 P_ESP)
{
    INITIALISER_DS(SELECTEUR_DATA_NOYAU);                   
    Affiche_Message_Exception("default de page : ", P_ESP);
    HALT;
}

//------------------------------------------------------------------------------
void CallBack_CoProcesseur(UINT32 P_ESP)
{
    INITIALISER_DS(SELECTEUR_DATA_NOYAU);                   
    Affiche_Message_Exception("coprrcesseurt : ", P_ESP); 
    HALT;
}


//------------------------------------------------------------------------------
void CallBack_Exception_Par_Defaut(UINT32 P_ESP)
{
    INITIALISER_DS(SELECTEUR_DATA_NOYAU);                  
    Affiche_Message_Exception("par defaut : ", P_ESP);
}

