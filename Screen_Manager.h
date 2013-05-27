/* 
 * File:   Screen_Buffer.h
 * Author: Admin
 *
 * Created on 27 mai 2013, 14:35
 */

#ifndef SCREEN_BUFFER_H
#define	SCREEN_BUFFER_H
#include "ECRAN.h"

typedef struct screen_buffer {
	T_CARACTERE_ECRAN Cellules[NOMBRE_LIGNES][NOMBRE_COLONNES];
	BYTE Curseur_X;
	BYTE Curseur_Y;
	BYTE Attribut;
} screen_buffer;

#endif	/* SCREEN_BUFFER_H */

