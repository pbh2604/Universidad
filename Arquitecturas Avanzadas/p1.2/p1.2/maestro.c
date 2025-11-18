//--------------------------------------------------------------------------+
//         Modelo de practica de Arquitecturas Avanzadas                    |
//                                                                          |
// maestro.c:  Programa principal, que genera una secuencia aleatoria de    |
//             numeros naturales y la ordena con el apoyo de procesos       |
//             esclavos que ordenan cada uno un trozo de la secuencia y     |
//             luego intervienen en un proceso de mezcla de dichos trozos.  |
//--------------------------------------------------------------------------+

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "mpi.h"

#include "fapoyo.h"
#include "practica.h"

int main(int argc, char *argv[]) {
    int A[CARD_A]; // Vector a ordenar
    int numEsclavos;
    int i, inicioRodaja, longRodaja, yo;
    struct timeval t0, tf, t;
    MPI_Status estado;

    setbuf(stdout, NULL); // Forzar salida sin buffer
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numEsclavos);
    numEsclavos--; // El maestro no cuenta
    MPI_Comm_rank(MPI_COMM_WORLD, &yo);

    // Generacion aleatoria de la secuencia
    init_aleatorios();
    sec_aleatoria(A, CARD_A);

    printf("Secuencia inicial: \n");
    visualiza_rodaja(A, CARD_A);

    assert(gettimeofday(&t0, NULL) == 0);
    // ordenar
    inicioRodaja = 0;
    longRodaja = CARD_A / numEsclavos;

    // Se envian mensajes de ordenar a los esclavos
    for (i = 1; i <= numEsclavos; i++) {
        MPI_Send(&A[inicioRodaja], longRodaja, MPI_INT, i, 1, MPI_COMM_WORLD);
        inicioRodaja += longRodaja;
    }

    // Se recibe el resultado del primer esclavo
    MPI_Recv(A, CARD_A, MPI_INT, 1, 1, MPI_COMM_WORLD, &estado);
    assert(gettimeofday(&tf, NULL) == 0);
    timersub(&tf, &t0, &t);

    printf("Secuencia ordenada:\n");
    visualiza_rodaja(A, CARD_A);
    printf("\n\nTiempo de proceso = %ld.%ld s\n", t.tv_sec, t.tv_usec / 1000);

    MPI_Finalize();
    exit(0);
}
