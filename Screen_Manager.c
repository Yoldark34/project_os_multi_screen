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
	g_screenBuffers->currentScreenIndex = 9999; //Remplacer par -1
	g_screenBuffers->currentWritingIndex = 9999; //Remplacer par -1
	g_screenBuffers->lastScreenIndex = 9999; //Remplacer par -1
	g_pidOutScreens->maxUsedIndex = 0;

	Attach_Pid_To_Screen(1, 1);
	Attach_Pid_To_Screen(2, 2);
	Attach_Pid_To_Screen(3, 2);

	SetCurrentBuffers(g_screenBuffers);
	switchScreen(0);
}

void Attach_Pid_To_Screen(UINT32 p_pid, int p_screenId) {
	assoc test;
	test.pid = p_pid;
	test.screenIndex = p_screenId;
	g_pidOutScreens->listAssocs[g_pidOutScreens->maxUsedIndex] = test;
	g_pidOutScreens->maxUsedIndex++;
	if (g_screenBuffers->listBuffers[p_screenId].init == false) {
		InitBuffer();
	}
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
		g_screenBuffers->lastScreenIndex = g_screenBuffers->currentScreenIndex; //9999 lors du premier appel Remplacer par -1
		g_screenBuffers->currentScreenIndex = p_screenIndex;

		BufferToScreen();
	}
}

void switchWritingContextFromPid(UINT32 P_Pid) {
	int L_Index = getScreenIndexFromPid(P_Pid);

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
		g_screenBuffers->listBuffers[g_screenBuffers->currentScreenIndex].Cellules[l_indexCellule].Caractere = ' ';
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

	SetBuffer();
}

