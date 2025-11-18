#include <stdio.h>
#include <stdlib.h>
//RECUERDA CUANDO SON PUNTEROS EN LOS PROTOTIPOS NO PONES LA LETRA, SOLO EL ASTERÍSCO.
void scanBit(char *);
void scanNibble(char *,char *, char *, char *);
void printNibble(char ,char ,char ,char);
void rotarNibbleDcha(char *,char *,char *,char *);

int main(int argc, char *argv []){
    char b3,b2,b1,b0; // nibble
    char opcion;
    do{
        scanNibble(&b3,&b2,&b1,&b0);
        printf("\nnibble: ");
        printNibble(b3,b2,b1,b0);
        rotarNibbleDcha(&b3,&b2,&b1,&b0);
        printf ("\nnibble rotado: ");
        printNibble(b3,b2,b1,b0);
        fflush(stdin);
        printf ("\n\nROTAR OTRO NIBBLE (s/n) ? ");
        fflush(stdin);//
        scanf("%c", &opcion);
        fflush(stdin);
    } while (opcion=='s'||opcion=='S');
    return 0;
}

void scanBit(char *c){
    do{
    printf("\tbit ? ");
    fflush(stdin);
    scanf("%c",c);
    }while(*c!='0' && *c!='1');
}

void scanNibble(char *b3,char *b2, char *b1, char *b0){
    printf("NIBBLE:\n");
    printf("bit 3.\n");
    scanBit(b3);//no se pone & porque ya es un puntero.
    printf("bit 2.\n");
    scanBit(b2);
    printf("bit 1.\n");
    scanBit(b1);
    printf("bit 0.\n");
    scanBit(b0);
}

void printNibble(char b3,char b2,char b1,char b0){
    printf("%c%c%c%c",b3,b2,b1,b0);
}

void rotarNibbleDcha(char *b3,char *b2,char *b1,char *b0){
    char aux = *b3;// me ralle era facil...
    *b3 = *b2;     //aux<-b3 / b3<-b2 / b2<-b1 / b1<-b0 / bo <-aux
    *b2 = *b1;     // el valor que se va a introducir siempre a la derecha.
    *b1 = *b0;
    *b0 = aux;

}

