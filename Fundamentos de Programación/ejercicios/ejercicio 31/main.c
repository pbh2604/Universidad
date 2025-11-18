/*función que recibiendo como parámetro un array de 50 caracteres, devuelva la primera mayúscula que aparezca en él
 * o '#' sino se encuentra ninguna*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 50

void rellenar(char [N]);
void mostrar(char [N]);
char busqueda(char *);// aquí sería poner char [N]

int main() {
    char array[N];
    rellenar(array);
    mostrar(array);
    printf("\nel resultado: %c ", busqueda(&array));// aquí pondría array sin más
    return 0;
}

void rellenar(char array[N]){
    srand(time(NULL));
    int i;
    for (i = 0; i < N; i++) {
        array[i] = rand()%(255-32+1)+32;
    }
}

void mostrar(char array[N]){
    int i;
    for(i=0;i<N;i++) {
        printf("%c ", array[i]);
    }
}

char busqueda(char *array){// es lo mismo que poner char array[N]
    int aux = 0,i;
    char resultado='#';
    for(i=0;i<N;i++) {
        if (array[i] > 'A' && array[i] < 'Z' && aux == 0){
            resultado = array[i];
            aux = 1;
        }
    }
    return resultado;
}
