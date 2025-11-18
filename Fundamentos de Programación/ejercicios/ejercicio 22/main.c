#include <stdio.h>
/*Una función que recibe como parámetro:
 - si: mayúscula --> que imprima desde la letra hasta z en mayúscula
 - si: minúscula --> que imprima desde la letra hasya a en minúscula*/

void imprimir_letras(char );

int main() {
    char c;
    printf("Introduce una letra: ");
    scanf("%c",&c);
    imprimir_letras(c);
    return 0;
}

void imprimir_letras(char c){
    if(c >= 'A' && c <= 'Z'){
        for (; c <= 'Z'; c++)
            printf("%c ", c);
    }else if(c >= 'a' && c <= 'z'){
        for (; c >= 'a'; c--)
            printf("%c ", c);
    }
}
