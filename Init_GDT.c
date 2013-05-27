#include "Descripteurs.h"
#include "PLAN_MEMOIRE.h"
#include "MACRO.h"





//------------------------------------------------------------------------------
// Variables globales
//------------------------------------------------------------------------------
T_INFO_GDT Info_GDT;
//------------------------------------------------------------------------------


void Intialisation_Descripteurs_Noyau()
{
 T_DESCRIPTEUR_SEGMENT* L_Descripteurs_Segment=(T_DESCRIPTEUR_SEGMENT*)ADRESSE_DESCRIPTEURS_SEGMENTS;

/*

UINT16 L_Index;
  for (L_Index=0; L_Index<LIMITE_DESCRIPTEURS_SEGMENT; L_Index++){
     Configure_Descripteur_Segment(&L_Descripteurs_Segment[L_Index],0,0,0,0,0,0,0,0,0,0);  
   }
 
*/
 
 
 // DESCRIPTEUR NULL
    Configure_Descripteur_Segment(&L_Descripteurs_Segment[0],0,0,0,0,0,0,0,0,0,0);  // le premier descripteur est null
   
     //DESCRIPTEUR SEGMENT DE CODE
    
  Configure_Descripteur_Segment(&L_Descripteurs_Segment[INDEX_DESCRIPTEUR_CODE_NOYAU],                       // Segment de Code
                                  BASE_CODE_NOYAU,LIMITE_CODE_NOYAU,               // Base :0 Limite : 4Go
                                  SEGMENT_TYPE_LECTURE_EXECUTION_ACCEDE,      // Type : Execution-Lecture accédé par registre (Segment de CODE)
                                  1,                         // bit DT Segment mémoire et non guichet donc DT =1
                                  RING_0,                    // Privilege niveau 0 le plus interne (normal c'est le CS du Noyau)
                                  1,                         // bit P est présent donc valide pour la translation d'adresses
                                  1,                         // bit AVL à usage privé ... donc ne sert à rien sauf si on veut ...
                                  0,                         // bit O à 0
                                  1,                         // bit D  toujours à 1 (instruction par défaut sur 32 bits) les i286 pêuvent mettre à 0
                                  1);                        // bit G granularité de la limite à 4Ko (et non pas 1 octet)

   //DESCRIPTEUR SEGMENT DE DONNEES
     Configure_Descripteur_Segment(&L_Descripteurs_Segment[INDEX_DESCRIPTEUR_DATA_NOYAU],                       // Segment de Data
                                  BASE_DATA_NOYAU,LIMITE_DATA_NOYAU,               // Base :0 Limite : 4Go
                                  SEGMENT_TYPE_LECTURE_ECRITURE_ACCEDE,    // Type : -Lecture-Ecriture accédé par registre (Segment de DATA)
                                  1,                         // bit DT Segment mémoire et non guichet donc DT =1
                                  RING_0,                    // Privilege niveau 0 le plus interne (normal c'est le DS du Noyau)
                                  1,                         // bit P est présent donc valide pour la translation d'adresses
                                  1,                         // bit AVL à usage privé ... donc ne sert à rien sauf si on veut ...
                                  0,                         // bit O à 0
                                  1,                         // bit D  toujours à 1 (instruction par défaut sur 32 bits) les i286 pêuvent mettre à 0
                                  1);                        // bit G granularité de la limite à 4Ko (et non pas 1 octet)

     //DESCRIPTEUR SEGMENT DE PILE
     Configure_Descripteur_Segment(&L_Descripteurs_Segment[INDEX_DESCRIPTEUR_STACK_NOYAU],                       // Segment de Stack
                                  BASE_STACK_NOYAU,LIMITE_STACK_NOYAU,               // Base :0 Limite : 0
                                  SEGMENT_TYPE_LECTURE_ECRITURE_INVERSE_ACCEDE,                       // Type : Lecture-Ecriture accédé redimentionnable
                                  1,                         // bit DT Segment mémoire et non guichet donc DT =1
                                  RING_0,                    // Privilege niveau 0 le plus interne (normal c'est le SS du Noyau)
                                  1,                         // bit P est présent donc valide pour la translation d'adresses
                                  1,                         // bit AVL à usage privé ... donc ne sert à rien sauf si on veut ...
                                  0,                         // bit O à 0
                                  1,                         // bit D  toujours à 1 (instruction par défaut sur 32 bits) les i286 pêuvent mettre à 0
                                  1);                        // bit G granularité de la limite à 4Ko (et non pas 1 octet)
  
}

