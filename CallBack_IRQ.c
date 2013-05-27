#include "PLAN_MEMOIRE.h"
#include "Ecran.h"
#include "Outils.h"
#include "MACRO.h"
#include "CallBack_IRQ.h"
#include "HARD_8042_Clavier.h"
#include "Ordonnanceur.h"

boolean Ctrl = false;

//##############################################################################
// QUAND CES ROUTINES S'EXECUTENT, NOUS SOMMES DANS LE RING 0
//  CS= SELECTEUR_CODE_NOYAU
//  
// les autres selecteurs (DS) n'ont pas changé !
//##############################################################################

//==============================================================================
// IRQ 0 : Horloge
//==============================================================================

void CallBack_IRQ0()
{                      
  INITIALISER_DS(SELECTEUR_DATA_NOYAU);

    
 Ordonnanceur();
 //schedule();
}  


//------------------------------------------------------------------------------
void CallBack_IRQ1()
{
   INITIALISER_DS(SELECTEUR_DATA_NOYAU);
	UINT16 L_Code = Lecture_Scan_Code();
	switch (L_Code) {
		case 78:
			Periode_Ordonnanceur += 5;
			if (Periode_Ordonnanceur > 400L) Periode_Ordonnanceur = 400L;
			break;
		case 74:
			Periode_Ordonnanceur -= 5;
			if (Periode_Ordonnanceur < 6L) Periode_Ordonnanceur = 6L;
			break;
		case 29://LCtrl down
			Ctrl = true;
			break;
		case 157://LCtrl up
			Ctrl = false;
			break;
		case 59://F1
		case 60://F2
		case 61://F3
		case 62://F4
		case 63://F5
		case 64://F6
		case 65://F7
		case 66://F8
		case 67://F9
		case 68://F10
			if (Ctrl) {
				switchScreen(L_Code - 59);
			}
			break;
		case 87://F11
		case 88://F12
			if (Ctrl) {
				switchScreen(L_Code - 77);
			}
			break;
		default:
			break;
	}
   
}
//------------------------------------------------------------------------------
void CallBack_IRQ3()
{
  INITIALISER_DS(SELECTEUR_DATA_NOYAU);
  Affiche_Chaine("IRQ3\n");

}
//------------------------------------------------------------------------------
void CallBack_IRQ4()
{
  INITIALISER_DS(SELECTEUR_DATA_NOYAU);
  Affiche_Chaine("IRQ4\n");


}
//------------------------------------------------------------------------------
void CallBack_IRQ5()
{
  INITIALISER_DS(SELECTEUR_DATA_NOYAU);
  Affiche_Chaine("IRQ5\n");


}
//------------------------------------------------------------------------------
void CallBack_IRQ6()
{
   INITIALISER_DS(SELECTEUR_DATA_NOYAU);  
   Affiche_Chaine("IRQ6\n");


}
//------------------------------------------------------------------------------
void CallBack_IRQ7()
{
   INITIALISER_DS(SELECTEUR_DATA_NOYAU);
	//Affiche_Chaine("IRQ7\n");


}
//------------------------------------------------------------------------------
void CallBack_IRQ8()
{
  INITIALISER_DS(SELECTEUR_DATA_NOYAU);  
  Affiche_Chaine("IRQ8\n");


}
//------------------------------------------------------------------------------
void CallBack_IRQ9()
{
   INITIALISER_DS(SELECTEUR_DATA_NOYAU);  
   Affiche_Chaine("IRQ9\n");

  
}
//------------------------------------------------------------------------------
void CallBack_IRQ10()
{
                       // Sauvergader tous les registres
  INITIALISER_DS(SELECTEUR_DATA_NOYAU);
  Affiche_Chaine("IRQ10\n");


}
//------------------------------------------------------------------------------
void CallBack_IRQ11()
{
  INITIALISER_DS(SELECTEUR_DATA_NOYAU);
  Affiche_Chaine("IRQ11\n");


}
//------------------------------------------------------------------------------
void CallBack_IRQ12()
{
  INITIALISER_DS(SELECTEUR_DATA_NOYAU);
  Affiche_Chaine("IRQ12\n");


}
//------------------------------------------------------------------------------
void CallBack_IRQ13()
{
   INITIALISER_DS(SELECTEUR_DATA_NOYAU);
  Affiche_Chaine("IRQ13\n");


}
//------------------------------------------------------------------------------
void CallBack_IRQ14()
{
   INITIALISER_DS(SELECTEUR_DATA_NOYAU); 
   Affiche_Chaine("IRQ14\n");


}
//------------------------------------------------------------------------------
void CallBack_IRQ15()
{
  INITIALISER_DS(SELECTEUR_DATA_NOYAU);
  Affiche_Chaine("IRQ15\n");


}
//------------------------------------------------------------------------------

void CallBack_Defaut()
{
                        // Sauvergader tous les registres
  INITIALISER_DS(SELECTEUR_DATA_NOYAU);
  Affiche_Chaine("Interruption \n");


}
//------------------------------------------------------------------------------

