#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Programa que lea caracteres por teclado, si se ve letra mayúcula imprima la
correspondencia en minúscula y vicerversa, si lee un dígito imprimas el valor
 resultante de sumarle 80 ( * = fin)(cualquier otro caracter se imprima) */
int main() {
    char c;
    printf("Introduce caracteres (* para acabar): ");
    do{
        scanf("%c",&c);
        if(c >= 'a' && c <= 'z')
            printf("%c",c-'a'+ 'A');
        else if(c >= 'A' && c <='Z')
            printf("%c",c-'Z'+ 'z');
        else if( c>= '0'&& c<= '9')
            printf("%i",c -'0'+80);
    }while(c != '*');
    return 0;
}
