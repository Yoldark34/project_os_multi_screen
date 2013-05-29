#include "Screen_Manager.h"
#include "Processus.h"
#include "Outils.h"
#include "PLAN_MEMOIRE.h"
#include "Buffer_Manager.h"


typedef struct assoc {
	UINT32 pid;
	int screenIndex;
} assoc;

typedef struct pidOutScreen {
	int maxUsedIndex;
	assoc listAssocs[NB_PROCESS_MAX];
} pidOutScreen;

pidOutScreen* g_pidOutScreens;
ScreenBuffers* g_screenBuffers;

int getScreenIndexFromPid(UINT32 p_pid);
void switchScreen(int p_screenIndex);
void BufferToScreen();
void InitBuffer();

void Initialisation_Multi_Screen() {
	int l_index = 0;
	UINT32 L_Adresse_Table = ADRESSE_MULTI_SCREEN;
	Creation_Tables_Pages_Process(L_Adresse_Table);
	g_pidOutScreens = (pidOutScreen*) (ADRESSE_MULTI_SCREEN + (sizeof (pidOutScreen)));
	g_screenBuffers = (ScreenBuffers*) (ADRESSE_MULTI_SCREEN + (sizeof (pidOutScreen) + (sizeof (ScreenBuffers))));
	for (l_index = 0; l_index < NB_SCREEN; l_index++) {
		g_screenBuffers->listBuffers[l_index].init = false;
	}
	g_screenBuffers->currentScreenIndex = -1;
	g_screenBuffers->currentWritingIndex = -1;
	g_screenBuffers->lastScreenIndex = -1;
	g_pidOutScreens->maxUsedIndex = 0;

	SetCurrentBuffers(g_screenBuffers);
	switchScreen(0);
}

boolean ThisPidIsDisplayedOnTheCurentScreen(UINT32 p_pid) {
	if (getScreenIndexFromPid(p_pid) == g_screenBuffers->currentScreenIndex) {
		return true;
	}
	return false;
}

int getScreenIndexFromPid(UINT32 p_pid) {
	int l_screenIndex = -1;
	int l_index = 0;
	int test = 0;
	while (l_screenIndex == -1 && l_index < g_pidOutScreens->maxUsedIndex) {
		if (g_pidOutScreens->listAssocs[l_index].pid == p_pid) {
			l_screenIndex = g_pidOutScreens->listAssocs[l_index].screenIndex;
		}
		l_index++;
	}
	if (l_screenIndex == -1) {
		l_screenIndex = g_screenBuffers->currentScreenIndex;
		g_pidOutScreens->listAssocs[g_pidOutScreens->maxUsedIndex].pid = p_pid;
		g_pidOutScreens->listAssocs[g_pidOutScreens->maxUsedIndex].screenIndex = g_screenBuffers->currentScreenIndex;
		g_pidOutScreens->maxUsedIndex++;
	}
	g_screenBuffers->currentWritingIndex = l_screenIndex;

	return l_screenIndex;
}

void switchScreen(int p_screenIndex) {
	if (g_screenBuffers->currentScreenIndex != p_screenIndex) {
		g_screenBuffers->lastScreenIndex = g_screenBuffers->currentScreenIndex; //-1 lors du premier appel
		g_screenBuffers->currentScreenIndex = p_screenIndex;
		//Affiche_Chaine("\n\n\n\n switch current context : ");
		//Affiche_Chaine(Entier_Vers_Chaine(p_screenIndex));
		BufferToScreen();
	}
}

void switchWritingContextFromPid(UINT32 P_Pid) {
	int L_Index = getScreenIndexFromPid(P_Pid);
	//Affiche_Chaine("\n\n\n\n switch writing context : ");
	//Affiche_Chaine(Entier_Vers_Chaine(L_Index));
	if (g_screenBuffers->currentWritingIndex != L_Index) {
		g_screenBuffers->currentWritingIndex = L_Index;
	}
}

void InitBuffer() {
	int l_indexCellule;

	g_screenBuffers->listBuffers[g_screenBuffers->currentScreenIndex].Attribut = 0x07;
	g_screenBuffers->listBuffers[g_screenBuffers->currentScreenIndex].Curseur_X = 0;
	g_screenBuffers->listBuffers[g_screenBuffers->currentScreenIndex].Curseur_Y = 0;

	for (l_indexCellule = 0; l_indexCellule < NOMBRE_ELEMENTS; l_indexCellule++) {
		g_screenBuffers->listBuffers[g_screenBuffers->currentScreenIndex].Cellules[l_indexCellule].Caractere = '*';
		g_screenBuffers->listBuffers[g_screenBuffers->currentScreenIndex].Cellules[l_indexCellule].Attribut = g_screenBuffers->listBuffers[g_screenBuffers->currentScreenIndex].Attribut;
	}
	g_screenBuffers->listBuffers[g_screenBuffers->currentScreenIndex].init = true;
}

void BufferToScreen() {
	boolean init = false;

	if (g_screenBuffers->listBuffers[g_screenBuffers->currentScreenIndex].init == false) {
		InitBuffer();
		init = true;
	}
	//Efface_Ecran();
	//Positionne_Curseur(0, 0);

	SetBuffer();

	/*if (init) {
		switchWritingContextFromPid(1);
		Buf_Regle_Couleur(ROUGE);
		Buf_Affiche_Chaine("\n\n\n\n");
		Buf_Affiche_Chaine("Ecran : ");
		Buf_Affiche_Chaine(Entier_Vers_Chaine((g_screenBuffers->currentScreenIndex) + 1));
	}*/
}

