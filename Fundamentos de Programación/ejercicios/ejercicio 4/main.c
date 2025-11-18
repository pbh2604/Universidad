#include <stdio.h>
/*El programa lee 3 números enteros e imprime por pantalla el mayor de los tres*/
int main() {
    int n,n1,n2;
    printf("Introduce 3 valores para los numeros enteros:");
    scanf("%i %i %i",&n,&n1,&n2);
    /*if ( n >= n1) {
        if (n >= n2)
            printf("Introduce mayor valor es: %i",n);
        else
            printf("Introduce mayor valor es: %i",n2);
    }else
        if(n1 >= n2)
            printf("El mayor valor es: %i",n1);
        else
            printf("Introduce mayor valor es: %i",n2);*/
    //Otra forma de hacerlo
    printf("El mayor valor de los tres: %i",(n>=n1)?((n>=n2)?n:n2):((n1>=n2)?n1:n2));
    return 0;
}
