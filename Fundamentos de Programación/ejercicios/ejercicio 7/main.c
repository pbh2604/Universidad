#include <stdio.h>
/*Programa que lea entero y si es postivo imprima su  cuadrado*/
int main() {
    int n;
    printf("Introduce un entero: ");
    scanf("%i",&n);
    if(n > 0)
        printf("%i",n*n);
    else
        printf("No se puede hacer debido a que es negativo");
        return 0;
}
