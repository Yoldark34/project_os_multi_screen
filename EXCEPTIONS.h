
#ifndef EXCEPTIONS_H
#define	EXCEPTIONS_H

#define NOMBRE_EXCEPTIONS 15

#define EXCEPT_ERREUR_DIVISION          0
#define EXCEPT_MISE_AU_POINT            1

#define EXCEPT_INT3                     3
#define EXCEPT_DEBORDEMENT              4
#define EXCEPT_LIMITE                   5
#define EXCEPT_CODEOP_INVALIDE          6
#define EXCEPT_DNA                      7
#define EXCEPT_DOUBLE_FAUTE             8
#define EXCEPT_DEPASSEMENT              9
#define EXCEPT_TSS_INVALIDE             10
#define EXCEPT_SEGMENT_NON_PRESENT      11
#define EXCEPT_SEGMENT_PILE             12
#define EXCEPT_VIOLATION_PROTECTION     13
#define EXCEPT_DEFAUT_DE_PAGE           14

#define EXCEPT_COPROCESSEUR             16



void Exception_Erreur_Division();
void Exception_Mise_Au_Point();
void Exception_INT3();
void Exception_Debordement();
void Exception_Limite();
void Exception_CodeOP_Invalide();
void Exception_DNA();
void Exception_Double_Faute();
void Exception_Depassement();
void Exception_TSS_Invalide();
void Exception_Segment_Non_Present();
void Exception_Segment_Pile();
void Exception_Violation_Protection();
void Exception_Defaut_De_Page();
void Exception_CoProcesseur();

void Exception_Par_Defaut();

#endif	/* EXCEPTIONS_H */

