#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//structs
typedef enum{
    FILE_ERROR
}F_ERROR;

typedef struct{
    char identificador[11];
    unsigned apuesta[6];
}Apuesta;

//prototipos
int aleatorio(int, int);
void crear_identificador(char [11]);
void crear_num(unsigned [6]);
void crear_apuesta(Apuesta*);
void crear_apuestas(const char *, unsigned);

//main
int main(void){
   char nombre[20];
   unsigned apuesta;

   srand(time(NULL));
   printf("Donde guardaras las apuestas? :");
   gets(nombre);

   printf("\nNumero de apuestas quieres generar? :");
   scanf("%u", &apuesta);
   fflush(stdin);
   crear_apuestas(nombre, apuesta);
   return 0;
}

//funciones
void crear_apuestas(const char *nombre, unsigned _ap){
    int i;
    FILE* f_in;
    Apuesta apuesta;
    if (!(f_in=fopen(nombre, "wb")))
        exit(FILE_ERROR);
    for (i=0; i<_ap; i++){
            crear_apuesta(&apuesta);
    fwrite(&apuesta, sizeof(Apuesta), 1, f_in);
    }
    fclose(f_in);
}

void crear_identificador(char _iden[11]){
    int i;
    _iden[0] = '2';
    _iden[1] = '8';
    for (i=2; i<10; i++)
        _iden[i] = aleatorio('0', '9');
    _iden[10] = aleatorio('A', 'Z');
    _iden[11] = '\0';
}

void crear_num(unsigned num[6]){
    int i, j;
    for (i=0; i<6;){
        num[i] = aleatorio(1, 49);
    for (j=0; j<i && num[j] != num[i]; j++);
    if (j == i)i++;}
    }

void crear_apuesta(Apuesta* apuesta){
    crear_identificador(apuesta->identificador);
    crear_num(apuesta->apuesta);
}

int aleatorio(int inf, int sup){
    int aux = inf;
    if (inf > sup){
        inf = sup;
        sup = aux;
    }
    return (rand()%(sup-inf+1)+inf);
}

