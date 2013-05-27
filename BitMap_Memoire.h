
#ifndef BITMAP_MEMOIRE_H
#define	BITMAP_MEMOIRE_H

#include "PLAN_MEMOIRE.h"

extern UINT32 Nombre_Pages_Libres;

//------------------------------------------------------------------------------

#define BITMAP_MARQUE_RESERVATION(Page) ((BYTE*)ADRESSE_BITMAP_MEMOIRE)[(Page)>>3] |= (1<<((Page)%8));\
                                         
#define BITMAP_RESERVE_PAGE(Page)  BITMAP_MARQUE_RESERVATION(Page);\
                                   Nombre_Pages_Libres--;

#define BITMAP_MARQUE_LIBERATION(Page)  ((BYTE*)ADRESSE_BITMAP_MEMOIRE)[(Page)>>3] &= ~(1<<((Page)%8));\

#define BITMAP_LIBERE_PAGE(Page) BITMAP_MARQUE_LIBERATION(Page);\
                                 Nombre_Pages_Libres++;;

#define DONNE_ETAT_BITMAP(Index)        (( ((BYTE*)ADRESSE_BITMAP_MEMOIRE)[(Index)>>3] >> (Index%8) )&0x01)



//------------------------------------------------------------------------------
void Initialisation_BitMap_Memoire();


#define DEBUG_BITMAP_MEMOIRE

#endif	/* BITMAP_MEMOIRE_H */

