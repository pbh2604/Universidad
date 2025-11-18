/*programa que lea matriz 10x15 enteros, valor entre 1 y 9(filas), valor entre 1 y 14
 * (columna)e imprima por pantalla los valores de la submatriz generada*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
#define M 15

int main() {
    int matriz[N][M],i,j,f,c;
    for(i=0;i<N;i++)
        for(j=0;j<M;j++)
            scanf("%i",&matriz[i][j]);

    for(i=0;i<N;i++) {
        for (j = 0; j < M; j++)
            printf("%i ", matriz[i][j]);
        printf("\n");
    }

    do{
        scanf("%i",&f);
    }while(f<1 || f>9);

    do{
        scanf("%i",&c);
    }while(c<1 || c>14);

    for(i=f-1;i<N;i++) {
        for (j = c-1; j < M; j++)
            printf("%i ", matriz[i][j]);
        printf("\n");
    }
    return 0;
}
