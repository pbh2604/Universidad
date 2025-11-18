#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 30

int aleatorio (int, int);
void imprimir (char *);
void rellenar (char *);
void eliminar (char *, char);
void compactar (char *);


main ()
{
    char letras[30],c;
    srand(time(NULL));
    rellenar(letras);
    imprimir(letras);
    do{
        printf("\n\nIntroduzca una letra mayuscula: ");
        fflush(stdin);
        scanf("%c",&c);
    }while(c<'A' || c>'F');
    eliminar(letras,c);
    printf("\n\n");
    imprimir(letras);
    printf("\n\n");
    compactar(letras);
    imprimir(letras);
}

int aleatorio (int inf, int sup)
{
    int aux = inf;

    if (inf > sup)
       {  inf = sup;
          sup = aux;
       }
    return (rand()%(sup-inf+1)+inf);
}
void imprimir(char *cadena){
    for(int i=0; i<N;i++)
        printf("%c ",cadena[i]);

}

void rellenar(char *cadena){
    for(int i=0;i<N;i++)
        cadena[i] = aleatorio('A','F');
}

void eliminar (char *cadena,char letra){
    for(int i=0;i<N;i++){
        if(cadena[i] == letra){
            cadena[i] = '.';
        }
    }
}

void compactar(char *cadena){
    int i, j;
    char auxiliar;
    for(i=0; i<N; i++){//Si quiero ir cambiando algo e ir moviendolo a la derecha, lo que tengo que hacer es utilizar un aux y un bucle externo que sea mayor
        for(j=i+1;j<N; j++)//este bucle siempre va un paso por delante
            if(cadena[i] == '.'){// cuando cumple la condición cambia de posición los caracteres
                auxiliar = cadena[i];
                cadena[i] = cadena[j];
                cadena[j] = auxiliar;
                }

    }
}

