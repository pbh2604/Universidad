#------------------------------------------------------------------#
# PCM. Arquitecturas Avanzadas Curso 16/17 ETSISI        31/01/17  #
#                                                                  #
# Makefile para el desarrollo de las pruebas de los programas      #
#          relacionados con la practica 0 de MPI.                  #
#------------------------------------------------------------------#

CC          = mpicc

todo:	helloWorld hola pingpong psendrec costeop costemc

helloWorld: helloWorld.c
	$(CC) -Wall -ggdb helloWorld.c -o helloWorld

hola: hola.c
	$(CC) -Wall -ggdb hola.c -o hola

pingpong: pingpong.c
	$(CC) -Wall -ggdb pingpong.c -o pingpong

psendrec: psendrec.c
	$(CC) -Wall -ggdb psendrec.c -o psendrec

costeop: costeop.c
	gcc -Wall costeop.c -o costeop

costemc: costemc.c
	gcc -Wall costemc.c -o costemc -lpthread

borrar:
	rm *.o	helloWorld hola pingpong psendrec costeop costemc

