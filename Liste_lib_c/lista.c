/* Librerie standard */
#include <stdio.h>	
#include <stdlib.h>	

/* Definizione del nuovo tipo */
typedef struct nodo  {
	int dato;		/* valore del nodo */
	struct nodo* succ_p;	/* puntatore a elem. succ. */
	struct nodo* prec_p;	/* puntatore a elem. prec. */
}nodo_t;			/* ridefinizione del nuovo tipo */

/* Prototipi delle funzioni */

nodo_t *crea_nodo(int);
void in_testa(int, nodo_t **);
void in_coda(int, nodo_t **);
void mostra(nodo_t *);
void mostra_ind(nodo_t *);
void rim_testa(nodo_t **);
void rim_coda(nodo_t **);
void rim_elem(int, nodo_t **);
void ins_spec(int, int, nodo_t **, int);
void visita(int, nodo_t *, int);
int conta(nodo_t *, int);

/* Definizione delle funzioni */

/* Funzione per creare un nuovo nodo, 
la funzione riceve in input il valore da
aggiungere ed alloca lo spazio necessario
all'inserimento, i campi puntatore precedente
e successivo vengono inizializzati a NULL.
Viene restituito l'indirizzo del nuovo elemento */
nodo_t *crea_nodo(int x) {

	nodo_t *nuovo 		/* puntatore che ospiterà
				l'indirizzo del nuovo elem. */

		/* Viene allocato lo spazio necessario alla 
		creazione del nuovo elemento */
		= (nodo_t *)malloc(sizeof(nodo_t *));

	nuovo->dato = x;	/* il valore viene acquisito */
	
	/* I campi puntatore precedente e successivo vengono
	inizializzati a NULL */	
	nuovo->prec_p = nuovo->succ_p = NULL;

	/* Viene restituito l'indirizzo del nodo creato */
	return nuovo;
}

/* Corpo della funzione inserisci testa,
la quale riceve in input il valore da aggiungere e il 
riferimento alla struttura localizzata tramite il suo
primo elemento.
Viene invocata la funzione crea_nodo() per aggiungere
il nuovo elemento; quest'ultimo diviene la nuova testa,
mentre la precedente diviene l'elemento successivo ad essa. */
void in_testa(int x, nodo_t **testa) {

	/* Invocazione della funzione crea nodo */
	nodo_t *nuovo = crea_nodo(x);

	/* Caso lista inizialmente vuota, il nuovo elemento
	viene posizionato in testa */	
	if(*testa == NULL) {
		*testa = nuovo;
	}
	
	/* Se la lista non è vuota */
	else{
		/* Si crea lo spazio per il nuovo elemento
		all'indirizzo puntato da prec_p inizialmente
		settato a NULL */
		(*testa)->prec_p = nuovo;

		/* La vecchia testa diviene il secondo elem. */
		nuovo->succ_p = *testa;
	
		/* Viene aggiornata la nuova testa */		
		*testa = nuovo;	
	}
}

/* Funzione per inserire in coda, che riceve in input
il valore da inserire e il riferimento alla struttura.
Viene richiamata la funzione crea_nodo() per aggiungere
il nuovo nodo; in caso di lista vuota questo diventa la 
nuova testa; altrimenti si scorre la lista fino alla sua
fine, per poi inizializzare il puntatore succ_p (con valore
NULL) come nuovo elemento */
void in_coda(int x, nodo_t **testa) {

	/* Dichiarazione e inizializzazione del puntatore 
	interno alla funzione, che assume l'indirizzo del 
	primo elemento della lista.
	Questo viene utilizzato come puntatore ausiliario 
	per scorrere la lista ed aggingere l'elemento in coda */
	nodo_t *temp = *testa;	
			
	/* Invocazione della funzione crea_nodo() */
	/* La variabile *nuovo contiene 
	l'indirizzo del nuovo elemento generato dalla 
	funzione crea_nodo() */
	nodo_t *nuovo = crea_nodo(x);

	/* Se la lista è priva di elementi, è sufficiente
	aggiornare la testa della lista con l'indirizzo 
	restituito dalla funzione crea_nodo() */	
	if(*testa == NULL) {
		*testa = nuovo;
	}
	
	/* Se la lista non è vuota */
	else{
	
	/* Si scorre fino alla fine */
		while(temp->succ_p != NULL)
			temp = temp->succ_p;
	
	/* Il nuovo nodo viene inserito in coda */
		temp->succ_p = nuovo;
	
	/* Si collega il nuovo nodo con il suo precedente */
		nuovo->prec_p = temp;
	}
}

