#include <stdio.h>
#include <stdlib.h>

/* De acuerdo al precio de la predna efectuas un descuento.
 * SI:  1-10 -> 0%
 *      11-100 -> 10%
 *      >100 -> 25%
 */
int main() {
    float n;
    printf("Introduce el precio de la prenda: ");
    scanf("%f",&n);
    if(n > 10 && n <= 100)
        printf("Se ha efectuado un descuento del 10%: %.3f",n*0.9);
        else if(n > 100)
            printf("Se ha efectuado un descuento del 25%: %.3f",n*0.75);
        else
            printf("No se ha efectuado ningun descuento: %.2f",n);
    return 0;
}
