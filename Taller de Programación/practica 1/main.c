#include <stdio.h>
/*DATO IMPORTANTE: Es que los char al mostrarlos en pantalla, cuando pones un %d en vez de un %c, muestra el valor de la letra en la tabla ASCII*/
/*OTRO DATO IMPORTANTE: while y do while, en el while solo se ejecuta si se cumple la condición, pero en el do while, se asegura que se ejecute
al menos una vez.
OJO: En el do while: cuando pones la condición tienes que poner el valor contrario al que quieres */
int   main(){
    unsigned long int seg,min,h,seg2,aux1,aux2;
    int i,aux = 100000,aux3;
    printf("Introduce un numero en segundos: ");
    scanf("%i",&seg);
    seg2 = seg;
    if(seg >59){
        min= seg/60;
        seg= seg%60;
        if(min>59){
            h= min/60;
            min= min%60;
            if(h<24){
                printf("la hora es %hu:%hu:%hu\n",h,min,seg);
            }
        }
    }

    do{
        aux= aux/10;
    }while(aux>seg2);

    for(i=0;seg2>aux && aux2!=1;i++){
        aux1= seg2/aux;
        seg2=seg2%aux;
        aux2=0;
        if(aux==10){
            printf("%hu%hu",seg2,aux1);
            aux2=1;
        }
        aux = aux/10;
    }

    return 0;
}
