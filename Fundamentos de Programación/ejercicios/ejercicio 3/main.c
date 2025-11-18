#include <stdio.h>

/* Que lea 2 letras mayúsculas y un caracter, y diga si el caracter es una
 * mayúscula entre las dos letras leidas en primer lugar.*/
int main() {
    char letra, letra1,c;
    printf(" Los valores en mayUsculas de las letras: ");
    scanf ("%c %c",&letra,&letra1 );
    printf("Introduce el valor del caracter: ");
    fflush(stdin);
    scanf("%c",&c);
    if( letra <= c && c <= letra1)
        printf("El valor esta contenido en el rango");
    else
        printf("El valor NO esta contenido en el rango");
    return 0;
}
