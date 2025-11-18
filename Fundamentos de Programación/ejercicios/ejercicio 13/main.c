#include <stdio.h>
/*Programa en c que lea un entero n (tiene que ser distinto de 0 ) e imprima
 * por pantalla la serie armónica 1/1 , 1/2, 1/3 ,..., 1/n */
int main() {
    int n;
    do{
       printf("Introduce un numero distinto de 0: ");
       scanf("%i",&n);
    }while(n <= 0);
    for(int i = 1;i < n ; i++)
        printf("1/%i,",i);
    printf("1/%i",n);
    return 0;
}
