//------------------------------------------------------------------+
// hola.c: Primer ejemplo de prueba del entorno MPI.                |
//------------------------------------------------------------------+
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include "mpi.h"

#define LONG_BUFFER 100
#define TAG_MESSAGE 100
#define TAG_TIME 101
#define TIME_ELEMENTS 2

//--------------------------------------------------------------------
void esclavo(int yo) {
    char buffer[LONG_BUFFER] = {0};
    struct timeval t0, tf, t;
    long int tiempo[TIME_ELEMENTS]; // Segundos y microsegundos

    gettimeofday(&t0, NULL);

    // Construir el mensaje de manera segura
    snprintf(buffer, LONG_BUFFER, "Hola, desde ");
    gethostname(buffer + strlen(buffer), LONG_BUFFER - strlen(buffer));

    // Enviar el mensaje al maestro
    int err = MPI_Send(buffer, LONG_BUFFER, MPI_BYTE, 0, TAG_MESSAGE, MPI_COMM_WORLD);
    if (err != MPI_SUCCESS) {
        fprintf(stderr, "Error: MPI_Send falló en esclavo\n");
        MPI_Abort(MPI_COMM_WORLD, err);
    }

    sleep(yo + 5);

    gettimeofday(&tf, NULL);
    timersub(&tf, &t0, &t);
    tiempo[0] = t.tv_sec;
    tiempo[1] = t.tv_usec;

    // Enviar los datos de tiempo al maestro
    err = MPI_Send(tiempo, TIME_ELEMENTS, MPI_LONG, 0, TAG_TIME, MPI_COMM_WORLD);
    if (err != MPI_SUCCESS) {
        fprintf(stderr, "Error: MPI_Send falló en esclavo\n");
        MPI_Abort(MPI_COMM_WORLD, err);
    }
}

//--------------------------------------------------------------------
void maestro(int numEsclavos) {
    int i;
    char buffer[LONG_BUFFER] = {0};
    long int tiempo[TIME_ELEMENTS];
    MPI_Status estado;

    // Obtener el nombre del host del maestro
    gethostname(buffer, LONG_BUFFER);
    printf("Maestro ejecutándose en %s\n", buffer);

    // Recibir mensajes de los esclavos
    for (i = 0; i < numEsclavos; i++) {
        int err = MPI_Recv(buffer, LONG_BUFFER, MPI_BYTE, MPI_ANY_SOURCE, TAG_MESSAGE,
                           MPI_COMM_WORLD, &estado);
        if (err != MPI_SUCCESS) {
            fprintf(stderr, "Error: MPI_Recv falló en maestro\n");
            MPI_Abort(MPI_COMM_WORLD, err);
        }
        printf("Del proceso %d: %s\n", estado.MPI_SOURCE, buffer);
    }

    // Recibir datos de tiempo de los esclavos
    for (i = 0; i < numEsclavos; i++) {
        int err = MPI_Recv(tiempo, TIME_ELEMENTS, MPI_LONG, i + 1, TAG_TIME, MPI_COMM_WORLD, &estado);
        if (err != MPI_SUCCESS) {
            fprintf(stderr, "Error: MPI_Recv falló en maestro\n");
            MPI_Abort(MPI_COMM_WORLD, err);
        }
        printf("Tiempo del Proceso[%d] = %.6f s\n", i + 1, tiempo[0] + tiempo[1] / 1000000.0);
    }
}

//--------------------------------------------------------------------
int main(int argc, char *argv[]) {
    int yo, numProcesos;

    setbuf(stdout, NULL); // Deshabilitar el buffer de salida

    // Inicializar MPI
    int err = MPI_Init(&argc, &argv);
    if (err != MPI_SUCCESS) {
        fprintf(stderr, "Error al inicializar MPI\n");
        MPI_Abort(MPI_COMM_WORLD, err);
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &yo);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesos);

    if (numProcesos < 2) {
        fprintf(stderr, "Se requieren al menos 2 procesos\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    if (yo == 0) {
        maestro(numProcesos - 1);
    } else {
        esclavo(yo);
    }

    MPI_Finalize();
    return 0;
}
