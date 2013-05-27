#include "type.h"
#include "PLAN_MEMOIRE.h"
#include "Ecran.h"
#include "BitMap_Memoire.h"
#include "Outils.h"



//#############################################################################
//# VARIABLE GLOBALE
//#############################################################################
UINT32 Nombre_Pages_Libres=(NOMBRE_TOTAL_PAGES);


//#############################################################################
void Initialisation_BitMap_Memoire()
{
 // les pages  du noyau sont occupées
UINT32 L_Index;
  
UINT32 L_Nombre_Pages_Occuppees= (TAILLE_OS >>12);    // une page fait 4Ko
  
  for (L_Index=0; L_Index<L_Nombre_Pages_Occuppees; L_Index++) {
    BITMAP_RESERVE_PAGE(L_Index);    
  } 

#ifdef DEBUG_BITMAP_MEMOIRE
   Regle_Couleur(ROUGE); 
  Affiche_Chaine("[BITMAP] ");
  Regle_Couleur(BLANC); 
  Affiche_Chaine("Reservation de : ");
  Affiche_Chaine(Entier_Vers_Chaine(NOMBRE_TOTAL_PAGES-Nombre_Pages_Libres));
  Affiche_Chaine(" Pages allouees au noyau [00000000->");
  Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Index<<12,4));
  Affiche_Chaine("]\n");
  
#endif
  // Les autres pages sont libres  
  for (L_Index=L_Nombre_Pages_Occuppees; L_Index<NOMBRE_TOTAL_TABLES; L_Index++) {
    BITMAP_MARQUE_LIBERATION(L_Index);   
  } 
}
//------------------------------------------------------------------------------

