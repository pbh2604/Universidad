//-------------------------------------------------------------------+
// pingpong.c: Programa de prueba para evaluar los tiempos de        |
//             latencia de las comunicaciones.                       |
//-------------------------------------------------------------------+

#include <assert.h>
#include <stdio.h>
#include <sys/time.h>

#include "mpi.h"

#define ITERACIONES 200
#define LONG_MSJ 1 // Probar con 1, 1000 y 100000

//--------------------------------------------------------------------
void pong(void) {
    int basura[LONG_MSJ]; // Mensaje a intercambiarse
    int i;
    
    for(i = 0; i <= ITERACIONES; i++)
    {
        //recibir el mensaje enviado por proceso 0
        MPI_Recv(basura, LONG_MSJ, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        //devolver el mensaje al proceso 0
        MPI_Send(basura, LONG_MSJ, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

}

//--------------------------------------------------------------------
void ping(void) {
    int basura[LONG_MSJ]; // Mensaje a intercambiarse
    int i;
    struct timeval t0, t1, tiempo;
    long int microseg = 0;

    for (i = 0; i <= ITERACIONES; i++) {
        assert(gettimeofday(&t0, NULL) == 0);

        // Envio y recepcion a "pong"
        // envio del mensaje al proceso 1
        MPI_Send(basura, LONG_MSJ, MPI_INT, 1, 0, MPI_COMM_WORLD);
        // recepcion de la respuesta del proceso 1
        MPI_Recv(basura, LONG_MSJ, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        assert(gettimeofday(&t1, NULL) == 0);
        timersub(&t1, &t0, &tiempo);

        // Comprobacion de que no ha pasado un segundo: se supone que la latencia es menor
        // y el programa no está preparado para medir tiempos mayores
        assert(tiempo.tv_sec == 0);

        // Imprimir el tiempo en milisegundos
        printf("%7.9f ", tiempo.tv_usec / (1000.0 * 2));

        // Salto de línea cada 5 iteraciones
        if (((i + 1) % 5) == 0)
            printf("\n");

        // Se desprecia la primera comunicacion
        if (i > 0)
            microseg = microseg + tiempo.tv_usec;
    }
    printf("\nTiempo medio = %7.9f milisegundos\n", (float) microseg / (1000.0 * ITERACIONES * 2));
}

//--------------------------------------------------------------------
int main(int argc, char *argv[]) {
    int yo;

    setbuf(stdout, NULL); // Sin buffers de escritura
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &yo);
    if (yo == 0)
        ping();
    else
        pong();
    MPI_Finalize();
    return 0;
}
