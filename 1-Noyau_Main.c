#include "type.h"
#include "Ecran.h"
#include "Outils.h"
#include "Info_Boot.h"
#include "Init_GDT.h"
#include "Init_IDT.h"
#include "MACRO.h"
#include "PLAN_MEMOIRE.h"
#include "HARD_8042_Clavier.h"
#include "Pagination.h"
#include "Tas_Pages_Systeme.h"
#include "Allocation_Pages.h"
#include "Init_TSS.h"
#include "Processus.h"
#include "Ordonnanceur.h"
#include "BitMap_Memoire.h"
#include "API.h"
#include "Screen_Manager.h"




void OS_Main();

//----------------------------------------------------------------------------

void Affiche_Informations_Boot(T_BOOT_INFO* P_Info) {
	if ((P_Info->Flags & BOOT_INFO_MEMOIRE) == BOOT_INFO_MEMOIRE) {
		Regle_Couleur(BLANC);
		Affiche_Chaine(">>>Memoire detectee : ");
		UINT32 L_Taille_Memoire = P_Info->Adresse_Basse + P_Info->Adresse_Haute + 1024;
		Regle_Couleur(BLEU | LUMINEUX);
		Affiche_Chaine(Entier_Vers_Chaine(L_Taille_Memoire / 1024));
		Affiche_Chaine(" Mo \n");
	}
}
//----------------------------------------------------------------------------

void Affiche_Message(UCHAR* P_Message, UCHAR* P_Etat) {
	Regle_Couleur(BLANC);
	Affiche_Chaine(P_Message);
	Positionne_Curseur(78 - Taille_Chaine(P_Etat), Donne_Curseur_Y());
	Regle_Couleur(VERT | LUMINEUX);
	Affiche_Chaine(P_Etat);
	Affiche_Caractere('\n');
}
//---------------------------------------------------------------------------- 



//----------------------------------------------------------------------------

void OS_Start(T_BOOT_INFO* P_Info) {
	Efface_Ecran();
	Affiche_Message(">>>BOOT JLV OS V1 - 2011 Via GRUB : ", "OK");
	Affiche_Informations_Boot(P_Info);

	Initialisation_GDT();
	Affiche_Message(">>>Initialisation de la GDT : ", "OK");

	//Initialiser le pointeur pile.
	// NE PAS ETRE DANS UNE FONCTION CAR à la sortie d'une fonction, le regsitre ESP est réinitialisé à la valeur précédant l'appel.
	//  INITIALISE_SS_ESP(SELECTEUR_STACK_NOYAU,DEBUT_STACK_NOYAU);


	INITIALISE_SS_ESP(SELECTEUR_STACK_NOYAU, HAUT_STACK_NOYAU)
	OS_Main();
	asm("NOP");
}
//------------------------------------------------------------------------------

void Processus_Idle() {
	char* L_Message = (char*) 0x0002000; // on stocke la chaine en DS:xxxxx
	// ce code étant éxécuté en ring 3
	// on est donc dans le segment data du process
	// l'adresse 0 est en réalité "BASE_DATA_USER"
	int i = 0;
	while (1) {
		API_puts((char*) 0x0002000, 15);

	}
}

volatile void Processus_1() {
	char* L_Message = (char*) 0x0002000; // on stocke la chaine en DS:xxxxx
	int i = 0;
	while (1) {

		API_puts((char*) 0x0002000, 4);

	}

}

volatile void Processus_2() {
	char* L_Message = (char*) 0x0002000; // on stocke la chaine en DS:xxxxx
	int i = 0;
	while (1) {
		API_puts((char*) 0x0002000, 5);

		// ceci génère une exception de protection :
		// L_Message=(char*)0x000;
		// *L_Message=10;
	}

}

volatile void Processus_3() {
	char* L_Message = (char*) 0x0002000; // on stocke la chaine en DS:xxxxx

	while (1) {

		//API_puts((char*)0x0002000,6);
	}

}



//------------------------------------------------------------------------------

void OS_Main() {

	Affiche_Message(">>>Initialisation de la Pile (ESP) : ", "OK");

	Initialisation_IDT();
	Affiche_Message(">>>Initialisation de la IDT : ", "OK");

	Initialisation_TSS();
	Affiche_Message(">>>Initialisation du TSS : ", "OK");

	Initialisation_Pagination();
	Affiche_Message(">>>Initialisation de la Pagination : ", "OK");

	Initialisation_Tables_Pages_Process();
	Affiche_Message(">>>Initialisation des tables de pages process : ", "OK");

	Initialisation_BitMap_Memoire();
	Affiche_Message(">>>Initialisation du BitMap Memoire : ", "OK");


	Inititialisation_8259A();
	Affiche_Message(">>>Initialisation du PIC 8259A : ", "OK");

	Initialisation_8253(1193);
	Affiche_Message(">>>Initialisation du controleur 8253 : ", "OK");

	Initialisation_Info_Processus();
	Affiche_Message(">>>Initialisation Info Process : ", "OK");

	Initialisation_Multi_Screen();
	Affiche_Message(">>>Initialisation Multi Screen : ", "OK");

	Numero_Process_Courrant = 0;

	// ici nous sommes encore dans le noyau, 
	// les datas des processus sont donc chargées via le segmant data de l'OS
	// il faut donc prévoir le décalage  BASE_DATA_USER
	Charge_Processus(0, (UINT32) Processus_Idle, 8);
	Affiche_Message(">>> Chargement code process 0 ", "OK");
	Copier_Memoire_Process(0, (BYTE*) BASE_DATA_USER + 0x0002000, "Idle\n", 6);
	Affiche_Message(">>> Init data process 0 ", "OK");

	Charge_Processus(1, (UINT32) Processus_1, 8);
	Affiche_Message(">>> Chargement code process 1 ", "OK");
	Copier_Memoire_Process(1, (BYTE*) BASE_DATA_USER + 0x0002000, "-----Tache 1\n", 14);
	Affiche_Message(">>> Init data process 1 ", "OK");

	Charge_Processus(2, (UINT32) Processus_2, 8);
	Affiche_Message(">>> Chargement code process 2 ", "OK");
	Copier_Memoire_Process(2, (BYTE*) BASE_DATA_USER + 0x0002000, "----------Tache 2\n", 19);
	Affiche_Message(">>> Init data process 2 ", "OK");

	Charge_Processus(3, (UINT32) Processus_3, 8);
	Affiche_Message(">>> Chargement code process 3 ", "OK");
	Copier_Memoire_Process(3, (BYTE*) BASE_DATA_USER + 0x0002000, "---------------Tache 3\n", 24);
	Affiche_Message(">>> Init Data process 3 ", "OK");


	volatile T_INFO_PROCESSUS* L_Processus;
	L_Processus = Donne_Info_Processus(0);

	//AUTORISE_INTERRUPTION;
	//Attendre_Touche_Relache();

	Periode_Ordonnanceur = 10L;
	Donne_La_Main_Au_Processus(0); // donne la main en faisant via le schéduleur => les int sont donc activées

	while (1);
}
