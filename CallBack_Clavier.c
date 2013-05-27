#include "type.h"
#include "HARD_8042_Clavier.h"

/*
 EAX :
 * 0 : Lecture_Scan_Code
 *     retourne AL : scan code
 * 1 : Attendre_Touche:
 *    retourne AL : scan code
 * 2 : Attendre_Touche_Relache:
 *       retourne AL : scan code
 */

UINT16 CallBack_INT_Clavier(UINT32 P_EAX)
{
    switch (P_EAX) {
        case 0 : return Lecture_Scan_Code(); 
        case 1 : return Attendre_Scan_Code();
        case 2 : return Attendre_Touche_Relache();
    }
    return;
}
