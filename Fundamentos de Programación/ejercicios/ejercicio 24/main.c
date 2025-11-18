#include <stdio.h>
int intervalo(int ,int , int );
/*Programa que haga uso de la función anterior y realice: leer los dos valores del
 * intervalo y, a continuación, ller una secuencia de números enteros imprimiendo
 * para cada n si está o no dentro del intervalo. El program finaliza cuando
 * decida no introducir más números.*/
int main() {
    int a,b,n;
    char c;
    printf("Introduce los valores del intervalo: ");
    scanf("%i %i",&a,&b);
    do{
        printf("Introduce un valor: ");
        fflush(stdin);
        scanf("%i",&n);
        if(!intervalo(n,a,b))
            printf("El valor esta en el intervalo.\n");
        else
            printf("El valor NO esta en el intervalo.\n");
        printf("Introduce otro valor (s/n): ");
        fflush(stdin);
        scanf("%c",&c);
    }while(c == 's' || c == 'S');
    return 0;
}

int intervalo(int n,int a, int b){
    if (a > b){
        int aux = a;
        a = b;
        b = aux;
    }
    return n < a ? -1: n > b ? 1 : 0;
}