/*función que pasándole como parámetro matriz de 10x10 enteros,
 * intercambie entre sí los valores opuestos de la misma, es decir,
 * el[0][1] por [1][0], el [0][0] por [9][9] y así sucesivamente
 * hasta intercambiar todas las posiciones*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 3
#define M 3

void rellenar(int [N][M]);
void mostrar(int [N][M]);
void intercambiar_pos(int [N][M]);

int main() {
    int matriz[N][M];
    rellenar(matriz);
    mostrar(matriz);
    printf("\n");
    intercambiar_pos(matriz);
    mostrar(matriz);
    return 0;
}

void rellenar(int matriz[N][M]){
    srand(time(NULL));
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++)
            matriz[i][j] = rand()%(100-(-100)+1)+(-100);
}

void mostrar(int matriz[N][M]){
    for(int i=0;i<N;i++) {
        for (int j = 0; j < M; j++)
            printf("%i ",matriz[i][j]);
        printf("\n");
    }
}

void intercambiar_pos(int matriz[N][M]) {
    int i, j, k, l, aux1, aux[N][M];

    for (i = 0; i < M; i++)
        for (j = 0; j < M; j++)
            aux[i][j] = matriz[i][j];

    for (i = 0; i < M; i++)
        for (j = 0; j < M; j++) {
            if(i==0 && j == 0){
                aux1 = matriz[i][j];
                matriz[i][j] = matriz[N-1][M-1];
                matriz[N-1][M-1] = aux1;
            }else if(matriz[i][j] == aux[i][j]){
                aux1 = matriz[i][j];
                matriz[i][j] = matriz[j][i];
                matriz[j][i] = aux1;
            }
        }

}