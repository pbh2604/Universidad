#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//structs
typedef struct{
 char id[11];
 unsigned n[6];
}Apuesta;

// prototipos
int aleatorio(int, int);
void crear_num(unsigned[6]);
void premiado(int[6], const char*);
unsigned aciertos(Apuesta, unsigned[6], unsigned[]);

// main
int main(){
    Apuesta apuesta;
    FILE* fapuestas;
    FILE* fpremiado;
    unsigned premiado[6], acc[6];
    char nom_apuestas[20];
    char nom_premiado[20];
    unsigned i, j;
    srand(time(NULL));
    printf("\nDe donde quieres leer las apuestas? :");
    gets(nom_apuestas);
    printf("\nDonde quieres guardar los premiados? :");
    gets(nom_premiado);
    if (!(fapuestas=fopen(nom_apuestas, "rb")))
        exit(1);
    if (!(fpremiado=fopen(nom_premiado, "w")))
        exit(1);
    crear_num(premiado);
    fprintf(fpremiado, "Combinación ganadora: ");
    for (i=0; i<6; i++)
        fprintf(fpremiado, "%u ", premiado[i]);
    fprintf(fpremiado, "\n");
    while (fread(&apuesta, sizeof(Apuesta), 1, fapuestas))
        if ((j = aciertos(apuesta, premiado, acc)) > 1){
            fprintf(fpremiado, "%s %u: ", apuesta.id, j);
    for (i = 0; i<6; i++)
        fprintf(fpremiado, "%2u ", apuesta.n[i]);
    fprintf(fpremiado, "| ");
    for (i = 0; i<j; i++)
        fprintf(fpremiado, "%2u ", acc[i]);
    fprintf(fpremiado, "\n");
        }
    fclose(fpremiado);
    fclose(fapuestas);
    return 0;
}

// implementacion funciones
void crear_num(unsigned num[6]){
    int i, j;
    for (i=0; i<6;){
        num[i] = aleatorio(1, 49);
        for (j=0; j<i && num[j] != num[i]; j++);
            if (j == i)
                i++;
    }
}

unsigned aciertos(Apuesta apuesta, unsigned premiado[6], unsigned *_aciertos){
    unsigned cont_aciertos = 0, i, j;
    for (i=0; i<6; i++){
        for(j=0; j<6 && apuesta.n[i] != premiado[j]; j++);
            if (j<6)
                _aciertos[cont_aciertos++] = apuesta.n[i];
    }
    return cont_aciertos;
}

int aleatorio(int a, int b){
    return (rand()%(b-a+1)+a);
}
