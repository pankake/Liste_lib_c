progetto_ppl:	main.o lista.o Makefile
	gcc -ansi -Wall -O main.o lista.o -o progetto_ppl

main.o:		main.c lista.h Makefile
	gcc -ansi -Wall -O -c main.c

lista.o:	lista.c lista.h Makefile
	gcc -ansi -Wall -O -c lista.c

pulisci:
	rm -f *.o

pulisci_tutto:
	rm -f progetto_ppl *.o
