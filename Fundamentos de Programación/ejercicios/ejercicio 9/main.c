#include <stdio.h>
/*Programa en c que lea un caracter y diga si es un letra mayúscula, una
 * minúscula, un digito u otro distinto a estos*/
int main() {
    char c;
    printf("Introduce el digito: ");
    scanf("%c",&c);
    if(c >= 'A' && c<= 'Z')
        printf("La letra es mayuscula");
    else if(c>= 'a' && c<= 'z')
        printf("La letra es minuscula");
    else if(c>= '0' && c<= '9')
        printf("Es un digito");
    else
        printf("Es otro caracter: %c",c);
    return 0;
}