//==============================================================================

void Initialisation_Descripteurs_Utilisateurs()
{
T_DESCRIPTEUR_SEGMENT* L_Descripteurs_Segment=(T_DESCRIPTEUR_SEGMENT*)ADRESSE_DESCRIPTEURS_SEGMENTS;

Configure_Descripteur_Segment(&L_Descripteurs_Segment[INDEX_DESCRIPTEUR_CODE_USER],                       // Segment de Code
                                  BASE_CODE_USER,LIMITE_CODE_USER,               // Base :0 Limite : 4Go
                                  SEGMENT_TYPE_LECTURE_EXECUTION_ACCEDE,      // Type : Execution-Lecture accédé par registre (Segment de CODE)
                                  1,                         // bit DT Segment mémoire et non guichet donc DT =1
                                  RING_3,                    // Privilege niveau 3 le plus externe
                                  1,                         // bit P est présent donc valide pour la translation d'adresses
                                  1,                         // bit AVL à usage privé ... donc ne sert à rien sauf si on veut ...
                                  0,                         // bit O à 0
                                  1,                         // bit D  toujours à 1 (instruction par défaut sur 32 bits) les i286 pêuvent mettre à 0
                                  1);                        // bit G granularité de la limite à 4Ko (et non pas 1 octet)

   //DESCRIPTEUR SEGMENT DE DONNEES USER (Ring 3)
     Configure_Descripteur_Segment(&L_Descripteurs_Segment[INDEX_DESCRIPTEUR_DATA_USER],                       // Segment de Data
                                  BASE_DATA_USER,LIMITE_DATA_USER,               // Base :0 Limite : 4Go
                                  SEGMENT_TYPE_LECTURE_ECRITURE_ACCEDE,    // Type : -Lecture-Ecriture accédé par registre (Segment de DATA)
                                  1,                         // bit DT Segment mémoire et non guichet donc DT =1
                                  RING_3,                    // Privilege niveau 3 le plus externe
                                  1,                         // bit P est présent donc valide pour la translation d'adresses
                                  1,                         // bit AVL à usage privé ... donc ne sert à rien sauf si on veut ...
                                  0,                         // bit O à 0
                                  1,                         // bit D  toujours à 1 (instruction par défaut sur 32 bits) les i286 pêuvent mettre à 0
                                  1);                        // bit G granularité de la limite à 4Ko (et non pas 1 octet)

     //DESCRIPTEUR SEGMENT DE PILE USER (Ring 3)
     Configure_Descripteur_Segment(&L_Descripteurs_Segment[INDEX_DESCRIPTEUR_STACK_USER],                       // Segment de Stack
                                  BASE_STACK_USER,LIMITE_STACK_USER,                // Base :0 Limite : 0
                                  SEGMENT_TYPE_LECTURE_ECRITURE_INVERSE_ACCEDE,                       // Type : Lecture-Ecriture accédé redimentionnable
                                  1,                         // bit DT Segment mémoire et non guichet donc DT =1
                                  RING_3,                    // Privilege niveau 3 le plus externe
                                  1,                         // bit P est présent donc valide pour la translation d'adresses
                                  1,                         // bit AVL à usage privé ... donc ne sert à rien sauf si on veut ...
                                  0,                         // bit O à 0
                                  1,                         // bit D  toujours à 1 (instruction par défaut sur 32 bits) les i286 pêuvent mettre à 0
                                  1);                        // bit G granularité de la limite à 4Ko (et non pas 1 octet)
  
}


//==============================================================================
void Initialisation_GDT()
{
   Intialisation_Descripteurs_Noyau(); 
   Initialisation_Descripteurs_Utilisateurs();

     
  Info_GDT.Base=ADRESSE_DESCRIPTEURS_SEGMENTS;
  Info_GDT.Limite=LIMITE_DESCRIPTEURS_SEGMENTS *sizeof(T_DESCRIPTEUR_SEGMENT);
 
  //Initialiser le registre LGDT avec l'adresse de la structure d'information de la table
  INITIALISER_REGISTRE_GDTR(Info_GDT);
  
  
  // Initialiser les registres de segment data (ds, es,fs,gs) avec l'index du  descripteur 2
  INITIALISER_REGISTRES_SEGMENTS_DATA(SELECTEUR_DATA_NOYAU);

  // réalignement afin de vider le cache du processeur
  SAUT_ALIGNE(SELECTEUR_CODE_NOYAU)
     
}
