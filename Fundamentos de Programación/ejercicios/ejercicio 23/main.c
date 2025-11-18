#include <stdio.h>
int intervalo(int ,int , int );
/*Función que recibe como parámetros un número entero positivo n y otros dos enteros
 * positivos a y b que representan un intervalo, debiendo ser a<b, devuelva como
 * resultado:   -1 si n es menor que a
                 1 si n es mayor que b
                 0 si n esta en el intervalo*/
int main() {
    printf("%i",intervalo(2,4,6));
    return 0;
}

int intervalo(int n,int a, int b){
    if (a > b){
        int aux = a;
        a = b;
        b = aux;
    }
    return n < a ? -1: n > b ? 1 : 0;
}