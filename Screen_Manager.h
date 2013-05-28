/* 
 * File:   Screen_Buffer.h
 * Author: Admin
 *
 * Created on 27 mai 2013, 14:35
 */

#ifndef SCREEN_BUFFER_H
#define	SCREEN_BUFFER_H
//#include "Buffer_Manager.h"
#include "Ecran.h"
#define NB_SCREEN 12

void Initialisation_Multi_Screen();

typedef struct buffer {
	T_CARACTERE_ECRAN Cellules[NOMBRE_ELEMENTS];
	BYTE Curseur_X;
	BYTE Curseur_Y;
	BYTE Attribut;
	boolean init;
} buffer;

typedef struct ScreenBuffers {
	int currentScreenIndex;
	int currentWritingIndex;
	buffer listBuffers[NB_SCREEN];
} ScreenBuffers;

#endif	/* SCREEN_BUFFER_H */

