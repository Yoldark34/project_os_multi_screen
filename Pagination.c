#include "MACRO.h"
#include "PLAN_MEMOIRE.h"
#include "Descripteurs.h"
#include "Ecran.h"
#include "Outils.h"
#include "Pagination.h"


void Creation_Tables_Pages_Process(UINT32 P_Adresse_Base_Repertoire)
{
UINT32 L_Index;
T_ENTREE_TABLE_PAGE* L_Repertoire_Tables_Process = (T_ENTREE_TABLE_PAGE*)P_Adresse_Base_Repertoire;
T_ENTREE_TABLE_PAGE* L_Repertoire_Tables_OS =(T_ENTREE_TABLE_PAGE*)ADRESSE_REPERTOIRE_PAGES_OS;

// Les premières entrées pointent vers les tables de l'OS car le code est commun 
 for (L_Index=0; L_Index<NOMBRE_TABLES_PAGES_OS; L_Index++){
   L_Repertoire_Tables_Process[L_Index].Valeur = L_Repertoire_Tables_OS[L_Index].Valeur;
 }

// la suite pointe vers les tables relatives au contexte du process
T_ENTREE_TABLE_PAGE* L_Table_Pages_Process = (T_ENTREE_TABLE_PAGE*)(P_Adresse_Base_Repertoire+TAILLE_TABLE_DE_PAGES);
 for (L_Index=NOMBRE_TABLES_PAGES_OS; L_Index<NOMBRE_TABLES_PAGES_PROCESS; L_Index++){
  L_Repertoire_Tables_Process[L_Index].Valeur = ((UINT32)L_Table_Pages_Process& 0xFFFFF000); // seuls les 20 bits de poids fort sont conservés
  L_Repertoire_Tables_Process[L_Index].Element.Bit_P=0;  // page non présente pour l'intant
  L_Repertoire_Tables_Process[L_Index].Element.Bit_RW=1;  // accessible en lecture/ecriture/execution
  L_Repertoire_Tables_Process[L_Index].Element.Bit_US=1;
  //si Bit_US=0  à zéro Accés reservé au ring 0,1 et 2 (interdit au 3) et Page mémoire de 4Ko
  L_Table_Pages_Process += TAILLE_TABLE_DE_PAGES;
 } 


// A la suite sont stockées les tables de pagess
// les entrées pointentront vers des pages physiques
// Considérons ces pages innexstante pour l'instant
L_Table_Pages_Process = (T_ENTREE_TABLE_PAGE*)(P_Adresse_Base_Repertoire+TAILLE_TABLE_DE_PAGES);
  for (L_Index=0; L_Index<NOMBRE_TOTAL_PAGES; L_Index++){
    L_Table_Pages_Process[L_Index].Valeur=0; //
    L_Table_Pages_Process[L_Index].Element.Bit_P=0;
    L_Table_Pages_Process[L_Index].Element.Bit_RW=1;
    L_Table_Pages_Process[L_Index].Element.Bit_US=1;
    
    
  }


}

//##############################################################################


//------------------------------------------------------------------------------
void Configuration_Repertoire_Tables_OS()
{
UINT32 L_Index;
T_ENTREE_TABLE_PAGE* L_Repertoire_Tables = (T_ENTREE_TABLE_PAGE*)ADRESSE_REPERTOIRE_PAGES_OS;

// Pointer vers toutes les tables de pages 
// Les adresses virtuelles doivent être égales aux adresses physiques 
UINT32 L_Adresse_Table = ADRESSE_TABLES_PAGES_OS;

#ifdef DEBUG_PAGINATION
  Regle_Couleur(ROUGE); 
  Affiche_Chaine("[PAGINATION] ");
  Regle_Couleur(BLANC); 
  Affiche_Chaine("Mapping de : ");
  Affiche_Chaine(Entier_Vers_Chaine(NOMBRE_TABLES_PAGES_OS+1));
  Affiche_Chaine(" Repertoires\n");
#endif

 for (L_Index=0; L_Index<NOMBRE_TOTAL_TABLES; L_Index++){
    L_Repertoire_Tables[L_Index].Valeur = (L_Adresse_Table & 0xFFFFF000); // seuls les 20 bits de poids fort sont conservés
    L_Repertoire_Tables[L_Index].Element.Bit_P=1;  // page présente
    L_Repertoire_Tables[L_Index].Element.Bit_RW=1;  // accessible en lecture/ecriture/execution
    //si Bit_US=0   à zéro Accés reservé au ring 0,1 et 2 (interdit au 3) et Page mémoire de 4Ko
     L_Repertoire_Tables[L_Index].Element.Bit_US=1;
    L_Adresse_Table += TAILLE_TABLE_DE_PAGES;
 }
}

//------------------------------------------------------------------------------
void Configuration_Tables_De_Pages_OS()
{
UINT32 L_Entree;

T_ENTREE_TABLE_PAGE* L_Table = (T_ENTREE_TABLE_PAGE*)ADRESSE_TABLES_PAGES_OS;
UINT32 L_Adresse_Physique =0x00000000;


#ifdef DEBUG_PAGINATION
   Regle_Couleur(ROUGE); 
  Affiche_Chaine("[PAGINATION] ");
  Regle_Couleur(BLANC); 
  Affiche_Chaine("Mapping de : ");
 Affiche_Chaine(Entier_Vers_Chaine(NOMBRE_PAGES_OS));
 Affiche_Chaine(" Tables \n");
#endif


// Les adresses virtuelles sont égales aux adresses physiques 
for (L_Entree=0; L_Entree<NOMBRE_PAGES_OS; L_Entree++) {
        L_Table[L_Entree].Valeur=(L_Adresse_Physique& 0xFFFFF000); // seuls les 20 bits de poids fort sont conservés
        L_Table[L_Entree].Element.Bit_P=1;  // page présente
        L_Table[L_Entree].Element.Bit_RW=1;  // accessible en lecture/ecriture/execution    
        L_Table[L_Entree].Element.Bit_US=1;
        L_Adresse_Physique += TAILLE_PAGE_MEMOIRE;
    }   
 
  for (L_Entree=NOMBRE_PAGES_OS; L_Entree<NOMBRE_TOTAL_PAGES; L_Entree++){
    L_Table[L_Entree].Valeur=0; //
  }
 
}

