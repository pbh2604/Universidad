#include <stdio.h>
/*Programa que lea de teclado una vocal en minúscula y a continuación
 * leerá caracteres de teclado hasta que aparezca la vocal leida en mayúscula */
int main() {
    char v,c;
    printf("Introduce la vocal: ");
    do{
        scanf("%c",&v);
    }while(v != 'a' && v != 'e' && v != 'i' && v != 'o' && v != 'u');
    printf("Introduce los caracteres: ");
    do{
        scanf("%c",&c);
    }while(c != v-'a' +'A');
    return 0;
}
