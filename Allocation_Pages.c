#include "BitMap_Memoire.h"
#include "Ecran.h"
#include "Outils.h"
#include "Allocation_Pages.h"


UINT32 Cherche_Page_Systeme_Libre()
{
 UINT32 L_Numero_Page =0;
 BYTE L_Encore=1;
 UINT32 L_Page_Libre=0;
 while ((L_Numero_Page<NOMBRE_TOTAL_PAGES)&&L_Encore) {
     if (DONNE_ETAT_BITMAP(L_Numero_Page)==0) { 
        L_Encore=0; 
        L_Page_Libre=L_Numero_Page;
     }
     L_Numero_Page++;
 }
 return L_Page_Libre;
}
//------------------------------------------------------------------------------

void Allouer_Pages(UINT32 P_Adresse_Base_Repertoire, UINT32 P_Adresse_Virtuelle, UINT32 P_Nombre_Pages)
{
UINT32 L_Nombre_Pages;
UINT32 L_Adresse_Physique;
UINT32 L_Page_Libre;
   if (Nombre_Pages_Libres>= P_Nombre_Pages) {
       for (L_Nombre_Pages=0; L_Nombre_Pages<P_Nombre_Pages; L_Nombre_Pages++){        
           L_Page_Libre=Cherche_Page_Systeme_Libre();
           BITMAP_RESERVE_PAGE(L_Page_Libre);
           L_Adresse_Physique=L_Page_Libre<<12;
           Associer_Virtuel_Physique(P_Adresse_Base_Repertoire,P_Adresse_Virtuelle,L_Adresse_Physique );
           P_Adresse_Virtuelle += 4096;
           
       }
   }
  
#ifdef DEBUG_ALLOCATION
  Regle_Couleur(ROUGE);
  Affiche_Chaine("[Allocation pages] ");
  Regle_Couleur(BLANC);   
  Affiche_Chaine("Allocation de :");
  Affiche_Chaine(Entier_Vers_Chaine(L_Nombre_Pages));
  Affiche_Chaine(" pages. Il reste : ");
  Affiche_Chaine(Entier_Vers_Chaine(Nombre_Pages_Libres));
  Affiche_Caractere('\n');  
#endif
}
