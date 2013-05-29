/*
 * File:   ECRAN.h
 * Author: JLV
 *
 *
 */
#include "TYPE.h"
#include "Ecran.h"
#include "Screen_Manager.h"

#ifndef _BUFFER_MANAGER_H
#define	_BUFFER_MANAGER_H

void Buf_Efface_Ecran();
void Buf_Remplir_Ecran(UCHAR P_Caractere, BYTE P_Attribut);
void Buf_Defilement_Haut();
void Buf_Positionne_Curseur(BYTE P_X, BYTE P_Y);
void Buf_Affiche_Caractere(UCHAR P_Caractere);
void Buf_Affiche_Chaine(UCHAR P_Chaine[]);
void Buf_Regle_Couleur(BYTE P_Attribut);
BYTE Buf_Donne_Curseur_X();
BYTE Buf_Donne_Curseur_Y();
void SetCurrentBuffers(ScreenBuffers* P_Screen_Buffers);
void SetBuffer();
void Buf_Charge_Buf_Actuel_To_Screen();

#endif	/* _BUFFER_MANAGER_H */

