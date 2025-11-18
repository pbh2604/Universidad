#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"

int main(int argc, char* argv[]){
    Apuesta apuesta;
    FILE* fapuestas;
    FILE* fpremiados;
    unsigned premiado[6], acc[6];
    unsigned i, j;
    srand(time(NULL));
    if (argc<3)
        return 1;
    if (!(fapuestas=fopen(argv[1], "rb")))
        return 2;
    if (!(fpremiados=fopen(argv[2], "w")))
        return 2;
    crearnum(premiado);
    fprintf(fpremiados, "Combinación ganadora: ");
    for (i=0; i<6; i++)
        fprintf(fpremiados, "%u ", premiado[i]);
    fprintf(fpremiados, "\n");
    while (fread(&apuesta, sizeof(Apuesta), 1, fapuestas))
        if ((j = acertados(apuesta, premiado, acc)) > 2){
            fprintf(fpremiados, "%s %u: ", apuesta.id, j);
            for (i = 0; i<6; i++)
                fprintf(fpremiados, "%2u ", apuesta.n[i]);
            fprintf(fpremiados, "| ");
            for (i = 0; i<j; i++)
            fprintf(fpremiados, "%2u ", acc[i]);
            fprintf(fpremiados, "\n");
        }
    fclose(fpremiados);
    fclose(fapuestas);
    return 0;
}

