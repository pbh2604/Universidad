#include <stdio.h>
/*programa que imprima en cuatro columnas los caracteres correspondientes a
 * los codigo ASCII(del 32 al 255)*/
int main() {
    int cont =0;
    for (int i = 32; i < 256; i++) {
        printf("%c ",i);
        if (cont == 3){
            printf("\n");
            cont = 0;
        }
        cont++;
    }
    return 0;
}
