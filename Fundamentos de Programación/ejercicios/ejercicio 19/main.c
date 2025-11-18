#include <stdio.h>
/*Programa que imprima la tabla de multiplicar cruzada hasta 10
 * ejm: Si fuera hasta 4, habría que imprimir:
 *       1   2   3   4
 *   ----------------------
 *   1|  1   2    3    4
 *   2|  2   4    6    8
 *   3|  3   6    9    12
 *   4|  4   8    12   16*/
int main() {
    int n,i,j;
    do{
        printf("Introduce el valor de la tabla:");
        scanf("%i",&n);
    }while(n<1 || n > 10);
    printf("La tabla es del numero %i\n",n);
    printf("   ");
    for(i =1; i <= n; i++)
        printf("%i   ",i);
    printf("\n");
    for( i =0; i < n; i++)
        printf("----");
    printf("\n");
    for(i = 1;i<=n;i++){
        printf("%i| ",i);
        for(j = 1;j<=n;j++){
            printf("%i   ",i*j);
        }
        printf("\n");
    }
    return 0;
}
