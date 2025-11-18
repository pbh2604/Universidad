//--------------------------------------------------------------------------+
//         Modelo de practica de Arquitecturas Avanzadas                    |
//                                                                          |
// fapoyo.c:   Módulo que exporta un conjunto de funciones comunes a toda   |
//             la practica.                                                 |
//--------------------------------------------------------------------------+

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static double drango = 100000.0; // Rango de los numeros aleatorios

int aleatorio() {
    return (int)(((double)random() / RAND_MAX) * drango);
}

// ---------------------------------------------------------------------
//               F U N C I O N E S   E X P O R T A D A S
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
void init_aleatorios(void) {
    time_t taux;

    srandom((int)time(&taux));
}

// ---------------------------------------------------------------------
void sec_aleatoria(int *A, int longA) {
    int i;

    for (i = 0; i < longA; i++)
        A[i] = aleatorio();
}

// ---------------------------------------------------------------------
void visualiza_rodaja(int *A, int longA) {
    int i;

    for (i = 0; i < longA; i++) {
        printf("%6d ", A[i]);
        if (((i + 1) % 10) == 0)
            printf("\n");
    }
    printf("\n");
}
