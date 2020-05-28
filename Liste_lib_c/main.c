/* Inclusione delle librerie standard */
#include <stdio.h>
#include <stdlib.h>

/* Inclusione della libreria per la gestione della lista */
#include "lista.h"

/* Dichiarazione delle funzioni */
void menu();
void selezione();
int acquisisci(int);

/* Funzione principale */
int main() {
	
	/* Selezione degli algoritmi */
	selezione();	

	return 0;
}

/* Funzione per la selezione dell'operazione desiderata */
void selezione() {

	nodo_t *lista = NULL; 	/* puntatore al primo elemento */
	int scelta;		/* var. per contere la scelta */
	int lettura;		/* var. validazione degli input */
	char rimosso;		/* var. per svuotare il buffer */
	
	/* Acquisizione della scelta con validazione */
	do {
		
		menu();		/* stampa le possibili scelte */
		lettura = scanf("%d", &scelta); /* acquisizione */

		/* Verifica la validità degli input */
		if((lettura != 1) || ((scelta < 0) || (scelta > 9))) {
			printf("\nScelta non presente!\n");
			do
				rimosso = getchar();
			while(rimosso != '\n');
		}

		/* Distinzione delle operazioni da eseguire */
		printf("\n");
		switch(scelta) {
			case 1:
				/* Aggiunge testa alla lista */
				in_testa(acquisisci(2), &lista);
				break;
			case 2:
				/* Aggiunge coda alla lista */ 
				in_coda(acquisisci(2), &lista);
				break;
			case 3:
			case 4:
				/* Inserisce un nuovo elemento
				basandosi sulla posizione di
				un altro già presente */
				ins_spec(acquisisci(2), 
					 acquisisci(0), 
					 &lista, scelta);
				break;
			case 5: 
				/* Rimuove testa alla lista */
				rim_testa(&lista);
				break;
			case 6:
				/* Rimuove coda alla lista */
				rim_coda(&lista);
				break;
			case 7:
				/* Rimuove elemento specifico */
				rim_elem(acquisisci(2), &lista);
				break;
			case 8:
			case 9:
				/* Visita la lista in avanti o 
				all'indietro, in base alla scelta */
				visita(acquisisci(1), lista,
					scelta);
				break;
			case 0:
				/* Condizione di terminazione */
				break;
		}

		/* Stampa della lista attuale */
		printf("\nLista");
		mostra(lista);
		printf(" -> NULL\n\n");
	
	/* Condizioni di ripetizione */
	} while (scelta != 0 || lettura != 1 ||
		 scelta > 9);		
}

/* Funzione per l'acquisizione dei valori */
int acquisisci(int selez) {

	int lettura;		/* var. validazione degli input */
	int pos;		/* var. per il valore acquisito */
	char rimosso;		/* var. per svuotare il buffer */

	/* Acquisizione del nuovo valore con validazione */
	do {
		/* Con selez = 1, richiede la posizione */
		if(selez == 1)
			printf("Inserire posizione\n");

		/* Con sele = 2, chiede l'elemento
		su cui agire */
		else if(selez == 2)
			printf("Inserire elemento\n");

		/* Con selez != 1, richiede il valore 
		da prendere come riferimento */
		else
			printf("Inserire valore di riferimento \n");
		
		lettura = scanf("%d", &pos);

		/* Verifica la validità degli input */
		if(lettura != 1 || pos < 0) {
			printf("\nScelta non presente\n");
			do
				rimosso = getchar();
			while(rimosso != '\n');
		}

	/* Condizioni di ripetizione */
	} while (lettura != 1 || pos < 0);

	/* Restituisce il valore inserito */
	return pos;	
}

/* Funzione per la stampa delle opzioni */
void menu() {
	
	printf("\n********** MENU **********\n");
	printf("1. Inserimento testa\n");
	printf("2. Inserimento coda\n");
	printf("3. Inserimento prima elemento\n");
	printf("4. Inserimento dopo elemento\n"); 
	printf("5. Rimozione testa\n6. Rimozione coda\n");
	printf("7. Rimozione elemento\n");
	printf("8. Visita all'avanti\n");
	printf("9. Visita all'indietro\n");
	printf("0. Per terminare\n");
	
}
