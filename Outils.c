
#include "OUTILS.h" 

//-----------------------------------------------------------------------------------
//##############################################################################
#define TAILLE_MAXI_CHAINE_TMP 12
UCHAR Chaine_Temporaire_Char[TAILLE_MAXI_CHAINE_TMP];
//##############################################################################

//-----------------------------------------------------------------------------------
UINT32 Taille_Chaine(UCHAR P_Chaine[])
{
 UINT16 L_Taille=0;
   while (*P_Chaine !=0) {
      L_Taille++;
      P_Chaine++;
  }
  return L_Taille;
} 

//-----------------------------------------------------------------------------------
UCHAR* Entier_Vers_Chaine(UINT32 P_Valeur)
{
BYTE L_Octet;
INT16 L_Index=TAILLE_MAXI_CHAINE_TMP-2;
BYTE L_Digit=0;
   
  Chaine_Temporaire_Char[TAILLE_MAXI_CHAINE_TMP-1]=0;
  do {
   L_Octet = P_Valeur % 10;
   Chaine_Temporaire_Char[L_Index]=L_Octet+'0';
   P_Valeur=P_Valeur/10;
   L_Index--;
 } while (P_Valeur!=0);
  return (Chaine_Temporaire_Char+L_Index+1);
}

//-----------------------------------------------------------------------------------
UCHAR* Entier_Vers_Chaine_Hexa(UINT32 P_Valeur, BYTE P_Nombre_Octets)
{
BYTE L_Octet;
BYTE L_Index=0;
BYTE L_Digit=(P_Nombre_Octets<<1);

    if ((P_Nombre_Octets>0) && (P_Nombre_Octets<=4)) {
        do {
            L_Octet = P_Valeur & 0x0000000F;
            if (L_Octet<10) Chaine_Temporaire_Char[L_Digit-L_Index-1]=L_Octet+'0';
            else Chaine_Temporaire_Char[L_Digit-L_Index-1]=L_Octet-10+'A';

            L_Index++;
            P_Valeur=P_Valeur>>4;
            
        } while (L_Index<L_Digit);
        Chaine_Temporaire_Char[L_Digit]=0;
    } else Chaine_Temporaire_Char[0]=0;
    return Chaine_Temporaire_Char;
}

//-----------------------------------------------------------------------------------
void Copier_Memoire(BYTE* P_Destination, BYTE* P_Source, UINT32 P_Taille)
{   
 UINT32 L_Index=P_Taille;  
    while (L_Index) {
        L_Index--;
        P_Destination[L_Index]=P_Source[L_Index];
    }     
}

//-----------------------------------------------------------------------------------

/*
void* memcpy(void* P_Destination, const void* P_Source, UINT32 P_Taille)
{   
 UINT32 L_Index=P_Taille;  
    while (L_Index) {
        L_Index--;
        ((char*)P_Destination)[L_Index]=((char*)P_Source)[L_Index];
    }    
 return P_Destination;
}
*/
//-----------------------------------------------------------------------------------
 void Initialise_Memoire(BYTE* P_Destination, BYTE P_Valeur, UINT32 P_Taille)
 {
UINT32 L_Index=P_Taille;  
    while (L_Index) {
        L_Index--;
        P_Destination[L_Index]=P_Valeur;
    }     
}

