/* Definizione del nuvo tipo struttura,
costituita da un campo intero e due
puntatori per il doppio collegamento */
typedef struct nodo  {
	int dato;		/* valore del nodo */
	struct nodo* succ_p;	/* puntatore elem. succ. */
	struct nodo* prec_p;	/* puntatore elem. prec. */
}nodo_t;		        /* ridefinizione nuovo tipo */

/* Funzioni da esportare */
extern nodo_t *crea_nodo(int);
extern void in_testa(int, nodo_t **);
extern void in_coda(int, nodo_t **);
extern void mostra(nodo_t *);
extern void mostra_ind(nodo_t *);
extern void rim_testa(nodo_t **);
extern void rim_coda(nodo_t **);
extern void rim_elem(int, nodo_t **);
extern void ins_spec(int, int, nodo_t **, int);
extern void visita(int, nodo_t *, int);



