#include <stdio.h>
/*Programa que lea de teclado un número entero n entre 2 y 6 que va determinar
 * el número de secuencias crecientes a leer. A continuación leerá número:
 * enteros hasta que se hayan leido n secuencias crecientes. Por ejemplo, si el
 * número n es 3, una posible entrada de datos sería:
 * [1 2 8] [4 5 7 19] [-6 0 8 100] 27*/
int main() {
    int n,ant,act;
    do{
        printf("Introduce un numero entre 2 y 6:");
        scanf("%i",&n);
    }while(n<2 || n > 6);
    printf("Introduce valores enteros: ");
    scanf("%i",&ant);
    do{
        scanf("%i",&act);
        if (ant > act)
            n--;
        ant = act;
    }while(n);

    return 0;
}