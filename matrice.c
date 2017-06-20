#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"
#include "stackCella.h"


/* creazione matrice dinamica*/  
void creaMatrice (int riga, int colonna,cella **matrix){
	int i,j;
	for (i = 0; i < riga; ++i){
		matrix[i] = (cella *)malloc(colonna * sizeof(struct tcella));
	} 
	for(i=0; i<riga;i++){
		for(j=0;j<colonna;j++){
			matrix[i][j].contenuto=0;
			matrix[i][j].aperta=0;
		}
	}
	
}

/*controllo  se una data posizione è all'interno della matrice 1 posizione valida 0 non valida*/
int isValid(int riga,int colonna, int maxRighe, int maxColonne){
	if(riga>=0 && riga<=maxRighe && colonna>=0 && colonna<=maxColonne){
		return 1;
	}
	else{
		return 0;
	}
}


/*calolo il numero di celle vicine a una mina */
void preparaCampo (int riga, int colonna,int numeroMine,cella **matrix, stackcella c){
	int appRiga, appColonna,i,j,k;
	Info cell;
	for (k=0; k<numeroMine;k++){
		pop(&c, &cell);
		appRiga = cell.riga;
		appColonna = cell.colonna; 
		for (i = appRiga-1; i<=appRiga+1; i++){
			for (j = appColonna-1; j<=appColonna+1; j++){
				if (isValid(i,j,riga,colonna)){
					if(matrix[i][j].contenuto != -1){
						matrix[i][j].contenuto++;
					}
				}
			}
		}
	}	
}


/*posizione mine nella matrice a random e incremento */
void posiziona_Mine_Random (int riga, int colonna,int numeroMine, cella **matrix){
	int posRiga,posColonna;
	int mine = numeroMine;
	stackcella appoggio;
	Info pos;
	/*genero un numero casuale per riga e colonna controllo se quel posto matrix.contenuto == -1 non inserisco 
	 * altrimenti matrix.contenuto = -1 esegue questo fino a che numero di mine è maggiore di 0*/
	while (numeroMine >0){
		posRiga = rand()%(riga+1-0)+0;
		posColonna = rand()%(colonna+1-0)+0;
		if (matrix[posRiga][posColonna].contenuto == 0){
			matrix[posRiga][posColonna].contenuto = -1;
			pos.riga = posRiga;
			pos.colonna = posColonna;
			pos.ricorsione = 0;
			push(&appoggio, pos);
			numeroMine--;
		}
	}
	preparaCampo(riga,colonna,mine,matrix, appoggio);
}


/*creazione da file */
void inseriscimineDaFile(FILE *fp, int riga, int colonna, cella **matrix){
    int x,y;
    int numeroMine = 0;
    stackcella appoggio; 
    Info pos;
    while(!feof(fp) && fscanf(fp, "%d, %d", &x, &y)==2){
           matrix[x][y].contenuto = -1;
            pos.riga = x;
			pos.colonna = y;
			pos.ricorsione = 0;
			push(&appoggio, pos); 
			numeroMine++;
    }
    preparaCampo(riga,colonna,numeroMine,matrix, appoggio);
    
}

void crea_out(cella **mat, int righe, int colonne){
    FILE *f;
    f=fopen("output.txt","w");
    if(f==NULL){
        printf("Il file output non puo essere scritto\n");
    }
    else{
        int i, j;
        fprintf(f,"%d, %d\n", righe, colonne);
        fprintf(f, "\n");
        /*bisogna scrivere la dimensione della matrice come prima riga*/
        for(i=0; i<righe; i++){
            for (j=0; j<colonne; j++){
                if (mat[i][j].contenuto==-1)
                    fprintf(f,"%d, %d\n", i, j);
            }
        }
        fclose(f);
    }
    
}




void print(cella **mat, int riga,int colonna){
		int i,j;
		for(i=0; i<=riga;i++){
			for(j=0;j<=colonna;j++){
				printf("%d ", mat[i][j].contenuto);
			}
			printf("\n");
		}
}


