#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rotar.h"

//Para mandar un nombre de fichero al programa, ejecutalo desde la terminal
int main(int n, char* cadena[]){
    srand(time(NULL));
    FILE* f_out;
    char mat[M][N];

    if (n != 2){
        printf("ERROR: Maximo dos argumentos..xd");
        return 1;
    }

    if (!(f_out = fopen(cadena[1], "w"))){
        printf("ERROR: No se pudo abrir/crear el fichero");
        return 2;
    }

    Rellenar_mat(mat);
    Imprimir_mat(mat);
    matrizFichero (mat, f_out);
    Rotar_mat(mat);
    Imprimir_mat(mat);
    matrizFichero(mat, f_out);
    Desrotar_mat(mat);
    Imprimir_mat(mat);
    matrizFichero(mat, f_out);

    fclose(f_out);

    return 0;
}
