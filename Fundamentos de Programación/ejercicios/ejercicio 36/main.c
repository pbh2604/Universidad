/*programa que genere aleatoriamente una matriz de 10x15 caracteres alfabéticos y otros
 * dos caracteres alfabéticos más que representan un rango, y determina cuantos de los
 * valores introducidos están dentro del rango*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 3
#define M 3

int main() {
    srand(time(NULL));
    int i,j,cont=0;
    char matriz[N][M],c,c1,aux;
    for(i=0;i<N;i++)
        for(j=0;j<M;j++)
            matriz[i][j] = rand()%('Z'-'A'+1)+'A';

    for(i=0;i<N;i++) {
        for (j = 0; j < M; j++)
            printf("%c ", matriz[i][j]);
        printf("\n");
    }

    do{
        printf("INTRODUCE EL PRIMER VALOR DEL RANGO: ");
        scanf("%c",&c);
        fflush(stdin);
    }while(c <'A' || c >'Z');

    do{
        printf("INTRODUCE EL SEGUNDO VALOR DEL RANGO: ");
        scanf("%c",&c1);
        fflush(stdin);
    }while(c1 <'A' || c1 >'Z');

    if(c > c1){
        aux = c;
        c = c1;
        c1 = aux;
    }

    for(i=0;i<N;i++)
        for (j = 0; j < M; j++)
            if(matriz[i][j] >= c && matriz[i][j] <= c1)
               cont++;

    printf("EL NUMERO DE CARACTERES EN EL RANGO ES: %i",cont);

    return 0;
}
