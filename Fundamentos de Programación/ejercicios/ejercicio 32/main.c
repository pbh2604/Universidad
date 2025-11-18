/*funcion que recibe com parámetro array de 100 enteros, devuelve el número de valores positivos, negativos y cero contenidos en el mismo.*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 100

void rellenar(int [N]);
void mostrar(int [N]);
void contador(int *,int *,int *,int *);

int main() {
    int array[N],positivo = 0,negativo = 0,cero=0;
    rellenar(array);
    mostrar(array);
    contador(&array,&positivo,&negativo,&cero);
    printf("\nLa cantidad de postivos: %i,negativos %i,ceros: %i",positivo,negativo,cero);
    return 0;
}
 void rellenar(int array[N]){
    srand(time(NULL));
    int i;
    for(i = 0; i<N;i++)
        array[i] = rand()%(100-(-100)+1)+(-100);
}

void mostrar(int array[N]){
    int i;
    for(i=0;i<N;i++)
        printf("%i ", array[i]);
}

void contador(int *array, int *positivo, int *negativo,int *cero){
    int i;
    for(int i=0;i<N;i++){
        if(array[i] < 0){
            (*negativo)++;
        }else if(array[i] > 0){
            (*positivo)++;
        }else if(array[i] == 0){
            (*cero)++;
        }
    }

}