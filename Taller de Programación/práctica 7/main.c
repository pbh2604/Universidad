#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define F 40
#define C 11//por el \0
/*DATO IMPORTANTE: Cuando tenemos una matriz es decir, matriz[F][C],podemos pillar la primera pos de la fila,y estamos seleccionando la fila entera y
creando a su vez una cadena*/
int aleatorio(int, int);
void rellenar(char [F][C]);
void imprimir(char [F][C]);
int comparar(char *, char *);
char* mas_antigua(char [F][C]);

int main(){
    srand(time(NULL));
    char mat[F][C];
    rellenar(mat);
    imprimir(mat);
    fflush(stdin);
    printf("\nLa matricula mas antigua es: %s",mas_antigua(mat));
    printf("\n");
    return 0;
}

int aleatorio(int inf, int sup){
    int aux = inf;
    if (inf > sup)
       {  inf = sup;
          sup = aux;
       }
    return (rand()%(sup-inf+1)+inf);
}

void rellenar(char matriz[F][C]){
    for(int i=0;i<F;i++){
        matriz [i][0] = 'E';
        matriz [i][1] = '-';
        matriz [i][6] = '-';
        matriz [i][10] = '\0';
        for(int j=0;j<C;j++){
                if(j>1 && j<6){
                    matriz[i][j] = aleatorio('0','9');
                }else if(j>6 && j<10){
                    matriz[i][j] = aleatorio('A','Z');
                }
            }
        }
    }
void imprimir(char matriz[F][C]){
    for(int i = 0;i<F;i++){
        printf("%s\n",matriz[i]);
        }

}

int comparar(char *cadena1, char *cadena2){//recuerda char aux[N] = char *aux, apunto a la primera dirección de memoria
    int aux = strncmp(cadena1+7,cadena2+7,3);//pongo los numeros porque si puesiera cadena1[i] estaría recaudando la información y de la manera que lo pongo solo estoy apuntando a la información para comparar
    if (aux == 0)
        aux = strncmp(cadena1+2,cadena2+2,4);
    return aux;
}

char* mas_antigua(char matriz[F][C]){//lo que hace es guardar el valor del return en una dirección de memoria, ya que de esta forma no se borra el valor que es lo que pasa en una función normal y puedes itilzarlo posteriormente.
    int i,pos_antigua = 0;
    char masAnt[C];
    strcpy(masAnt,matriz[0]);
    for(i=1;i<F-1;i++)
        if(comparar(matriz[i],matriz[pos_antigua])<0)
            pos_antigua = i;
    return matriz[pos_antigua];
}
