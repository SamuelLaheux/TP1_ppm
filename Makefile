
all: ppm

ppm: ppm.cpp gargouille.o
	g++ -Wall -o ppm ppm.cpp gargouille.o

gargouille.o: gargouille.h gargouille.cpp
	g++ -Wall -c -o gargouille.o gargouille.cpp

