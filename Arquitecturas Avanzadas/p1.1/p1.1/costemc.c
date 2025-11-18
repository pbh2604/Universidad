//------------------------------------------------------------------+
// PCM. Arquitecturas Avanzadas Curso 16/17 ETSISI        31/01/17  |
//                                                                  |
// costemc.c: Prueba del coste de comunicacion entre dos threads a  |
//            traves de una posicion de memoria (uno escribe y el   |
//            otro lee.                                             |
//------------------------------------------------------------------+

#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/time.h>

#define NUM_VECES 100000

// Variables globales para que ambos procesos conozcan
// el identificador de thread del otro proceso
static pthread_t t_productor, t_consumidor;
static int datoComun = 0;
static long int microseg;
static sem_t sPro, sCon;

//-------------------------------------------------------------------
void *productor(void *basura) {
    struct timeval t0, tf, t;
    int i;

    assert(gettimeofday(&t0, NULL) == 0);
    for (i = 0; i < NUM_VECES; i++) {
        sem_wait(&sPro);
        datoComun++;
        sem_post(&sCon);
    }
    assert(gettimeofday(&tf, NULL) == 0);
    timersub(&tf, &t0, &t);
    microseg = t.tv_sec * 1000000 + t.tv_usec;
    printf("Tiempo sincronizacion por memoria comun = %7.9f milisegundos\n",
           (float)microseg / (1000.0 * (float)NUM_VECES));
    pthread_exit(NULL);
}

//-------------------------------------------------------------------
void *consumidor(void *basura) {

    int i;

    for (i = 0; i < NUM_VECES; i++) {
        sem_wait(&sCon);
        assert(datoComun == i + 1);
        sem_post(&sPro);
    }
    pthread_exit(NULL);
}

//-------------------------------------------------------------------
int main(int argc, char *argv[]) {
    assert(sem_init(&sPro, 0, 1) == 0);
    assert(sem_init(&sCon, 0, 0) == 0);
    assert(pthread_create(&t_productor, NULL, productor, NULL) == 0);
    assert(pthread_create(&t_consumidor, NULL, consumidor, NULL) == 0);
    assert(pthread_join(t_productor, NULL) == 0);
    assert(pthread_join(t_consumidor, NULL) == 0);
    return 0;
}
