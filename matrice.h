#include "stackCella.h"
#ifndef MATRICE
#define MATRICE

/*matrice è di tipo cella*/
struct tcella { 
	int contenuto; /*contenuto cella  MINA = -1 VUOTA =0 VICINE  = numero */ 
	int aperta;/* Aperta = 1 NON APERTA = 0 Bandierina = -2   */
};
typedef struct tcella cella;

void creaMatrice (int riga, int colonna,cella **matrix);
int isValid(int riga,int colonna, int maxRighe, int maxColonne);
void preparaCampo (int riga, int colonna,int numeroMine,cella **matrix, stackcella c);
void posiziona_Mine_Random (int riga, int colonna,int numeroMine, cella **matrix);
void inseriscimine(FILE *fp, int riga, int colonna, cella **matrix);
void print(cella **mat, int riga,int colonna);
void printStato(cella **mat, int riga,int colonna);
void printFineTurno(cella **mat, int riga,int colonna);
void apriVuote(int riga, int colonna,cella **matrix, int rigaPart, int colPart,stackcella *mosse);
void inserisciBandierina(cella **matrix, int riga, int colonna);
void rimuoviBandierina(cella **matrix, int riga, int colonna);
void annullaMossa (int riga, int colonna, cella **matrix, stackcella *mosse, int daAnnullare);
int eseguiMossa (int riga, int colonna, cella **matrix, stackcella *canc);
int isVittoria (int riga, int colonna, cella **mat);
void crea_out(cella **mat, int righe, int colonne);
void inseriscimineDaFile(FILE *fp, int riga, int colonna, cella **matrix);
#endif
