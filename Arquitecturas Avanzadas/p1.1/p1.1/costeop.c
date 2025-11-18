//------------------------------------------------------------------+
// costeop.c: Prueba de calculo del tiempo de ejecucion de una      |
//               una operacion simple condicional.                  |
//------------------------------------------------------------------+

#include <assert.h>
#include <stdio.h>
#include <sys/time.h>

#define LONG_VECTOR 10000000
#define NUM_VECES 10000000

static int vector[LONG_VECTOR];

//-------------------------------------------------------------------
void computar() {
    int i, j;

    j = 5;
    for (i = 0; i < NUM_VECES; i++) {
        // j = (j + 1) % 3333;
        if (j == 3333)
            j = 0;
        else
            j++;
    }
    vector[j] = 0;
}

//-------------------------------------------------------------------
int main(int argc, char *argv[]) {
    struct timeval t0, tf, tiempo;
    float microseg;

    assert(gettimeofday(&t0, NULL) == 0);
    computar();
    assert(gettimeofday(&tf, NULL) == 0);
    timersub(&tf, &t0, &tiempo);
    assert(tiempo.tv_sec == 0);
    microseg = (float)(tiempo.tv_usec) / NUM_VECES;
    printf("Tiempo de operacion basica: %7.9f milisegundos\n", microseg / 1000.0);
    return 0;
}