/* Funzione per rimuovere la testa, l'unico
parametro necessario è l'indirizzo della testa */
void rim_testa(nodo_t ** testa) {
	
	/* Se la lista è vuota si avverte l'utente */
	if(*testa == NULL)
		printf("Lista vuota!");
	
	/* Se la lista non è vuota */
	else {
		
		/* Si definisce un puntatore ausiliario, e lo 
		si inizializza con l'indirizzo della testa */
		nodo_t *temp = *testa;
	
		/* Caso lista composta da un solo elemento */
		if(temp->prec_p == temp->succ_p) {
			*testa = NULL;
			free(temp);
		}

		/* Caso lista con più elementi */
		else {
			/* Il secondo elemento viene aggiornato
			e diviene la nuova testa, mentre quella 
			precedente viene quindi eliminata */
			*testa = temp->succ_p;
			(*testa)->prec_p = NULL;
			free(temp);
		}
	}
}

/* Definizione del corpo della funzione per rimuovere
l'elemento in coda. In caso di lista vuota la funzione
termina alla prima riga ed il resto del codice non 
viene eseguito; in caso contrario si distingue il caso
di lista comprensiva di un solo elemento che viene quindi
rimosso. Nel caso con più di un elemento si scorre fino 
al carattere di terminazione (NULL)  */

void rim_coda(nodo_t **testa) {
	
	/* Se la lista è vuota la rimozione non può
	avere luogo, l'utente viene quindi avvisato */
	if(*testa == NULL)
		printf("Lista vuota!\n");
	
	/* Se la lista non è vuota */	
	else {
	
		/* Viene dichiarato un puntatore ausiliario che 
		assume l'indirizzo del primo elem. della lista */
		nodo_t *temp = *testa;

		/* Caso lista composta da un solo elemento */
		if(temp->prec_p == temp->succ_p) {
			*testa = NULL;
			free(temp);
		}

		/* Caso lista composta da più di un elem. */
		else {

			/* Si scorre l'intera lista */
			while(temp->succ_p != NULL)
				temp = temp->succ_p;
			
		/* Si elimina il collegamento all'ultimo elem.
		che può essere quindi rimosso */
		temp->prec_p->succ_p = NULL;
		free(temp);
		}
	}	
}

/* Definizione del corpo della funzione per rimuovere un
nodo a scelta dell'utente; la funzione accetta come parametri
il valore da rimuovere deciso dall'utente durante l'esecuzione
e il riferimento al primo elemento della lista.
Si distinguono le tre casistiche: lista vuota, lista con un solo
elemento e lista composta da più elementi.  */

