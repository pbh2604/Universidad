#include <stdio.h>
/*funcion que pasándole de parámetro un punto de las coordenadas x e y
 * enteros y un radio nos diga si el punto queda dentro de la circunferencia
 * */

void dentro(int, int, unsigned);

int main() {
    dentro(1,4,3);
    return 0;
}

void dentro(int x, int y, unsigned radio){
    if(x<0)
        x *=(-1);
    else if(y < 0)
        y *=(-1);
    if(x <= radio && y<= radio)
        printf("El punto esta contenido en la circunferencia");
    else
        printf("El punto no esta contenido en la circunferencia");
}
