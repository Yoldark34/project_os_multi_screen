/*
 * File:   ECRAN.h
 * Author: JLV
 *
 *
 */
#include "TYPE.h"

#ifndef _ECRAN_H
#define	_ECRAN_H

#define BLEU       0x01
#define FOND_BLEU  0x10
#define VERT       0x02
#define FOND_VERT  0x20
#define ROUGE      0x04
#define FOND_ROUGE 0x40
#define LUMINEUX   0x08
#define CLIGNOTANT 0x80
#define BLANC      ROUGE | VERT | BLEU

#pragma pack(1)
typedef struct {
    UCHAR Caractere;
    BYTE  Attribut;
}T_CARACTERE_ECRAN;
#pragma pack()

//extern BYTE* Video;
//extern T_CARACTERE_ECRAN* Map_Video;

//------------------------------------------------------------

  void Efface_Ecran();
  void Remplir_Ecran(UCHAR P_Caractere, BYTE P_Attribut);
  void Defilement_Haut();
  void Positionne_Curseur(BYTE P_X, BYTE P_Y);
  void Affiche_Caractere(UCHAR P_Caractere);
  void Affiche_Chaine(UCHAR* P_Chaine);
  void Regle_Couleur(BYTE P_Attribut);
  BYTE Donne_Curseur_X();
  BYTE Donne_Curseur_Y();



#endif	/* _ECRAN_H */

