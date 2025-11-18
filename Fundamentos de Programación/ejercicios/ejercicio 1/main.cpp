#include <stdlib.h>
#include <stdio.h>

/* Escribir un programa que lea por teclado 2 valores enteros positivos correspondientes
   a los lados de un rectángulo y luego el radio de un cículo entero (entero positivo
   también) y muestre por pantalla el área de ambas figuras. */
int main() {
    unsigned l1,l2,r;
    printf("Introduce los valores del rectangulo y el radio del circulo:");
    scanf("%u %u %u",&l1,&l2,&r);
    printf("El area del rectángulo es: %u, y el del circulo: %.2f",l1*l2,3.14*r*r);
    return 0;
}
