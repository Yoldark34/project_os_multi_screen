
#ifndef CALLBACK_EXCEPTION_H
#define	CALLBACK_EXCEPTION_H

void CallBack_Erreur_Division(UINT32);
void CallBack_Mise_Au_Point(UINT32);
void CallBack_INT3(UINT32);
void CallBack_Debordement(UINT32);
void CallBack_Limite(UINT32);
void CallBack_CodeOP_Invalide(UINT32);
void CallBack_DNA(UINT32);
void CallBack_Double_Faute(UINT32);
void CallBack_Depassement(UINT32);
void CallBack_TSS_Invalide(UINT32);
void CallBack_Segment_Non_Present(UINT32);
void CallBack_Segment_Pile(UINT32);
void CallBack_Violation_Protection(UINT32);
void CallBack_Defaut_De_Page(UINT32);
void CallBack_CoProcesseur(UINT32);


#endif	/* CALLBACK_EXCEPTION_H */

