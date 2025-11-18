//------------------------------------------------------------------+
// helloWorld.c: Primer ejemplo de prueba del entorno MPI.          |
//------------------------------------------------------------------+
#include <stdio.h>
#include <unistd.h>

#include "mpi.h"

//--------------------------------------------------------------------
int main(int argc, char *argv[]) {
    int yo, numProcesos;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &yo);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesos);
    if (yo == 0)
        printf("Se han creado %d procesos\n", numProcesos);
    printf("Soy el proceso %d\n", yo);
    MPI_Finalize();
    return 0;
}
