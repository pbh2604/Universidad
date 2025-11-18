#include <stdio.h>
/*funcion que recibe como parámetro entero long, que quite todos los
 * dígitos pares que contenga y lo devuelva como resultado*/
long quitar_pares(long);

int main() {
    printf("EL numero del resultado: %ld ",quitar_pares(182374));
    return 0;
}

long quitar_pares(long n){
    long aux = 0;
    for(;n;n/=10)//n!=0
        if(n%2)// n%2!=0
            aux= aux*10+n%10;//sale inverso
    for(;aux!=0;aux /= 10)// lo volvemos a la normalidad
        n = n*10 + aux%10;
    return n;
}