void rim_elem(int x, nodo_t **testa) {		

	/* In caso di lista vuota la rimozione non può avere
	luogo, viene quindi notificato con un messaggio */
	if(*testa == NULL)
		printf("Lista vuota!");

	/* Caso in cui la lista consta di un solo elemento */
	else if((*testa)->succ_p == NULL)

		/* si invoca la funzione rim_testa() */
		rim_testa(*&testa); 

	/* Caso lista con piu di un elemento */
	else {
		
		/* Si definisce un puntatore ausiliario, che 
		viene inizializzato con l'indirizzo della testa */
		nodo_t *temp = *testa;	

		/* Variabile che contiene il valore di ritorno della
		funzione conta (funzione adibita a scandire le 
		occorrenze di elementi contenenti lo stesso
		valore) */
		int scelta = conta(*testa, x); 
		
		/* Variabile usata per controllare l'esecuzione
		della funzione */
		int rimosso = 1;
	
		/* Il ciclo continua fino a che non si incontra
		il valore da rimuovere o se, nel caso il valore
		non fosse presente, la variabile rimosso viene
		settata a 0. Nel contempo la variabile scelta
		deve rimanere diversa dal valore 1, la quale
		rappresenta la casistica in cui si incontrino più 
		occorrenze dello stesso valore */
		while(((temp->dato != x) &&
			 (rimosso != 0)) || (scelta != 1)) {

			/* Se scorrendo la lista incontro il valore 
			cercato ma l'occorrenza di questo non è 
			quella desiderata, si decrementa la var.
			scelta di un unità */
			if((temp->dato == x) && (scelta != 1))
				scelta--;
			
			/* Caso in cui scorrendo tutta la lista 
			il valore non viene trovato nemmeno una
			volta e si notifica con un messaggio */
			if(temp->succ_p == NULL) {
				printf("Valore non trovato!\n");

				/* Se rimosso viene impostato a 0
				l'esecuzione della funzione
				termina */
				rimosso = 0;
			}			
			else
				/* Incremento del ciclo iterativo */
				temp = temp->succ_p;		
		}
		
		/* Se l'elemento da eliminare è stato trovato */
		if(rimosso != 0) {
			
			/* L'elemento da rimuovere è situato
			in testa alla lista */
			if(temp == *testa) {

				/* Il secondo elemento della lista
				viene aggiornato a nuova testa,
				e la precedente può essere quindi
				rimossa */
				*testa = (*testa)->succ_p;
				
				/* Si aggiorna il marcatore di 
				fine lista della nuova testa */
				(*testa)->prec_p = NULL;
				free(temp);
			}

			/* Caso in cui l'elemento da rimuovere 
			è situato in coda */
			else if(temp->succ_p == NULL)

				/* Si invoca la funzione per 
				rimuovere un elem. dalla coda */
				rim_coda(*&testa);
				
			/* Caso in cui l'elemento da rimuovere non si
			trova agli estremi della lista */
			else {				
				/* Si aggiorna il puntatore a 
				elemento precedente del nodo 					successivo a quello da eliminare,
				che viene fatto	puntare al nodo che 					precede temp */
				temp->succ_p->prec_p = temp->prec_p;
				
				/* Lo stesso tipo di aggiornamento
				del collegamento risulta
				necessario per il nodo che precede
				quello da eliminare */
				temp->prec_p->succ_p = temp->succ_p;
				free(temp);
			}
		}	
	}
}

