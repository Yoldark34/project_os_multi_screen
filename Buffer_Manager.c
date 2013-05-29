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
ScreenBuffers* Screen_Buffers;

//-------------------------------------------------
// Variables globales internes
//--------------------------------------------------
BYTE Buf_Attribut_Actuel = 0x07;



//#################################################################################################

void Buf_Save_Actual_Screen_To_Buffer();


void SetCurrentBuffers(ScreenBuffers* P_Screen_Buffers) {
	Screen_Buffers = P_Screen_Buffers;
}

void SetBuffer() {
	Buf_Map_Video = (T_CARACTERE_ECRAN*)&(Screen_Buffers->listBuffers[Screen_Buffers->currentScreenIndex].Cellules);
	Buf_Charge_Buf_Actuel_To_Screen();
}

void Buf_Efface_Ecran() {
	if (Screen_Buffers->currentWritingIndex == Screen_Buffers->currentScreenIndex) {
		Efface_Ecran();
	} else {
		UINT16 L_Index;
		for (L_Index = 0; L_Index < NOMBRE_ELEMENTS; L_Index++) {
			Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Cellules[L_Index].Attribut = 0x07;
			Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Cellules[L_Index].Caractere = ' ';
		}
		Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Curseur_X = 0;
		Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Curseur_Y = 0;
	}
}

//--------------------------------------------------------------------------------------------------

void Buf_Remplir_Ecran(UCHAR P_Caractere, BYTE P_Attribut) {
	if (Screen_Buffers->currentWritingIndex == Screen_Buffers->currentScreenIndex) {
		Remplir_Ecran(P_Caractere, P_Attribut);
	} else {
		UINT16 L_Index;
		for (L_Index = 0; L_Index < NOMBRE_ELEMENTS; L_Index++) {
			Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Cellules[L_Index].Attribut = P_Attribut;
			Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Cellules[L_Index].Caractere = P_Caractere;
		}
		Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Curseur_X = 0;
		Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Curseur_Y = 0;
	}
}

//--------------------------------------------------------------------------------------------------

void Buf_Defilement_Haut() {
	BYTE* L_PT_Ligne_0 = (BYTE*)&(Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Cellules);
	BYTE* L_PT_Ligne_1 = (BYTE*)&(Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Cellules) + NOMBRE_BYTE_PAR_LIGNE;

	UINT16 L_Index;
	for (L_Index = 0; L_Index < NOMBRE_BYTE_TOTAL - NOMBRE_BYTE_PAR_LIGNE; L_Index++) {
		L_PT_Ligne_0[L_Index] = L_PT_Ligne_1[L_Index];

	}

	UINT16 L_Offset = NOMBRE_ELEMENTS - NOMBRE_COLONNES;
	T_CARACTERE_ECRAN L_Caractere = {.Attribut = 0x07, .Caractere = ' '};


	for (L_Index = 0; L_Index < NOMBRE_COLONNES; L_Index++) {
		Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Cellules[L_Offset] = L_Caractere;
		L_Offset++;
	}
	Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Curseur_X = 0;
}

//--------------------------------------------------------------------------------------------------

inline void Buf_Positionne_Curseur(BYTE P_X, BYTE P_Y) {
	if (Screen_Buffers->currentWritingIndex == Screen_Buffers->currentScreenIndex) {
		Positionne_Curseur(P_X, P_Y);
	} else {
		Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Curseur_X = P_X;
		Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Curseur_Y = P_Y;
	}
}
//--------------------------------------------------------------------------------------------------

inline void Buf_Repositionne_Curseur() {

	if (Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Curseur_X >= NOMBRE_COLONNES) {
		Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Curseur_X = 0;
		Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Curseur_Y++;
	}
	if (Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Curseur_Y >= NOMBRE_LIGNES) {
		Buf_Defilement_Haut();
		Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Curseur_Y--;
	}
}


//--------------------------------------------------------------------------------------------------

inline void Buf_Affiche_Caractere(UCHAR P_Caractere) {
	if (Screen_Buffers->currentWritingIndex == Screen_Buffers->currentScreenIndex) {
		Affiche_Caractere(P_Caractere);
	} else {
		UINT16 L_Offset;
		switch (P_Caractere) {
			case 10: Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Curseur_Y++;
				Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Curseur_X = 0;
				break;
			case 13: Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Curseur_X = 0;
				break;
			case 9: Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Curseur_X = Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Curseur_X + TAILLE_TABULATION;
				Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Curseur_X = Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Curseur_X % NOMBRE_COLONNES;
				break;
			default: L_Offset = (Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Curseur_Y * NOMBRE_COLONNES) + Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Curseur_X;
				Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Cellules[L_Offset].Attribut = Buf_Attribut_Actuel;
				Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Cellules[L_Offset].Caractere = P_Caractere;
				Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Curseur_X++;
		}
		Buf_Repositionne_Curseur();
	}
}



