//------------------------------------------------------------------+
//         Modelo de practica de Arquitecturas Avanzadas            |
//                                                                  |
// fburbuja.c: Modulo que exporta la funcion "burbuja" que implemen-|
//             ta la ordenacion secuencial mediante este metodo.    |
//------------------------------------------------------------------+

#include "fapoyo.h"

void burbuja(int *A, int longA) {
    int i, j, elemento;

    for (i = 1; i < longA; i++) {
        for (j = longA - 1; j >= i; j--)
            if (A[j - 1] > A[j]) {
                elemento = A[j - 1];
                A[j - 1] = A[j];
                A[j] = elemento;
            }
    }
}
