#ifndef HARD_8042_CLAVIER_H
#define	HARD_8042_CLAVIER_H
#include "type.h"

UINT16 Lecture_Scan_Code();
UINT16 Attendre_Scan_Code();
UINT16 Attendre_Touche_Relache();

#endif	/* HARD_8042_CLAVIER_H */