/* Funzione per inserire un nuovo elemento subito prima o subito
dopo un valore di riferimento. La funzione acquisisce come
parametri un intero da inserire, il valore a cui fare riferimento,
il primo nodo della lista ed il valore necessario per permettere la 
scelta del tipo di inserimento (prima/dopo) */
void ins_spec(int x, int val_rif, nodo_t **testa, int selez) {
	
	/* Var. puntatore per contenere l'indirizzo del nuovo
	elemento */
	nodo_t *elem = NULL;

	/* Variabile usata per gestire l'uscita dalla funzione */
	int esci = 0;
	
	/* In caso di lista vuota la rimozione non può avere
	luogo, viene quindi notificato con un messaggio */
	if(*testa == NULL) {
		printf("Lista vuota!\n");
		printf("Il valore %d viene inserito in testa\n", x);
		
		/* Si richiama la funzione per la creazione di
		un nuovo nodo */
		elem = crea_nodo(x);

		/* L'elemento inserito diventa la nuova testa */
		*testa = elem;
	}
	else {

		/* Puntatore ausiliario per scorrere la lista */
		nodo_t *temp1 = *testa;

		/* Secondo puntatore ausiliario per la creazione 
		del nuovo nodo */
		nodo_t *temp2 = *testa;

		/* Variabile che contiene il valore di ritorno della
		funzione conta (funzione adibita a scandire le 
		occorrenze di elementi contenenti lo stesso
		valore) */
		int scelta = conta(*testa, val_rif);

		/* Continua a iterare fino a quando non trova
		il valore richiesto oppure fino ad arrivare
		alla fine della lista; allo stesso tempo il ciclo
		continua fino a quando la var. scelta ha un valore
		diverso da 1.  */
		while(((temp1->dato != val_rif) && 
			(esci == 0)) || (scelta != 1)) {

			/* Quando trova un nodo nella lista
			contenente un valore uguale a quello di
			riferimento, scelta viene decrementato
			di un unità */
			if(temp1->dato == val_rif)
				scelta--;
			
			/* Se arriva fino a fine della lista allora
			il valore di riferimento non è presente */
			if(temp1->succ_p == NULL) {

				/* Notifica con un messagio */
				printf("Il valore %d non è presente",
					val_rif);

				/* La var. esci viene impostata
				ad 1, questo consente di terminare
				l'esecuzione della funzione */
				esci = 1;
			}
			else

				/* Incremento del while */
				temp1 = temp1->succ_p;

		}

		/* Se la variabile selez ha valore 3, l'inserimento
		avrà luogo subito prima del valore usato come
		riferimento */
		if(selez == 3) {

			/* Se l'elemento di riferimento si trova in
			cima alla lista */
			if((temp1->prec_p == NULL) && (esci == 0))
			
				/* Viene invocata la funzione per
				aggiungere un nuovo elemento 
				in testa */
				in_testa(x, &*testa);
	 
			/* Caso in cui l'elemento da rimuovere non
			sitrova agli estremi della lista */
			else if(esci == 0) {

				/* Viene invocata la funzione
				che genera un nuovo nodo */
				elem = crea_nodo(x);

				/* Il puntatore temp2 viene
				associato al campo puntatore
				precedente di temp1 */
				temp2 = temp1->prec_p;
			
				/* Il nuovo elemento diventa il nodo 
				precedente a temp1 */
				temp1->prec_p = elem;

				/* Il campo puntatore al
				nodo successivo	del nuovo elemento
				viene associato a temp1 */
				elem->succ_p = temp1;
			
				/* Viene definito il collegamento
				con il nodo che precede quello
				appena creato, che viene
				associato a temp2 */
				elem->prec_p = temp2;
			
				/* temp2 viene collegato al nodo
				appena creato che lo succede */
				temp2->succ_p = elem;
			}
		}

		/* Se la variabile selez ha valore diverso da 3,
		l'inserimento del nuovo elem. avrà luogo subito
		dopo il valore di riferimento */
		else {

			/* Se l'elemento di riferimento si trova
			in coda */
			if((temp1->succ_p == NULL) && (esci == 0))

				/* L'elemento viene aggiunto in coda
				attraverso l'invocazione della
				funzione in_coda() */
				in_coda(x, &*testa);

			/* Se l'elemento di riferimento non si trova
			in coda */
			else if(esci == 0){

				/* Invoca la funzione per creare un
				nuovo nodo */
				elem = crea_nodo(x);

				/* Il puntatore temp2 viene
				associato al campo puntatore
				successivo di temp1 */
				temp2 = temp1->succ_p;
			
				/* Il nuovo elemento diventa il nodo 
				successivo a temp1 */
				temp1->succ_p = elem;

				/* Il campo puntatore al nodo
				precedente del nuovo elemento
				viene associato	a temp1 */
				elem->prec_p = temp1;

				/* Viene definito il collegamento
				con il nodo che succede quello
				appena creato,che viene associato
				a temp2 */
				elem->succ_p = temp2;

				/* temp2 viene collegato al nodo
				appena creato che lo precede */
				temp2->prec_p = elem;
			}		
		}
	}
}