void printStato(cella **mat, int riga,int colonna){
		int i,j;
		for(i=0; i<=riga;i++){
			for(j=0;j<=colonna;j++){
				if (mat[i][j].contenuto == -2)
						printf("? ");
					else if(mat[i][j].contenuto == -1){
						printf("* ");
					}
					else if (mat[i][j].contenuto == 0){
						printf("v ");
					}
					else{
						printf("%d ", mat[i][j].contenuto);
					}
			}
			printf("\n");
		}
}


void printFineTurno(cella **mat, int riga,int colonna){
		int i,j;
        printf("\n___________________________________\n");
        printf("Stato partita:\n");
		for(i=0; i<=riga;i++){
			for(j=0;j<=colonna;j++){
				if (mat[i][j].aperta==1 || mat[i][j].aperta == -2){
					if (mat[i][j].aperta == -2)
						printf("? ");
					else if(mat[i][j].contenuto == -1){
						printf("* ");
					}
					else if (mat[i][j].contenuto == 0){
						printf("v ");
					}
					else{
						printf("%d ", mat[i][j].contenuto);
					}
				}
				else{
					printf("%d ", mat[i][j].aperta);
				}
			}
			printf("\n");
		}
}


/* FASE DI GIOCO */

/* parametri riga nrighe matrice, colonna ncolonne matrice, matrix matrice, rigaPart e colPar da dove iniziare a aprirex */
void apriVuote(int riga, int colonna,cella **matrix, int rigaPart, int colPart,stackcella *mosse){
	Info app;
	if (isValid(rigaPart,colPart,riga,colonna) && matrix[rigaPart][colPart].aperta == 0  ){
		if(matrix[rigaPart][colPart].contenuto == 0){
			app.riga = rigaPart;
			app.colonna = colPart;
			app.ricorsione = 1;
			push(mosse,app);
			matrix[rigaPart][colPart].aperta = 1;
			apriVuote(riga,colonna,matrix,rigaPart-1,colPart-1,mosse);
			apriVuote(riga,colonna,matrix,rigaPart,colPart-1,mosse);
			apriVuote(riga,colonna,matrix,rigaPart+1,colPart-1,mosse);
			apriVuote(riga,colonna,matrix,rigaPart+1,colPart,mosse);
			apriVuote(riga,colonna,matrix,rigaPart+1,colPart+1,mosse);
			apriVuote(riga,colonna,matrix,rigaPart,colPart+1,mosse);
			apriVuote(riga,colonna,matrix,rigaPart-1,colPart+1,mosse);
			apriVuote(riga,colonna,matrix,rigaPart-1,colPart,mosse);
		}
	}
	if (isValid(rigaPart,colPart,riga,colonna) && matrix[rigaPart][colPart].contenuto>= 0){
		app.riga = rigaPart;
			app.colonna = colPart;
			app.ricorsione = 1;
			push(mosse,app);
			matrix[rigaPart][colPart].aperta = 1;
	}
}

/* funzione per inserimento bandierina*/
void inserisciBandierina(cella **matrix, int riga, int colonna){
	matrix[riga][colonna].aperta = -2;
}

/*funzione per rimozione bandierina*/
void rimuoviBandierina(cella **matrix, int riga, int colonna){
	matrix[riga][colonna].aperta = 0;
}


/*Funzione che annulla la mossa*/
void annullaMossa (int riga, int colonna, cella **matrix, stackcella *mosse, int daAnnullare){
	Info metti;
	while (daAnnullare>0){
		pop(mosse, &metti);
		matrix[metti.riga][metti.colonna].aperta = 0;
		if(*mosse){
			pop(mosse, &metti);
			if (metti.ricorsione == 1){
				while(metti.ricorsione == 1 && (*mosse)){
					matrix[metti.riga][metti.colonna].aperta = 0;
					pop(mosse,&metti);
				}
			}
			else{
				push(mosse, metti);
			}	
		}
		daAnnullare--;		
	}
}




