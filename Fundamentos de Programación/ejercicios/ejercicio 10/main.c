#include <stdio.h>
/*Programa en c que lea un caracter y diga si es un letra mayúscula, una
 * minúscula, un digito u otro distinto a estos
 * A este ejercicio se le añade el complemento de mirar si es una vocal*/
int main() {
    char c;
    printf("Introduce un caracter: ");
    scanf("%c",&c);

    if(c >= 'A' && c<= 'Z')
        if(c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
            printf("Es una vocal mayuscula");
        else
            printf("La letra es mayuscula");
    else if(c>= 'a' && c<= 'z')
        if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            printf("Es una vocal minuscula");
        else
            printf("La letra es minuscula");
    else if(c>= '0' && c<= '9')
        printf("Es un digito");
    else
        printf("Es otro caracter: %c",c);
    return 0;
}