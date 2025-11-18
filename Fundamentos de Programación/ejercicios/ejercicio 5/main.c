#include <stdio.h>

/*programa que lea 2 valores enteros por teclado(0:fin) e imprima
 * al final el menor y el mayor de los valores leidos*/
int main(){
    int n,n1,aux;
    while(aux !=0) {
        printf("Introduce el primer valor: ");
        scanf("%i", &n);
        printf("Introduce el segundo valor: ");
        fflush(stdin);
        scanf("%i", &n1);
        if (n > n1)
            printf("El mayor es %i y el menor es %i\n", n, n1);
        else
            printf("El mayor es %i y el menor es %i\n", n1, n);
        printf("Introduce 0 para finalizar el programa: ");
        scanf("%i",&aux);
    }
    return 0;
}
