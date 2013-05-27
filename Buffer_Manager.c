/*
 * File:   ECRAN.c
 * Author: JLV
 * TP EMA OS 2011
 *
 */
#include "Buffer_Manager.h"
//#include "TYPE.h"
#include "OUTILS.h"
#include "Screen_Manager.h"

#define ADRESSE_BASE_VIDEO     0xB8000


//-------------------------------------------------------
// Variables globale Externes
//-------------------------------------------------
BYTE* Buf_Video = (BYTE*) ADRESSE_BASE_VIDEO;
T_CARACTERE_ECRAN* Buf_Map_Video = (T_CARACTERE_ECRAN*) ADRESSE_BASE_VIDEO;
ScreenBuffer* Current_Buffer;

//-------------------------------------------------
// Variables globales internes
//--------------------------------------------------
BYTE Buf_ECRAN_Curseur_X = 0;
BYTE Buf_ECRAN_Curseur_Y = 0;
BYTE Buf_Attribut_Actuel = 0x07;



//#################################################################################################

void Buf_SetCurrentBuffer(ScreenBuffer* buffer) {
	Current_Buffer = buffer;
}

void Buf_Efface_Ecran() {
	UINT16 L_Index;
	for (L_Index = 0; L_Index < NOMBRE_ELEMENTS; L_Index++) {
		Buf_Map_Video[L_Index].Attribut = 0x07;
		Buf_Map_Video[L_Index].Caractere = ' ';
		Current_Buffer->listBuffers[Current_Buffer->currentScreenIndex].Cellules[L_Index].Attribut = 0x07;
		Current_Buffer->listBuffers[Current_Buffer->currentScreenIndex].Cellules[L_Index].Caractere = ' ';
	}
	Buf_ECRAN_Curseur_X = 0;
	Buf_ECRAN_Curseur_Y = 0;
	Current_Buffer->listBuffers[Current_Buffer->currentScreenIndex].Curseur_X = 0;
	Current_Buffer->listBuffers[Current_Buffer->currentScreenIndex].Curseur_Y = 0;
}

//--------------------------------------------------------------------------------------------------

void Buf_Remplir_Ecran(UCHAR P_Caractere, BYTE P_Attribut) {
	UINT16 L_Index;
	for (L_Index = 0; L_Index < NOMBRE_ELEMENTS; L_Index++) {
		Buf_Map_Video[L_Index].Attribut = P_Attribut;
		Buf_Map_Video[L_Index].Caractere = P_Caractere;
		Current_Buffer->listBuffers[Current_Buffer->currentScreenIndex].Cellules[L_Index].Attribut = P_Attribut;
		Current_Buffer->listBuffers[Current_Buffer->currentScreenIndex].Cellules[L_Index].Caractere = P_Caractere;
	}
	Buf_ECRAN_Curseur_X = 0;
	Buf_ECRAN_Curseur_Y = 0;
	Current_Buffer->listBuffers[Current_Buffer->currentScreenIndex].Curseur_X = 0;
	Current_Buffer->listBuffers[Current_Buffer->currentScreenIndex].Curseur_Y = 0;
}

//--------------------------------------------------------------------------------------------------

void Buf_Defilement_Haut() {
	BYTE* L_PT_Ligne_0 = Buf_Video;
	BYTE* L_PT_Ligne_1 = Buf_Video + NOMBRE_BYTE_PAR_LIGNE;

	UINT16 L_Index;
	for (L_Index = 0; L_Index < NOMBRE_BYTE_TOTAL - NOMBRE_BYTE_PAR_LIGNE; L_Index++) {
		L_PT_Ligne_0[L_Index] = L_PT_Ligne_1[L_Index];

	}

	UINT16 L_Offset = NOMBRE_ELEMENTS - NOMBRE_COLONNES;
	T_CARACTERE_ECRAN L_Caractere = {.Attribut = 0x07, .Caractere = ' '};


	for (L_Index = 0; L_Index < NOMBRE_COLONNES; L_Index++) {
		Buf_Map_Video[L_Offset] = L_Caractere;
		Current_Buffer->listBuffers[Current_Buffer->currentScreenIndex].Cellules[L_Offset].Caractere = ' ';
		Current_Buffer->listBuffers[Current_Buffer->currentScreenIndex].Cellules[L_Offset].Attribut = 0x07;
		L_Offset++;
	}
	Buf_ECRAN_Curseur_X = 0;
	Current_Buffer->listBuffers[Current_Buffer->currentScreenIndex].Curseur_X = 0;
}

//--------------------------------------------------------------------------------------------------

inline void Buf_Positionne_Curseur(BYTE P_X, BYTE P_Y) {
	Buf_ECRAN_Curseur_X = P_X;
	Buf_ECRAN_Curseur_Y = P_Y;
	Current_Buffer->listBuffers[Current_Buffer->currentScreenIndex].Curseur_X = P_X;
	Current_Buffer->listBuffers[Current_Buffer->currentScreenIndex].Curseur_Y = P_Y;
}
//--------------------------------------------------------------------------------------------------

