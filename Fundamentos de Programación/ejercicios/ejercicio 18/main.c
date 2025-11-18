#include <stdio.h>
/*Programa que lea de teclado números enteros (al menos uno) que irá sumando en
 * una variable (inicializada a 0).Por cada número leído imprimirá ese valor y la
 * suma acumulada hasta ese momento. El programa termina cuando todos nº leidos
 * suman 0*/
int main() {
    int suma=0,n,i;
    printf("Introduce valores enteros: ");
    do {
        scanf("%i", &n);
        printf("numero actual: %i\n",n);
        printf("suma: %i\n",suma += n);
    }while(suma);
    return 0;
}
