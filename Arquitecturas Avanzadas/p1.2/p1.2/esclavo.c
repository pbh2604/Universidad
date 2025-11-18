//--------------------------------------------------------------------------+
//        Modelo de practica de Arquitecturas Avanzadas                     |
//                                                                          |
// esclavo.c:  Codigo de los procesos esclavos, que reciben primero un      |
//             mensaje indicandoles los identificadores de todos los        |
//             esclavos arrancados y luego uno con su rodaja a ordenar.     |
//             Posteriormente, entrará a formar parte de un proceso de      |
//             mezcla que concluira con el array completo ordenado en el    |
//             primer esclavo, que sera el que devuelva el array ordenado   |
//             al proceso maestro. Los esclavos van terminando segun se     |
//             les va terminando su trabajo.                                |
//--------------------------------------------------------------------------+

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "mpi.h"

#include "fburbuja.h"
#include "practica.h"

/**
 * Funcion que realiza la mezcla de dos arrays ordenados.
 *
 * Parametros:
 * - A: Primer array
 * - longA: Longitud del primer array
 * - B: Segundo array
 * - longB: Longitud del segundo array
 * - C: Array donde se almacena el resultado (salida)
 * - pLongC: Puntero a la longitud del array resultante (salida)
 */
void mezclar(int *A, int longA, int *B, int longB, int *C, int *pLongC) {

    int ia, ib, ic; // Indices para recorrer los tres arrays

    ia = 0;
    ib = 0;
    ic = 0;
    *pLongC = longA + longB;
    while ((ia < longA) && (ib < longB)) {
        if (A[ia] < B[ib])
            C[ic++] = A[ia++];
        else
            C[ic++] = B[ib++];
    }
    if (ia == longA)
        while (ib < longB)
            C[ic++] = B[ib++];
    else
        while (ia < longA)
            C[ic++] = A[ia++];
}

/**
 * Funcion que realiza las mezclas de las rodajas de los esclavos.
 *
 * Parametros:
 * - numEsclavos: Número de esclavos
 * - yo: Identificador del esclavo
 * - A: Rodaja de datos a mezclar
 * - longA: Longitud de la rodaja
 * - B: Array auxiliar
 * - longB: Longitud del array auxiliar
 * - C: Array donde se almacena el resultado
 * - pLongC: Puntero a la longitud del array resultante (salida)
 * Devuelve un puntero al array ordenado
 */
int *hacerMezclas(int yo, int numEsclavos, int *A, int longA, int *B, int longB, int *C, int *pLongC) {
    int mezclarEnC;
    int rodajas;
    int mezcladores; // Numero de mezcladores en cada etapa
    MPI_Status estado;

    rodajas = numEsclavos;
    mezclarEnC = TRUE;
    while (rodajas > 1) {
        mezcladores = rodajas / 2;
        if (yo <= mezcladores) {
            // Proceso mezclador
            MPI_Recv(B, CARD_A, MPI_INT, yo + mezcladores, 1, MPI_COMM_WORLD, &estado);
            MPI_Get_count(&estado, MPI_INT, &longB);
            if (mezclarEnC)
                mezclar(A, longA, B, longB, C, pLongC);
            else
                mezclar(C, *pLongC, B, longB, A, &longA);
        } else {
            // Proceso que suministra rodaja a mezclar
            if (mezclarEnC)
                MPI_Send(A, longA, MPI_INT, yo - mezcladores, 1, MPI_COMM_WORLD);
            else
                MPI_Send(C, *pLongC, MPI_INT, yo - mezcladores, 1, MPI_COMM_WORLD);
            MPI_Finalize();
            exit(0);
        }
        rodajas = rodajas / 2;
        if (mezclarEnC)
            mezclarEnC = FALSE;
        else
            mezclarEnC = TRUE;
    }
    if (mezclarEnC)
        return A;
    else
        return C;
}

int main(int argc, char *argv[]) {
    int numEsclavos; // Numerados de 1 en adelante
    int A[CARD_A], B[CARD_A], C[CARD_A];
    int longA, longB, longC; // Longitudes actuales de las rodajas
    int yo;
    int *resultado; // Puntero al array donde queda ordenado
    MPI_Status estado;

    setbuf(stdout, NULL); // Forzar salida sin buffer
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numEsclavos);
    numEsclavos--; // El maestro no cuenta
    MPI_Comm_rank(MPI_COMM_WORLD, &yo);

    longA = CARD_A / numEsclavos;
    MPI_Recv(A, longA, MPI_INT, 0, 1, MPI_COMM_WORLD, &estado);
    burbuja(A, longA);

    longB = 0; // Longitud inicial de B. La rellenerá el primer mezclador
    resultado = hacerMezclas(yo, numEsclavos, A, longA, B, longB, C, &longC);
    MPI_Send(resultado, CARD_A, MPI_INT, 0, 1, MPI_COMM_WORLD);

    MPI_Finalize();
    exit(0);
}
