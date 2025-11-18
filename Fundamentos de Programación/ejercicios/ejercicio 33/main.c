/*programa que lea caracteres y va almacenando en array de 30 elementos las vocales mayúsculas que aparecen. El programa termina cuando
 * se completa el array.Como resultado muestra por pantalla las vocales almacenadas y pocentaje de vocales frente al total de caracteres
 * leidos*/
#include <stdio.h>
#define N 5//PARA QUE SEAN 30 SOLO HABRÍA QUE PONER 30 AQUÍ

int main() {
    char array[N]={" "},aux;
    int i=0,total = 0,vocal=0;
    do{
        scanf("%c",&aux);
        fflush(stdin);// ESTO ES NECESARIO, PORQUE SINO EL TOTAL DE CARACTERES LEIDOS SERÍAN 9 Y NO 5, PORQUE TMB CONTARÍA LOS SALTOS DE LÍNEA
        total++;
        if(aux == 'A' || aux == 'E' || aux == 'I' || aux == 'O' || aux == 'U') {
            array[i] = aux;
            vocal++;
            i++;
        }
    }while(array[i] < N);
    for(i=0;i<N;i++)
        printf("%c ",array[i]);
    printf ("\nEl numero de caracteres leidos totales: %i, el porcentaje: %.2f%%",total,(float)vocal/total *100);
    return 0;
}
