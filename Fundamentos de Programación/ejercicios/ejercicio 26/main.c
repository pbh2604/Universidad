#include <stdio.h>
/*funcion pasando como parámetro los días que tiene 1 mes y el dia de la
 * semana que cae el día 1 de ese mes imprima el calendario de ese mes */

void calendario(unsigned , unsigned );

int main() {
    calendario(29,4);
    return 0;
}
void calendario(unsigned dias, unsigned dsemana){
    int i,j;
    printf("L  M  X  J  V  S  D\n");
    for(i=1;i<dsemana;i++)
        printf("   ");
    for(i=dsemana,j=1;j<=dias;i++,j++) {
        if (i == 8) {
            printf("\n");
            i=1;
        }
        printf("%i  ",j);
    }

    printf("1");
}


