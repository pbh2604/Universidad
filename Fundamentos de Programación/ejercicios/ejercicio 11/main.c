#include <stdio.h>
/*Programa en c que lea el día mes y año de dos fechas e imprima la fecha
 * más reciente (simplificar: todos los mese tienen 30 días) */
int main() {
    unsigned dia,mes,anio,dia1,mes1,anio1,diatotal,diatotal1;
    do{
        printf("Introduce el dia de la primera fecha: ");
        scanf("%i",&dia);
    }while(dia > 30);
    do{
        printf("Introduce el mes de la primera fecha: ");
        scanf("%i",&mes);
    }while(mes > 12);
        printf("Introduce el anio de la primera fecha: ");
    scanf("%i",&anio);

    do{
        printf("Introduce el dia de la segunda fecha: ");
        scanf("%i",&dia1);
    }while(dia1 > 30);
    do{
        printf("Introduce el mes de la segunda fecha: ");
        scanf("%i",&mes1);
    }while(mes1 > 12);
    printf("Introduce el anio de la segunda fecha: ");
    scanf("%i",&anio1);

    diatotal = dia +(mes-1)*30 + (anio-1)*365;
    diatotal1 = dia1 +(mes1-1)*30 + (anio1-1)*365;

    if(diatotal < diatotal1)
        printf("%i-%i-%i",dia1,mes1,anio1);
    else
        printf("%i-%i-%i",dia,mes,anio);

    return 0;
}
