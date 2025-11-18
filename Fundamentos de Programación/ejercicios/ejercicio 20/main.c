#include <stdio.h>
/*Escribir una función que recibiendo como parámetro un nº entero positivo lo
 * devuelva invertido */
int main() {
    unsigned n,rest;
    scanf("%u",&n);
    printf("El numero original es: %u\n",n);
    printf("El numero al reves: ");
    while(n>0){
        printf("%u",n%10);
        n = n/10;
    }
    return 0;
}
