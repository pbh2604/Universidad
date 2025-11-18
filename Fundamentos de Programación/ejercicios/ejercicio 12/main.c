#include <stdio.h>
/* Programa que lea un digito en tre el 1 y el 9, y lo imprima como numero romano*/
int main() {
    char c;
    printf("Introduce el digito entre el 1 y el 9: ");
    scanf("%c", &c);
    switch(c){
        case '1': printf("I");break;
        case '2': printf("II");break;
        case '3': printf("III");break;
        case '4': printf("IV");break;
        case '5': printf("V");break;
        case '6': printf("VI");break;
        case '7': printf("VII");break;
        case '8': printf("VIII");break;
        case '9': printf("IX");break;
    }
    return 0;
}