//##############################################################################

inline UINT32 Donne_Adresse_Tables_Pages_Process(UINT32 P_Numero)
{
   return   ADRESSE_REPERTOIRE_PAGES_PROCESS+(P_Numero*TAILLE_STRUCTURE_PAGES_UN_PROCESS);  
}
//------------------------------------------------------------------------------


UINT32 Donne_Adresse_Physique(UINT32 P_Adresse_Base_Repertoire,UINT32 P_Virtuelle)
{
  UINT32 L_Index_Repertoire;    
UINT32 L_Index_Table;
T_ENTREE_TABLE_PAGE* L_Repertoire = (T_ENTREE_TABLE_PAGE*)P_Adresse_Base_Repertoire;
T_ENTREE_TABLE_PAGE* L_Table;
        L_Index_Repertoire=P_Virtuelle>>22;
        L_Index_Table=(P_Virtuelle & 0x003FF000)>>12;
        
        if (L_Repertoire[L_Index_Repertoire].Element.Bit_P==1) {
          L_Table=(T_ENTREE_TABLE_PAGE*)(L_Repertoire[L_Index_Repertoire].Valeur & 0xFFFFF000);          
          return  ((L_Table[L_Index_Table].Element.Adresse <<12) +  (P_Virtuelle & 0x00000FFF));
        } else return 0xFFFFFFFF;
}


//------------------------------------------------------------------------------
UINT32 Associer_Virtuel_Physique(UINT32 P_Adresse_Base_Repertoire, UINT32 P_Virtuelle, UINT32 P_Physique)
{


T_ENTREE_TABLE_PAGE* L_Repertoire = (T_ENTREE_TABLE_PAGE*)P_Adresse_Base_Repertoire;
T_ENTREE_TABLE_PAGE* L_Table;
 
UINT32 L_Numero_Table=P_Virtuelle>>22;
    L_Repertoire[L_Numero_Table].Element.Bit_P=1;
    L_Repertoire[L_Numero_Table].Element.Bit_RW=1;
    L_Repertoire[L_Numero_Table].Element.Bit_US=1;
        
    L_Table=(T_ENTREE_TABLE_PAGE*)   (L_Repertoire[L_Numero_Table].Valeur & 0xFFFFF000);
    
UINT32 L_Numero_Page = ((P_Virtuelle>>12)& 0x3FF);
         
  L_Table[L_Numero_Page].Element.Adresse = (P_Physique>>12);
  L_Table[L_Numero_Page].Element.Bit_P =1;
  L_Table[L_Numero_Page].Element.Bit_US =1;
  L_Table[L_Numero_Page].Element.Bit_RW =1;   

     
   #ifdef DEBUG_PAGINATION
        Regle_Couleur(ROUGE);
        Affiche_Chaine("[Asso @V -> @P] ");
        Regle_Couleur(BLANC); 
        Affiche_Chaine(" @V: ");
        Affiche_Chaine(Entier_Vers_Chaine_Hexa(P_Virtuelle,4));
        Affiche_Chaine(" Ent. Rep: ");
        Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Numero_Table,2));
        Affiche_Chaine(" Ent. Table: ");
        Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Numero_Page,2));
        Affiche_Chaine(" @P: ");
        Affiche_Chaine(Entier_Vers_Chaine_Hexa(P_Physique & 0xFFFFF000,4));
        Affiche_Chaine("\n");
      #endif
  
   return L_Table[L_Numero_Page].Valeur; 
}

//------------------------------------------------------------------------------
void Initialisation_Tables_Pages_Process()
{
    UINT16 L_Index;
    UINT32 L_Adresse_Table = ADRESSE_REPERTOIRE_PAGES_PROCESS;
    #ifdef DEBUG_PAGINATION
      Regle_Couleur(ROUGE);
      Affiche_Chaine("[TABLE PROCESS] ");
      //Regle_Couleur(BLANC); 
      //Affiche_Chaine("@Tables : ");
    #endif
    for (L_Index=0; L_Index<NOMBRE_MAXI_PROCESSUS; L_Index++) {       
      #ifdef DEBUG_PAGINATION
       // Affiche_Chaine(Entier_Vers_Chaine_Hexa(L_Adresse_Table,4));
        Affiche_Chaine(".");
      #endif
      Creation_Tables_Pages_Process(L_Adresse_Table);
      L_Adresse_Table+=TAILLE_STRUCTURE_PAGES_UN_PROCESS;
    }
    #ifdef DEBUG_PAGINATION
      Regle_Couleur(BLANC); 
      Affiche_Chaine("\n");
   #endif
}


//##############################################################################
void Initialisation_Pagination()
{
   Configuration_Repertoire_Tables_OS();
   Configuration_Tables_De_Pages_OS();
  
  INITIALISER_REGISTRE_CR3_CONST(ADRESSE_REPERTOIRE_PAGES_OS);
  ACTIVER_PAGINATION;
}



