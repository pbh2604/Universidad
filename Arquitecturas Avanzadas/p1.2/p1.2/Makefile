#------------------------------------------------------------------#
# Arquitecturas Avanzadasccc                                       #
#                                                                  #
# Makefile para el desarrollo de la practica modelo.               #
#------------------------------------------------------------------#

CC      = mpicc -Wall
CLINKER = mpicc -Wall

todo: maestro esclavo burbuja

maestro: maestro.o fapoyo.o
	$(CLINKER) -o maestro maestro.o fapoyo.o

esclavo: esclavo.o fburbuja.o fapoyo.o
	$(CLINKER) -o esclavo esclavo.o fburbuja.o fapoyo.o

burbuja: burbuja.o fburbuja.o fapoyo.o
	gcc -o burbuja burbuja.o fburbuja.o fapoyo.o

maestro.o: maestro.c fapoyo.h practica.h
	$(CC) -O3 -Wall -ggdb -c maestro.c

esclavo.o: esclavo.c practica.h fburbuja.h fapoyo.h
	$(CC) -O3 -Wall -ggdb -c esclavo.c

burbuja.o: burbuja.c practica.h fburbuja.h
	gcc -O3 -Wall -ggdb -c burbuja.c

fburbuja.o: fburbuja.c fapoyo.h
	gcc -O3 -Wall -ggdb -c fburbuja.c

fapoyo.o: fapoyo.c
	gcc -O3 -Wall -ggdb -c fapoyo.c

borrar:
	rm *.o  burbuja maestro esclavo
