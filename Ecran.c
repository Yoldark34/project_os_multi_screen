/*
 * File:   ECRAN.c
 * Author: JLV
 * TP EMA OS 2011
 *
 */
#include "ECRAN.h"
//#include "TYPE.h"
#include "OUTILS.h"





#define ADRESSE_BASE_VIDEO     0xB8000
#define NOMBRE_COLONNES        80
#define NOMBRE_LIGNES          25
#define NOMBRE_ELEMENTS        NOMBRE_COLONNES*NOMBRE_LIGNES
#define NOMBRE_BYTE_TOTAL      NOMBRE_COLONNES*NOMBRE_LIGNES*2
#define NOMBRE_BYTE_PAR_LIGNE  NOMBRE_COLONNES*2
#define TAILLE_TABULATION      4

//-------------------------------------------------------
// Variables globale Externes
//-------------------------------------------------
BYTE* Video = (BYTE*)ADRESSE_BASE_VIDEO;
T_CARACTERE_ECRAN* Map_Video=(T_CARACTERE_ECRAN*)ADRESSE_BASE_VIDEO;

//-------------------------------------------------
// Variables globales internes
//--------------------------------------------------
BYTE ECRAN_Curseur_X = 0;
BYTE ECRAN_Curseur_Y = 0;
BYTE Attribut_Actuel = 0x07;



//#################################################################################################
void Efface_Ecran()
{
UINT16 L_Index;
  for (L_Index=0; L_Index<NOMBRE_ELEMENTS; L_Index++) {
        Map_Video[L_Index].Attribut=0x07;
        Map_Video[L_Index].Caractere=' ';
  }
 ECRAN_Curseur_X = 0;
 ECRAN_Curseur_Y = 0;
}

//--------------------------------------------------------------------------------------------------
void Remplir_Ecran(UCHAR P_Caractere, BYTE P_Attribut)
{
  UINT16 L_Index;
    for (L_Index=0; L_Index<NOMBRE_ELEMENTS; L_Index++) {
        Map_Video[L_Index].Attribut=P_Attribut;
        Map_Video[L_Index].Caractere=P_Caractere;
    }
 ECRAN_Curseur_X = 0;
 ECRAN_Curseur_Y = 0;
}

//--------------------------------------------------------------------------------------------------
void Defilement_Haut()
{
BYTE* L_PT_Ligne_0 = Video;
BYTE* L_PT_Ligne_1 = Video + NOMBRE_BYTE_PAR_LIGNE;

UINT16 L_Index;
    for (L_Index=0; L_Index<NOMBRE_BYTE_TOTAL-NOMBRE_BYTE_PAR_LIGNE; L_Index++) {
      L_PT_Ligne_0[L_Index]=L_PT_Ligne_1[L_Index];

    }

UINT16 L_Offset=NOMBRE_ELEMENTS-NOMBRE_COLONNES;
T_CARACTERE_ECRAN L_Caractere={.Attribut=0x07,.Caractere=' '};


  for (L_Index=0; L_Index<NOMBRE_COLONNES;L_Index++ ) {
     Map_Video[L_Offset]=L_Caractere;
     L_Offset++;
  }
  ECRAN_Curseur_X = 0;
}
 
//--------------------------------------------------------------------------------------------------
inline void Positionne_Curseur(BYTE P_X, BYTE P_Y)
{
   ECRAN_Curseur_X = P_X;
   ECRAN_Curseur_Y = P_Y;
}
//--------------------------------------------------------------------------------------------------
inline void Affiche_Curseur()
{
#define outb(P_Port,P_Valeur) asm volatile ("outb %%al,%%dx" ::"d"(P_Port), "a"(P_Valeur));

 UINT16 L_Offset;
   L_Offset = (ECRAN_Curseur_Y* NOMBRE_COLONNES) + ECRAN_Curseur_X;

    outb(0x3d4, 0x0f);
    outb(0x3d5, (BYTE) L_Offset);
    outb(0x3d4, 0x0e);
    outb(0x3d5, (BYTE) (L_Offset >> 8));
}




//--------------------------------------------------------------------------------------------------
inline void Repositionne_Curseur()
{
     
    if (ECRAN_Curseur_X>=NOMBRE_COLONNES) {
       ECRAN_Curseur_X=0;
       ECRAN_Curseur_Y++;
    }
    if (ECRAN_Curseur_Y>=NOMBRE_LIGNES) {
           Defilement_Haut();
           ECRAN_Curseur_Y--;
     }
}


//--------------------------------------------------------------------------------------------------
inline void Affiche_Caractere(UCHAR P_Caractere)
 {
  UINT16 L_Offset;
     switch (P_Caractere) {
         case 10 : ECRAN_Curseur_Y++;
                   ECRAN_Curseur_X=0;
                   break;
         case 13 : ECRAN_Curseur_X=0;
                   break;
         case 9  : ECRAN_Curseur_X = ECRAN_Curseur_X + TAILLE_TABULATION;
                   ECRAN_Curseur_X = ECRAN_Curseur_X % NOMBRE_COLONNES;
                   break;
         default : L_Offset = (ECRAN_Curseur_Y* NOMBRE_COLONNES) + ECRAN_Curseur_X;
                   Map_Video[L_Offset].Attribut=Attribut_Actuel;
                   Map_Video[L_Offset].Caractere=P_Caractere;
                   ECRAN_Curseur_X++;                 
     }
      Repositionne_Curseur();
      Affiche_Curseur();
 }



//--------------------------------------------------------------------------------------------------
void Affiche_Chaine(UCHAR P_Chaine[])
{
 int  L_Index=0;

    while (P_Chaine[L_Index]!=0) {
        Affiche_Caractere(P_Chaine[L_Index]);
        L_Index++;
     }
   Affiche_Curseur();
}

//--------------------------------------------------------------------------------------------------
void Regle_Couleur(BYTE P_Attribut)
{
   Attribut_Actuel=P_Attribut;
}


//--------------------------------------------------------------------------------------------------
  BYTE Donne_Curseur_X()
  {
    return ECRAN_Curseur_X;    
  }
  
//--------------------------------------------------------------------------------------------------
  BYTE Donne_Curseur_Y()
  {
    return ECRAN_Curseur_Y;   
  }

  //--------------------------------------------------------------------------------------------------
  void Affiche_Liste_Caracteres(UCHAR P_Caractere, UINT16 P_Repetition)
  {
   int L_Index;
   
   for (L_Index=0; L_Index<P_Repetition; ++L_Index) {
       Affiche_Caractere(P_Caractere);
   }  
  }
