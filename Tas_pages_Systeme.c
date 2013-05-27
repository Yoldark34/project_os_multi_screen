
#include "type.h"
#include "PLAN_MEMOIRE.h"
#include "Descripteurs.h"


/*


void RAZ_Tas_Pages_Systeme()
{
UINT32 L_Index;
  for (L_Index=ADRESSE_BASE_TAS_PAGES_SYSTEME>>12; L_Index<LIMITE_TAS_PAGES_SYSTEME>>12; L_Index++) {
    BITMAP_MARQUE_LIBERATION(ADRESSE_BASE_BITMAP_MEMOIRE, L_Index);  
  }
}
//-----------------------------------------------------------------------------
BYTE Donne_Nombre_Pages_Systeme_Libres()
{
 UINT32 L_Compteur=0;
 UINT32 L_Index;
 for (L_Index=ADRESSE_BASE_TAS_PAGES_SYSTEME>>12; L_Index<LIMITE_TAS_PAGES_SYSTEME>>12; L_Index++) {
    L_Compteur += DONNE_ETAT_BITMAP(ADRESSE_BASE_BITMAP_MEMOIRE,L_Index);
  }
 return L_Compteur;
}

//-----------------------------------------------------------------------------
UINT32 Cherche_Page_Systeme_Libre()
{
 UINT32 L_Index_Bitmap_Debut =ADRESSE_BASE_TAS_PAGES_SYSTEME>>12;
 UINT32 L_Index_Bitmap_Fin=LIMITE_TAS_PAGES_SYSTEME>>12;
 BYTE L_Encore=1;
 UINT32 L_Page_Libre=0;
 while ((L_Index_Bitmap_Debut<L_Index_Bitmap_Fin)&&L_Encore) {
     if (DONNE_ETAT_BITMAP(ADRESSE_BASE_BITMAP_MEMOIRE,L_Index_Bitmap_Debut)==0) { 
        L_Encore=0; 
        L_Page_Libre=L_Index_Bitmap_Debut;
     }
     L_Index_Bitmap_Debut++;
 }
 return L_Page_Libre;
}


//-----------------------------------------------------------------------------
UINT32 Reserve_Adresse_Page_System_Libre()
{
 UINT32 L_Page_Libre = Cherche_Page_Systeme_Libre();
   if (L_Page_Libre) BITMAP_MARQUE_RESERVATION(ADRESSE_BASE_BITMAP_MEMOIRE,L_Page_Libre);
 return L_Page_Libre<<12;
}

//-----------------------------------------------------------------------------
void Libere_Adresse_Page_System(UINT32 P_Adresse)
{
    if ((P_Adresse >=ADRESSE_BASE_TAS_PAGES_SYSTEME) && (P_Adresse<LIMITE_TAS_PAGES_SYSTEME)) {
        P_Adresse>>=12;
        BITMAP_MARQUE_LIBERATION(ADRESSE_BASE_BITMAP_MEMOIRE,P_Adresse);
    }
}

//##############################################################################
// création d'une structure repertoire + table page pour un processus dont 
// la taille du contexte est passée en paramètre (arondi à 4Ko)
// l'adresse du répertoire est retourné
//------------------------------------------------------------------------------
UINT32 Creation_Structure_Page_Process(UINT32 P_Taille_Contexte)
{

 UINT32 L_Nombre_Tables_Necessaires = (P_Taille_Contexte>>22)+1;
 T_ENTREE_TABLE_PAGE* L_Adresse_Repertoire = (T_ENTREE_TABLE_PAGE*)0;
 INT16 L_Index;
if (Donne_Nombre_Pages_Systeme_Libres()>= (L_Nombre_Tables_Necessaires+1))  { 
  L_Adresse_Repertoire = (T_ENTREE_TABLE_PAGE*)Reserve_Adresse_Page_System_Libre();
  
  for ( L_Index=0; L_Index<L_Nombre_Tables_Necessaires; L_Index++){ 
   L_Adresse_Repertoire[L_Index].Valeur = Reserve_Adresse_Page_System_Libre();
   L_Adresse_Repertoire[L_Index].Element.Bit_P=1;  // page présente
   L_Adresse_Repertoire[L_Index].Element.Bit_RW=1;  // accessible en lecture/ecriture/execution
  //Bit_US=0 et Bit_PS  sont à zéro Accés reservé au ring 0,1 et 2 (interdit au 3) et Page mémoire de 4Ko
  }
} 

 return (UINT32)L_Adresse_Repertoire;
    
}
*/

void Initlisation_Structure_Pages_Process()
{
    
}
