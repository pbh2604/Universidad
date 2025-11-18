#include <stdio.h>
/*Función que recibe como parámetro 2 números enteros y 1 caracter( que será
 '+', '-', '*', '/' o '%'), devuelva como resultado el valor obtenido al operar. */

float operar(int , int , char);

int main() {
    int n,n1;
    char c;
    printf("Introduce el primer valor entero: ");
    scanf("%i",&n);
    printf("Introduce el segundo valor entero: ");
    scanf("%i",&n1);
    fflush(stdin);
    printf("Introduce el valor del caracter puede ser(*,-,/,%,*): ");
    fflush(stdin);
    do {
        scanf("%c", &c);
    }while(c != '*'  && c != '-' && c != '/' && c != '+' && c != '%');
    printf("El resultado es: %.2f",operar(n,n1,c));
    return 0;
}

float operar(int n, int n1, char c){
    switch(c){
        case '*': return n*n1;break;
        case '+': return n+n1;break;
        case '-': return n-n1;break;
        case '/': return n/n1;break;
        case '%': return n%n1;break;
    }
}
