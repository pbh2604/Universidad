#include <stdio.h>
/*Programa que lea de teclado caracteres(al menos 1) y realice:
 * Si es un digito: sumar los valores de los digitos hasta el 9
 * EJM: LEE el 6, imprime la suma de 6+7+8+9
 * Si es un caracter mayúscula: imprime 5 letras posteriores o hasta llegar a la Z
 * EJM: LEE T, imprime T U V X Y Z
 * Si es otro caso no hará nada, finaliza cuando lea '*' */
int main() {
    char c;
    int i;
    do {
        scanf("%c", &c);
        if(c >= '0'&& c <= '9'){
            for(i=0; c <= '9';c++)
                i += c-'0';
            printf("El resultado de la suma es: %i\n",i);
        }
        if(c >= 'A' && c <= 'Z') {
            while (c <= 'Z') {
                printf("%c ",c);
                c++;
            }
            printf("\n");
        }
        }while(c != '*');
    return 0;
}
