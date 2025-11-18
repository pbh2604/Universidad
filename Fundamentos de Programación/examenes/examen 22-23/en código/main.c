#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define N 5

int main(){
    char c;
    int array[26] = {0},total=0,i;
    printf("Introduzca letras mayusculas <Z para acabar>: \n");
    fflush(stdin);
    do{
        do {
            scanf("%c", &c);
            //fflush(stdin);
        }while(c<'A' || c>'Z');
            total++;
            array[c-'A']++;
    }while(c != 'Z');

    printf("\nLas veces que ha aparecido cada letra y su secuencia es: \n");
    fflush(stdin);

    printf("%i\n",total);
    for(i=0;i<26;i++)
        if(array[i] > 0) {
            printf("%c    %i   %.2f \n", i + 'A', array[i], (float) array[i]*100/total );
            fflush(stdin);
        }
    return 0;
}
