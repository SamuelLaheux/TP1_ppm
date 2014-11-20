
all: ppm

ppm: ppm.c gargouille.o
	gcc -Wall -o ppm ppm.c gargouille.o

gargouille.o: gargouille.h gargouille.c
	gcc -Wall -c -o gargouille.o gargouille.c

