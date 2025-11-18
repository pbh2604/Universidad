#include <stdio.h>
#include<time.h>
#include <stdlib.h>
#define N 100
/*Problema que lea un array de 100 enteros y muestre en pantalla el menor
 * y mayor de ellos*/
void rellenar(int[N]);
void mostrar(int[N]);
void mayor_menor(int[N],int *,int *);

int main() {
    int array[N],mayor,menor;
    /*si hubiera leido un array por pantalla
     * for(int i=0;i<N;i++)
     *      scanf("%i",&array[i]);*/
    rellenar(array);
    mostrar(array);
    printf("\n");
    mayor_menor(array,&mayor,&menor);
    printf("EL MAYOR ES: %i , EL MENOR ES: %i",mayor,menor);
    return 0;
}

void rellenar(int array[N]){
    srand(time(NULL));
    int i;
    for(i=0; i<N;i++)
        array[i]= rand()%(100-1+1)+1;
}

void mostrar(int array[N]){
    int i;
    for( i=0; i<N;i++)
        printf("%i ",array[i]);
}

void mayor_menor(int array[N],int *mayor,int *menor){
    int i;
    *mayor = * menor = array[0];
    for(int i=1;i<N;i++) {
        if (array[i] > *mayor)
            *mayor = array[i];
        else if(array[i] < *menor)
            *menor = array[i];
    }
}