//--------------------------------------------------------------------------------------------------

void Buf_Affiche_Chaine(UCHAR P_Chaine[]) {
	if (Screen_Buffers->currentWritingIndex == Screen_Buffers->currentScreenIndex) {
		Affiche_Chaine(P_Chaine);
	} else {
		//Affiche_Chaine("\n\n\n je buffer dans :");
		//Affiche_Chaine(Entier_Vers_Chaine(Screen_Buffers->currentWritingIndex));
		int L_Index = 0;

		while (P_Chaine[L_Index] != 0) {
			Buf_Affiche_Caractere(P_Chaine[L_Index]);
			L_Index++;
		}
	}
}

//--------------------------------------------------------------------------------------------------

void Buf_Regle_Couleur(BYTE P_Attribut) {
	if (Screen_Buffers->currentWritingIndex == Screen_Buffers->currentScreenIndex) {
		Regle_Couleur(P_Attribut);
	} else {
		Buf_Attribut_Actuel = P_Attribut;
	}
}


//--------------------------------------------------------------------------------------------------

BYTE Buf_Donne_Curseur_X() {
	if (Screen_Buffers->currentWritingIndex == Screen_Buffers->currentScreenIndex) {
		return Donne_Curseur_X();
	} else {
		return Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Curseur_X;
	}
}

//--------------------------------------------------------------------------------------------------

BYTE Buf_Donne_Curseur_Y() {
	if (Screen_Buffers->currentWritingIndex == Screen_Buffers->currentScreenIndex) {
		return Donne_Curseur_Y();
	} else {
		return Screen_Buffers->listBuffers[Screen_Buffers->currentWritingIndex].Curseur_Y;
	}
}

//--------------------------------------------------------------------------------------------------

void Buf_Affiche_Liste_Caracteres(UCHAR P_Caractere, UINT16 P_Repetition) {
	if (Screen_Buffers->currentWritingIndex == Screen_Buffers->currentScreenIndex) {
		Affiche_Liste_Caracteres(P_Caractere, P_Repetition);
	} else {
		int L_Index;

		for (L_Index = 0; L_Index < P_Repetition; ++L_Index) {
			Buf_Affiche_Caractere(P_Caractere);
		}
	}
}

void Buf_Charge_Buf_Actuel_To_Screen() {
	if (Screen_Buffers->currentScreenIndex != Screen_Buffers->lastScreenIndex) {
		Buf_Save_Actual_Screen_To_Buffer();
	}
	int L_Index;
	for (L_Index = 0; L_Index < NOMBRE_ELEMENTS; L_Index++) {
		Map_Video[L_Index] = Screen_Buffers->listBuffers[Screen_Buffers->currentScreenIndex].Cellules[L_Index];
	}
	Positionne_Curseur(Screen_Buffers->listBuffers[Screen_Buffers->currentScreenIndex].Curseur_X, Screen_Buffers->listBuffers[Screen_Buffers->currentScreenIndex].Curseur_Y);
	Affiche_Curseur();
}

void Buf_Save_Actual_Screen_To_Buffer() {
	if (Screen_Buffers->lastScreenIndex == 9999) {//Seulement lors de la premiere utilisation pendant l'initialisation du multi screen Remplacer par -1
		Screen_Buffers->lastScreenIndex = Screen_Buffers->currentScreenIndex;

	}
	int L_Index;
	for (L_Index = 0; L_Index < NOMBRE_ELEMENTS; L_Index++) {
		Screen_Buffers->listBuffers[Screen_Buffers->lastScreenIndex].Cellules[L_Index] = Map_Video[L_Index];
	}

	Screen_Buffers->listBuffers[Screen_Buffers->lastScreenIndex].Curseur_X = Donne_Curseur_X();
	Screen_Buffers->listBuffers[Screen_Buffers->lastScreenIndex].Curseur_Y = Donne_Curseur_Y();
}
