#include "Screen_Manager.h"
#include "Processus.h"
#include "Outils.h"
#define NB_SCREEN 12

typedef struct assoc {
	UINT32 pid;
	int screenIndex;
} assoc;

typedef struct pidOutScreen {
	int maxUsedIndex;
	assoc listAssocs[NB_PROCESS_MAX];
} pidOutScreen;

typedef struct ScreenBuffer {
	int currentScreenIndex;
	screen_buffer listBuffers[NB_SCREEN];
} ScreenBuffer;

pidOutScreen pidOutScreens;
ScreenBuffer screenBuffers;

int getScreenIndexFromPid(UINT32 p_pid);
void switchScreen(int p_screenIndex);
void BufferToScreen();

int getScreenIndexFromPid(UINT32 p_pid) {
	int l_screenIndex = -1;
	int l_index = 0;
	while (l_screenIndex == -1 && l_index < NB_PROCESS_MAX) {
		if (pidOutScreens.listAssocs[l_index].pid == p_pid) {
			l_screenIndex = pidOutScreens.listAssocs[l_index].screenIndex;
		}
		l_index++;
	}
	if (l_screenIndex == -1) {
		l_screenIndex = screenBuffers.currentScreenIndex;
		pidOutScreens.maxUsedIndex++;
		pidOutScreens.listAssocs[pidOutScreens.maxUsedIndex].pid = p_pid;
		pidOutScreens.listAssocs[pidOutScreens.maxUsedIndex].screenIndex = screenBuffers.currentScreenIndex;
	}
	return l_screenIndex;
}

void switchScreen(int p_screenIndex) {
	Affiche_Chaine(Entier_Vers_Chaine(p_screenIndex));
	/*
	if (screenBuffers.currentScreenIndex != p_screenIndex) {
		screenBuffers.currentScreenIndex = p_screenIndex;
		BufferToScreen();
	}
	//*/
}

void BufferToScreen() {
	int l_indexLigne;
	int l_indexColonne;
	Efface_Ecran();
	for (l_indexLigne = 0; l_indexLigne < NOMBRE_LIGNES; l_indexLigne++) {
		for (l_indexColonne = 0; l_indexColonne < NOMBRE_COLONNES; l_indexColonne++) {
			Positionne_Curseur(l_indexColonne, l_indexLigne);
			Regle_Couleur(screenBuffers.listBuffers[screenBuffers.currentScreenIndex].Cellules[l_indexLigne][l_indexColonne].Attribut);
			Affiche_Caractere(screenBuffers.listBuffers[screenBuffers.currentScreenIndex].Cellules[l_indexLigne][l_indexColonne].Caractere);
		}
	}
	Positionne_Curseur(screenBuffers.listBuffers[screenBuffers.currentScreenIndex].Curseur_X, screenBuffers.listBuffers[screenBuffers.currentScreenIndex].Curseur_Y);
}
