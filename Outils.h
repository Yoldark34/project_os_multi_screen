#ifndef OUTILS_H
#define	OUTILS_H
#include "TYPE.h"





 UINT32 Taille_Chaine(UCHAR P_Chaine[]);
 UCHAR* Entier_Vers_Chaine(UINT32 P_Valeur);
 UCHAR* Entier_Vers_Chaine_Hexa(UINT32 P_Valeur, BYTE P_Nombre_Octets);
 void Copier_Memoire(BYTE* P_Destination, BYTE* P_Source, UINT32 P_Taille);
 void Initialise_Memoire(BYTE* P_Destination, BYTE P_Valeur, UINT32 P_Taille);
 
 
#endif	/* OUTILS_H */

