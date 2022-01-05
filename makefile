CC = gcc
CFLAGS =  -ansi -g -Wall `pkg-config --cflags MLV`
LDFLAGS = `pkg-config --libs-only-other --libs-only-L MLV`
LDLIBS = `pkg-config --libs-only-l MLV`

reversi: main.o plateau.o jeux.o arbre.o ia.o evaluation.o
	$(CC) main.o plateau.o jeux.o arbre.o ia.o evaluation.o -o Reversi $(LDFLAGS) $(LDLIBS)

%o:%c %h
	$(CC) -o $@ -c $< $(OPTIONS)

propre:
	rm *.o Reversi
