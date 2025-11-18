#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tipos.h"

int main(int argc, char* argv[]){
    FILE* f_in;
    unsigned n_apuestas;
    srand(time(NULL));
    if (argc<2){
        printf("EXISTE ERROR");
        return 1;
    }
    if (!(f_in=fopen(argv[1], "wb")))
        return 2;
    printf("\n¿Cuantas apuestas generas? :");
    scanf("%u", &n_apuestas);
    fflush(stdin);
    printf("\nEl archivo pesará %.9fmb Seguir? (S/N): ",(sizeof(Apuesta)/1000000.f));
    if (toupper(getchar()) != 'S')
        return 0;
    rellenarfapuestas(f_in, n_apuestas);
    fclose(f_in);
    return 0;
}
