/*función que pasándole parámetro matriz 10x15, determine si
 * todos los valores contenidos en ella son positivos o no*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 5
#define M 5

void rellenar(int [N][M]);
void mostrar(int [N][M]);
int todo_pos(int [N][M]);

int main() {
    int matriz[N][M];
    rellenar(matriz);
    mostrar(matriz);
    todo_pos(matriz);
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

int todo_pos(int matriz[N][M]){
    int resultado=0;// supongo que son positivos
    for(int i=0;i<N;i++)
        for (int j = 0; j < M; j++)
            if(matriz[i][j]<0)
                resultado=1;
    if(resultado == 0)
        printf("Todos son positivos");
    else
        printf("No todos son positivos");
    return resultado;
}

