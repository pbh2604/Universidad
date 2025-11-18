/*un array de 75 enteros que invierta sus elementos*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 75

void rellenar(int [N]);
void mostrar(int [N]);
void inv_array(int [N]);

int main() {
    int array[N];
    rellenar(array);
    mostrar(array);
    printf("\n\n");
    inv_array(array);
    mostrar(array);
    return 0;
}

void rellenar(int array[N]){
    srand(time(NULL));
    int i;
    for(i=0;i<N;i++)
        array[i]= rand()%(10-1+1)+1;
}

void mostrar(int array[N]){
    int i;
    for(i=0;i<N;i++)
        printf("%i ",array[i]);
}

void inv_array(int *array){// funciona igual con int array[N]
    int i,j,aux;
    for(i=0,j=N-1;i<j;i++,j--){
        aux = array[i];
        array[i] = array[j];
        array[j] = aux;
    }
}

