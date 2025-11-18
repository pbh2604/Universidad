/*función que recibe como parámetro un array de 50 caracteres, devuelve el numero de vocales que aparecen en él*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 50

void rellenar(char [N]);
void mostrar(char [N]);
int cont_vocales(char *);

int main() {
    char array[N];
    rellenar(array);
    mostrar(array);
    printf("\n");
    printf("%i",cont_vocales(array));
    return 0;
}

void rellenar(char array[N]){
    int i;
    srand(time(NULL));
    for(i=0;i<N;i++) {
        if(i%2 == 0)
            array[i] = rand() %('z'-'a'+1)+'a';
        else
            array[i] = rand() %('Z'-'A'+1)+'A';
    }
}

void mostrar(char array[N]){
    int i;
    for(i=0;i<N;i++)
        printf("%c",array[i]);
}

int cont_vocales(char *array){
    int i,cont =0;
    for(i=0;i<N;i++)
        if(array[i] == 'A' || array[i] == 'E' || array[i] =='I' || array[i] == 'O' || array[i] == 'U'
                || array[i] == 'a' || array[i] == 'e' || array[i] == 'i' || array[i] == 'o' || array[i] == 'u')
            cont++;
    return cont;
}
