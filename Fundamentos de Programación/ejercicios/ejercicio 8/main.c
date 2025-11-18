#include <stdio.h>
/* Programa en C que lea base y altura de 2 triángulos y diga mal cual tiene
 * menor área */
int main() {
    int b,h,b1,h1;
    printf("Introduce la base del primer triangulo: ");
    scanf("%i",&b);
    printf("Introduce la altura del primer triangulo: ");
    scanf("%i",&h);;
    fflush(stdin);
    printf("Introduce la base del segundo triangulo: ");
    scanf("%i",&b1);
    fflush(stdin);
    printf("Introduce la altura del segundo triangulo: ");
    scanf("%i",&h1);
    fflush(stdin);

    printf("El area del primer triangulo: %i\n",b*h);
    printf("El area del segundo triangulo: %i\n",b1*h1);

    if(b*h == b1*h1)
        printf("EL AREA ES IGUAL");
    else if(b*h < b1*h1)
        printf("El area del primer triangulo es menor");
    else if( b*h > b1*h1)
        printf("El area del segundo es menor");
    return 0;
}
