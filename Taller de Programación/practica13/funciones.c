#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rotar.h"

void Imprimir_mat (char matriz[M][N]){
    int i, j;
    printf("\n");
    for (i = 0; i < M; i++){
        for (j = 0; j < N; j++)
            printf(" %c ", matriz[i][j]);
        printf("\n");
    }
}

void Rellenar_mat (char  matriz[M][N]){
    int i, j;
    for (i = 0; i < M; i++)
        for (j = 0; j <N; j++)
            matriz[i][j] = aleatorio('A', 'Z');
}

void Rotar_mat (char matriz[M][N]){
    /*
    * === Funcionamiento:
    *
    * - mask = 3:
    *      3  = 00000011
    *
    * - char = 'A':
    *     'A' = 01000001    //65
    *
    * (1) ults = bits que queremos rotar (los 2 ultimos):
    *     00000011 (mask)
    *   & 01000001 (char)
    *  -------------------
    *     00000001 (ults)
    *
    * (2) Desplazamos ults a la izquierda:
    *     00000001 << 6 = 01000000
    *
    * (3) Desplazamos char dos veces a la derecha:
    *     01000001 >> 2 = 00010000
    *
    * (4) Ponemos los ultimos dos bits (ults) en las primeras dos posiciones de char
    *     01000000 (ults)
    *   | 00010000 (char)
    *  -------------------------
    *     01010000 (char rotado)
    *
    *
    * === Podemos calcularlo en una linea:
    *
    *   char = ( ( char & 3 ) << 6 ) | ( char >> 2 )
    *          | |____(1)___|      |   |____(3)____|
    *          |_________(2)_______|
    *          |________________(4)________________|
    *
    */
    int i, j;
    for (i=0; i<M; i++)
        for(j=0; j<N; j++)
            matriz[i][j] = (( ( matriz[i][j] & 3) << 6 ) | (matriz[i][j] >> 2));
}

void Desrotar_mat (char matriz[M][N]){
    /*
    * === Funcionamiento:
    *
    * - mask = 3 << 6 = 192:
    *      192  = 11000000
    *
    * - char rotado = 'A' rotado:
    *     'A' rotado = 01010000
    *
    * (1) prims = bits que queremos rotar (los 2 primeros):
    *     11000000 (mask)
    *   & 01010000 (char rotado)
    *  -------------------
    *     01000000 (prims)
    *
    * (2) Desplazamos prims a la derecha:
    *     01000000 >> 6 = 00000001
    *
    * (3) Desplazamos char rotado dos veces a la izquierda:
    *     01010000 << 2 = 01000000
    *
    * (4) Ponemos los primeros dos bits (prims) en las ultimas dos posiciones de char rotado
    *     00000001 (prims)
    *   | 01000000 (char rotado)
    *  -------------------------
    *     01000001 (char)
    *
    *
    * === Podemos calcularlo en una linea:
    *
    *   char = (     ( char & 192 ) >> 6 ) | ( char << 2 )
    *          | |____(1)_____|      |   |____(3)____|
    *          |_________(2)_________|
    *          |_________________(4)_________________|
    *
    */
    int i, j;
    for (i=0; i<M; i++)
        for(j=0; j<N; j++)
            matriz[i][j] = ( (matriz[i][j] & 192) >> 6 ) | (matriz[i][j] << 2);
}

void matrizFichero(char matriz[M][N], FILE* f_out){
    int i;
    for (i=0; i<M; i++)
        fputs(matriz[i], f_out);

}

int aleatorio(int inf, int sup){
    int aux = inf;
    if (inf > sup){
        inf = sup;
        sup = aux;
    }
    return (rand()%(sup-inf+1)+inf);
}