/*funzione per eseguire la mossa se restituisce 1 allora mossa a buon fine altrimenti ho trovato una bomba*/
int eseguiMossa (int riga, int colonna, cella **matrix, stackcella *canc){
	int eseguita=1;
	Info mossa; 
	pop(canc, &mossa);
	if(matrix[mossa.riga][mossa.colonna].contenuto == -1){ /* trovato fiore */
		matrix[mossa.riga][mossa.colonna].aperta = 1;
		push(canc, mossa);
		eseguita = 0;
	}
	else if(matrix[mossa.riga][mossa.colonna].contenuto == 0){ /* casella vuota */
		apriVuote(riga,colonna,matrix,mossa.riga,mossa.colonna,canc);
		push(canc, mossa);
	}
	else if(matrix[mossa.riga][mossa.colonna].contenuto >=1){ /* vicino bomba */
		matrix[mossa.riga][mossa.colonna].aperta = 1;
		push(canc, mossa);
	}
	return eseguita;
}



/*controllo vittoria 1 se vinto 0 se continuo a giocare*/
int isVittoria (int riga, int colonna, cella **mat){
	int vittoria =1;
	int i,j;
	for (i=0; i<=riga && vittoria; i++){
		for(j=0; j<=colonna && vittoria;j++){
			if (mat[i][j].aperta == 0 ){
				vittoria = 0;	
			}
		}
	}
	return vittoria;
}



