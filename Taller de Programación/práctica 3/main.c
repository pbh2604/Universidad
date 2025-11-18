#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned n;
    char letra,otra_letra;
    while(n){//IMPORTANTE PORQUE SINO, NO FUNCIONA CUANDO COLOCO EL VALOR DE 0.
        do{
            printf("NUMERO del 1 al 10, o 0 para finalizar: ");
            scanf("%u",&n);
            if(!n){ // n==0
                printf("Fin del programa");
                return 0;
            }
        }while(n>10);

        do{
            printf("Introduce una letra entre A y Z: ");
            fflush(stdin);
            scanf("%c",&letra);
        }while((letra > 'A') && (letra < 'Z'));//letra <'A'|| letra>'Z'

    for(int i=1;i<=n;i++){
        for(int j=0;j<i;j++){
            otra_letra = letra +j;
            if(otra_letra>'Z')
                otra_letra -= 26;
            printf("%c",otra_letra);
            }
            printf("\n");
        }
    }
    return 0;
}

