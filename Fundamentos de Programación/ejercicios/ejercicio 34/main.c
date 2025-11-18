/*función que recibe como parámetro matriz 10x15 enteros, devuelva n fila en la que la suma
 * de sus elementos que sea mayor que la del resto de las filas*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
#define M 15

void rellenar(int [N][M]);
void mostrar(int [N][M]);
unsigned sum_fila(int [N][M]);

int main() {
    int matriz[N][M];
    rellenar(matriz);
    mostrar(matriz);
    printf("\n%u",sum_fila(matriz));
    return 0;
}

void rellenar(int matriz[N][M]){
    srand(time(NULL));
    int i,j;
    for(i=0;i<N;i++)
        for(j=0;j<M;j++)
            matriz[i][j]=rand()%(100-1+1)+1;
}

void mostrar(int matriz[N][M]){
    int i,j;
    for(i=0;i<N;i++) {
        for (j = 0; j < M; j++)
            printf("%i ", matriz[i][j]);
        printf("\n");
    }
}

unsigned sum_fila(int matriz[N][M]){
    unsigned suma =0,aux,i,j,fila=0;
    for(i=0;i<M;i++) {
        aux += matriz[0][i];
    }
    printf("\nfila 0 la suma es: %u\n",aux);
    for(i=1;i<N;i++){
        for(j=0;j<M;j++)
            suma += matriz[i][j];
        printf("esta es la fila %u y su suma es: %u\n",i,suma);
        if(suma > aux){
            aux = suma;
            fila = i+1;
        }
        suma=0;
    }
    return fila;
}