/* Funzione di visita della lista, la quale riceve in 
input la posizione del nodo da cui iniziare la visita, la testa
della lista e un valore usato per scegliere la direzione da
seguire (avanti/indietro) */
void visita(int posizione, nodo_t *testa, int direz) {
	
	/* Puntatore ausiliario per scorrere la lista */
	nodo_t *corr = NULL;

	/* Variabile usata per notificare l'assenza 
	della posizione richiesta dall'utente */
	int errore = posizione;

	/* Ciclo iterativo, il puntatore ausiliario viene 
	inizializzato con l'indirizzo del primo elemento della
	lista; si scorre la lista fino a quando la variabile
	posizione non risulta essere uguale ad 1, questo implica
	l'arrivo nella posizione richiesta dall'utente */
	for(corr = testa; ((corr != NULL) && (posizione != 1));
		corr = corr->succ_p)
		
		/* La var. posizione viene decrementata di una 
		unità ad ogni passo del ciclo */ 		
		posizione--;

	/* Caso in cui si scorre fino al termine della lista,
	senza raggiungere la posizione richiesta dall'utente */
	if(corr == NULL) 
		
		/* Viene notificato un messaggio di errore */
		printf("Posizione %d non presente\n", errore);
	else {

		/* Visita della lista */
		printf("Visita");

		/* Se la var. direz ha valore 8,
		la visita viene effettuata all'avanti */
		if(direz == 8)

			/* Si invoca la funzione mostra,
			che visualizza la lista in avanti
			partendo dalla posizione del
			puntatore ausiliario corr */
			mostra(corr);
			
		/* Se la var. direz ha valore diverso da 8,
		la visita viene effettuata all'indietro */
		else
				
			/* Si invoca la funzione mostra_ind,
			che visualizza la lista all'indietro
			partendo dalla posizione del
			puntatore ausiliario corr */
			mostra_ind(corr);
		
		/* Lascia uno spazio */
		printf("\n");
	}
}

/* Funzione utilizzata per contare le occorrenze, i parametri 
necessari risultano essere il primo nodo della lista e il valore
di cui si vogliono contare le occorrenze */
int conta(nodo_t *testa, int val) {

	/* Puntatore ausiliario per lo scorrimento della lista */
	nodo_t *corr = testa;

	/* Variabile contatore delle occorrenze di un valore
	all'interno della lista */
	int n_occ = 0;

	/* Valore di ritorno della funzione, che contiene la 
	scelta dell'utente nel caso di più occorrenze dello
	stesso valore nei nodi della lista */
	int scelta = 1;

	/* Ciclo che scorre l'intera la lista, lo scopo è
	quello di contare le occorrenze all'interno della 
	lista del valore richiesto dall'utente */
	while(corr != NULL) {

		/* Ogni volta che la variabile val viene 
		incontrata in un nodo */
		if(corr->dato == val)

			/* La var. n_occ viene incrementata di
			un unità */
			n_occ++;

		/* Incremento del while */
		corr = corr->succ_p;
	}
	
	/* Se si rileva più di un occorrenza di val nella lista */
	if(n_occ > 1) {
		
		/* Variabile per la validazione degli input */
		int lettura;

		/* Variabile per svuotare il buffer */
		char rimosso;
		
		/* L'utente viene avvertito che sono state trovate
		n occorrenze all'interno della lista */
		printf("Sono presenti %d occorrenze di %d\n",
			n_occ, val);
		
		/* Acquisizione degli input con validazione */
		do {

			/* Scelta dell'occorrenza desiderata */
			printf("Quale selezionare?\n");
			lettura = scanf("%d", &scelta);

			/* Verifica la validità degli input */
			if(lettura != 1 || scelta < 1 ||
			  scelta > n_occ) {
				printf("\nSelezione impossibile\n");
				do
					rimosso = getchar();
				while(rimosso != '\n');
			}

		  /* Condizioni di ripetizione */
		} while (lettura != 1 || scelta < 1 ||
			scelta > n_occ);
	}
	/* La funzione restituisce l'occorrenza desiderata */
	return scelta;
}

/* Funzione ricorsiva che mostra la lista scorrendola in avanti,
l'unico parametro richiesto è l'indirizzo del primo nodo */
void mostra(nodo_t *p) {

	/* Se il nodo è diverso da NULL */
	if(p != NULL){

		/* IL nodo viene stampato a video */
		printf(" -> %d", p->dato);

		/* La funzione viene invocata
		sul nodo successivo */
		mostra(p->succ_p);
	}
}

/* Funzione ricorsiva che mostra la lista scorrendola all'indietro,
l'unico parametro risulta essere l'indirizzo del primo nodo */
void mostra_ind(nodo_t *p) {

	/* Se il nodo è diverso da NULL */
	if(p != NULL){

		/* Il nodo viene stampato a video */
		printf(" -> %d", p->dato);

		/* La funzione viene richiamata
		sul nodo precedente */
		mostra_ind(p->prec_p);
	}
}