int main(){
	int lines, columns, daRi, daCo, annullamenti,bomba, x,k, vai,opzione;
	int continua = 0;
	int contaErrori= 0;
	int quit = 0;
	int finegioco = 0;
	int numeroPartite = 0;
	cella **matrix;
	Info ce;
	stackcella mossa = empty_stack();
	FILE *fp;
	
	/*inizializzazione gioco creazione matrice e scelta */
	while(finegioco == 0){
	    printf("\nBenvenuto in Campo Minato!\n\n");
	    printf("___________________________________\n");
		printf("Seleziona modalità creazione campo di gioco: \n 1. crea campo random \n 2. crea campo da file\n 3. esci\n");
	    printf("___________________________________\n");
	    printf("digita la tua opzione: ");
		scanf("%d", &opzione);
	    printf("\n");
	    while (opzione>3 || opzione<0){
	        printf("____________________________________\n");
	        printf ("\n");
	        printf ("Opzione inesistente! \n");
	        printf ("Digitare il numero dell'opzione: ");
	        scanf ("%d", &opzione);
	        printf ("\n");
	    }
		if (opzione == 1){
	        printf("___________________________________\n");
			printf("Hai scelto creazione random\n");
			printf("Inserisci numero righe: ");
			scanf("%d", &lines);
			printf("Inserisci numero colonne: ");
			scanf("%d", &columns);
			printf("Inserisci numero errori massimo: ");
			scanf("%d", &annullamenti);
			do{
				printf("Inserisci il numero di bombe minore di %d: ", lines*columns);
				scanf("%d", &bomba);
			}
			while (bomba >= lines*columns);
			matrix =(cella**) malloc (lines * sizeof( struct tcella *)); 
			creaMatrice(lines,columns,matrix);
			posiziona_Mine_Random(lines-1,columns-1,bomba,matrix);
			crea_out(matrix, lines,columns);	
		}
		else if(opzione == 2){
	        printf("___________________________________\n");
			printf("Hai scelto creazione da file\n");
			fp = fopen("output.txt" , "r");  
			if(fp == NULL){
				perror("Ci sono stati problemi nella lettura del file, controlla che esista il file output.txt\n");
				return(-1);
			}
			else {
                printf("Il campo è stato caricato correttamente da fine!\n");
                printf("___________________________________\n");
				fscanf(fp, "%d, %d", &lines, &columns);
				matrix =(cella**) malloc (lines * sizeof( struct tcella *)); 
				creaMatrice(lines,columns,matrix);
			}
			printf("Inserisci numero errori massimo: ");
			scanf("%d", &annullamenti);
			inseriscimineDaFile(fp,lines-1,columns-1,matrix);
		}
		else if(opzione == 3){
			finegioco = 1;
		}
		/* fine inizializzaione matrice*/
			
			/*inizo fase gioco*/
				while (continua == 0 && quit == 0 && finegioco == 0){
			        do{
						printf("\n___________________________________\n");
						printf("Seleziona cosa fare\n 1. mossa\n 2. metti bandierina\n 3. rimuovi bandierina\n 4. ricomincia una nuova partita\n 5. chiudi il gioco\n");
						printf ("Digitare il numero dell'opzione: ");
						scanf("%d", &k);
					}
					while(k<=0 || k>5);				
					if (k==1){
						do{
                            printf("\n___________________________________\n");
							printf("Inserisci il numero della riga (compreso tra 0 e %d): ", lines-1);
							scanf("%d", &daRi);
						}
						while(daRi<0 || daRi >lines-1);
						do{
							printf("Inserisci il numero della colonna (compreso tra 0 e %d): ", columns-1);
							scanf("%d", &daCo);
						}
						while(daCo<0 || daCo >columns-1);
						ce.riga = daRi;
						ce.colonna = daCo;
						ce.ricorsione = 0;
						push(&mossa,ce);
						x = eseguiMossa(lines-1,columns-1, matrix, &mossa);
						if (x == 0){
							contaErrori++;
							printFineTurno(matrix,lines-1,columns-1);
							if (contaErrori > annullamenti){
								printf ("Hai raggiunto il massimo di errori\n");
								quit =-1;
							}
							else{
                                printf("____________________________________\n");
								printf("Hai trovato una mina, scegli cosa fare:\n 1. annullo le ultime %d mosse\n 2. finisci la partita\n",contaErrori);
								printf ("Digitare il numero dell'opzione: ");
								scanf("%d", &vai);
								if (vai == 1){
									if(contaErrori <= annullamenti){
										annullaMossa(lines-1,columns-1,matrix,&mossa, contaErrori);
									}
								}
								else {
									quit = -1;
								}
								
							}	
						}
					}
					else if(k==2){
						do{
							printf("Inserisci la riga dove inserire la bandierina (compreso tra 0 e %d): ", lines-1);
							scanf("%d", &daRi);
						}
						while(daRi<0 || daRi >lines-1);
						do{
							printf("Inserisci la colonna dove inserire la bandierina (compreso tra 0 e %d): ", columns-1);
							scanf("%d", &daCo);
						}
						while(daCo<0 || daCo >columns-1);
						inserisciBandierina(matrix,daRi,daCo);
					}
					else if(k==3){
						do{
							printf("Inserisci la riga della bandierina da rimuovere (compreso tra 0 e %d): ", lines-1);
							scanf("%d", &daRi);
						}
						while(daRi<0 || daRi >lines-1);
						do{
							printf("Inserisci la colonna della bandierina da rimuovere (compreso tra 0 e %d): ", columns-1);
							scanf("%d", &daCo);
						}
						while(daCo<0 || daCo >columns-1);
						rimuoviBandierina(matrix,daRi,daCo);
					}
					else if(k == 4){
						quit = -2; /* finisce il gioco su richiesta*/
						svuotastack (mossa);
					}
					else if(k == 5){
						finegioco = 1; /* finisce il gioco su richiesta*/
						numeroPartite++;
					}
					continua = isVittoria(lines-1,columns-1,matrix);
					if (quit != -1 && quit != -2){
						printFineTurno(matrix, lines-1,columns-1);
					}
			}
			if (continua == 1){
                printf("\n___________________________________\n");
				printf("Partita finita, hai vinto!\n");
				printf("Scegli cosa fare:\n 1. Ricomincia una partita\n 2. Concludi gioco\n");
                printf ("Digitare il numero dell'opzione: ");
				scanf("%d", &opzione);
				numeroPartite++;
			}
			else if (quit ==-1) {
                printf("\n___________________________________\n");
				printf("Hai perso :-(\n");
				printStato(matrix,lines-1,columns-1);
                printf("\n___________________________________\n");
				printf("Scegli cosa fare:\n 1. Ricomincia una partita\n 2. Concludi gioco\n");
                printf ("Digitare il numero dell'opzione: ");
				scanf("%d", &opzione);
				numeroPartite++;
			}
			else if (quit == -2){
				opzione = 0;
				numeroPartite++;
			}
			if (opzione == 2 || k == 5 || opzione ==3){
				finegioco = 1;
			}
			else{
				continua = 0;
				quit = 0;
				contaErrori = 0;
				mossa = empty_stack();
				free(matrix);
			}
	}
    printf("____________________________________\n");
	printf("Hai deciso di conludere il gioco dopo aver giocato %d partite\n", numeroPartite);
    printf("\n");
	if (numeroPartite ==0){
		svuotastack(mossa);
		free(matrix);	
	}
	return 0;
}




