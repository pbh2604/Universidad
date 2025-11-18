//--------------------------------------------------------------------------+
//         Modelo de practica de Arquitecturas Avanzadas                    |
//                                                                          |
// burbuja.c: Programa principal que genera una secuencia aleatoria de      |
//            numeros naturales y la ordena. Es una version secuencial      |
//            del problema de la practica para comparacion de tiempos.      |
//--------------------------------------------------------------------------+

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "practica.h"
#include "fapoyo.h"
#include "fburbuja.h"

int main()
{
  int A[CARD_A];
  struct timeval t0, tf, t;

  /* Generacion aleatoria de la secuencia */
  init_aleatorios();
  sec_aleatoria(A, CARD_A);
  printf("Vector inicial:\n\n");
  visualiza_rodaja(A, CARD_A);

  printf("Ordenando ..... \n");
  assert(gettimeofday(&t0, NULL) == 0);
  burbuja(A, CARD_A);
  assert(gettimeofday(&tf, NULL) == 0);
  timersub(&tf, &t0, &t);

  printf("Vector ordenado:\n\n");
  visualiza_rodaja(A, CARD_A);
  printf("Tiempo de proceso: (%ld.%ld) (s)\n",
         t.tv_sec, t.tv_usec / 1000);
  exit(0);
}