inline void Buf_Affiche_Curseur() {
#define outb(P_Port,P_Valeur) asm volatile ("outb %%al,%%dx" ::"d"(P_Port), "a"(P_Valeur));

	UINT16 L_Offset;
	L_Offset = (Buf_ECRAN_Curseur_Y * NOMBRE_COLONNES) + Buf_ECRAN_Curseur_X;

	outb(0x3d4, 0x0f);
	outb(0x3d5, (BYTE) L_Offset);
	outb(0x3d4, 0x0e);
	outb(0x3d5, (BYTE) (L_Offset >> 8));
}




//--------------------------------------------------------------------------------------------------

inline void Buf_Repositionne_Curseur() {

	if (Buf_ECRAN_Curseur_X >= NOMBRE_COLONNES) {
		Buf_ECRAN_Curseur_X = 0;
		Buf_ECRAN_Curseur_Y++;
		Current_Buffer->listBuffers[Current_Buffer->currentScreenIndex].Curseur_X = 0;
		Current_Buffer->listBuffers[Current_Buffer->currentScreenIndex].Curseur_Y = Buf_ECRAN_Curseur_Y;
	}
	if (Buf_ECRAN_Curseur_Y >= NOMBRE_LIGNES) {
		Buf_Defilement_Haut();
		Buf_ECRAN_Curseur_Y--;
		Current_Buffer->listBuffers[Current_Buffer->currentScreenIndex].Curseur_Y = Buf_ECRAN_Curseur_Y;
	}
}


//--------------------------------------------------------------------------------------------------
inline void Buf_Affiche_Caractere(UCHAR P_Caractere) {
	UINT16 L_Offset;
	switch (P_Caractere) {
		case 10: Buf_ECRAN_Curseur_Y++;
			Buf_ECRAN_Curseur_X = 0;
			Current_Buffer->listBuffers[Current_Buffer->currentScreenIndex].Curseur_X = Buf_ECRAN_Curseur_X;
			Current_Buffer->listBuffers[Current_Buffer->currentScreenIndex].Curseur_Y = Buf_ECRAN_Curseur_Y;
			break;
		case 13: Buf_ECRAN_Curseur_X = 0;
			Current_Buffer->listBuffers[Current_Buffer->currentScreenIndex].Curseur_X = Buf_ECRAN_Curseur_X;
			break;
		case 9: Buf_ECRAN_Curseur_X = Buf_ECRAN_Curseur_X + TAILLE_TABULATION;
			Buf_ECRAN_Curseur_X = Buf_ECRAN_Curseur_X % NOMBRE_COLONNES;
			Current_Buffer->listBuffers[Current_Buffer->currentScreenIndex].Curseur_X = Buf_ECRAN_Curseur_X;
			break;
		default: L_Offset = (Buf_ECRAN_Curseur_Y * NOMBRE_COLONNES) + Buf_ECRAN_Curseur_X;
			Buf_Map_Video[L_Offset].Attribut = Buf_Attribut_Actuel;
			Buf_Map_Video[L_Offset].Caractere = P_Caractere;
			Current_Buffer->listBuffers[Current_Buffer->currentScreenIndex].Cellules[L_Offset].Caractere = 'B';
			Current_Buffer->listBuffers[Current_Buffer->currentScreenIndex].Cellules[L_Offset].Attribut = Buf_Attribut_Actuel;
			Buf_ECRAN_Curseur_X++;
			Current_Buffer->listBuffers[Current_Buffer->currentScreenIndex].Curseur_X = Buf_ECRAN_Curseur_X;
	}
	Buf_Repositionne_Curseur();
	Buf_Affiche_Curseur();
}



//--------------------------------------------------------------------------------------------------

void Buf_Affiche_Chaine(UCHAR P_Chaine[]) {
	int L_Index = 0;

	while (P_Chaine[L_Index] != 0) {
		Buf_Affiche_Caractere(P_Chaine[L_Index]);
		L_Index++;
	}
	Buf_Affiche_Curseur();
}

//--------------------------------------------------------------------------------------------------

void Buf_Regle_Couleur(BYTE P_Attribut) {
	Buf_Attribut_Actuel = P_Attribut;
}


//--------------------------------------------------------------------------------------------------

BYTE Buf_Donne_Curseur_X() {
	return Buf_ECRAN_Curseur_X;
}

//--------------------------------------------------------------------------------------------------

BYTE Buf_Donne_Curseur_Y() {
	return Buf_ECRAN_Curseur_Y;
}

//--------------------------------------------------------------------------------------------------

void Buf_Affiche_Liste_Caracteres(UCHAR P_Caractere, UINT16 P_Repetition) {
	int L_Index;

	for (L_Index = 0; L_Index < P_Repetition; ++L_Index) {
		Buf_Affiche_Caractere(P_Caractere);
	}
}
