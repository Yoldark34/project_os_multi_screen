/* 
 * File:   API.h
 * Author: Administrateur
 *
 * Created on 28 avril 2013, 22:34
 */

#ifndef API_H
#define	API_H
#include "type.h"

void API_clrscr(); 
void API_puts(char* P_Message, BYTE P_Couleur); 
void API_Multi_Caractere(char P_Caractere, int P_Nombre);
int API_Attendre_Scan_Code(); 

#endif	/* API_H */

