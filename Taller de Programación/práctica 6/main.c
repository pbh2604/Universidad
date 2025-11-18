#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 8

int aleatorio (int,int);
void rellenar(int [N][N]);
void imprimir(int [N][N]);
void multiplicarmat1(int [N][N],int [N][N]);
void triangular_superior (int [N][N]);
void multiplicarmat2(int [N][N],int [N][N]);
void triangular_inferior(int [N][N]);
void identidad(int [N][N]);



int main(){
    srand(time(NULL));
    int m1[N][N];
    int m2[N][N];
    rellenar(m1);
    printf("IMPRIMO MATRIZ 1: \n\n");
    imprimir(m1);
    printf("\n");
    rellenar(m2);
    printf("IMPRIMO MATRIZ 2: \n\n");
    imprimir(m2);
    printf("\n");
    multiplicarmat1(m1,m2);
    printf("IMPRIMO MATRIZ MULTIPLICAR DE MATRIZ 1 POR MATRIZ 2: \n\n");
    imprimir(m1);
    printf("IMPRIMO MATRIZ TRIANGULAR SUPERIOR DE LA MATRIZ 1: \n\n");
    triangular_superior(m1);
    imprimir(m1);
    printf("IMPRIMO MATRIZ TRIANGULAR SUPERIOR DE LA MATRIZ 2: \n\n");
    triangular_superior(m2);
    imprimir(m2);
    multiplicarmat2(m2,m1);
    printf("IMPRIMO MATRIZ MULTIPLICAR DE MATRIZ 2 POR MATRIZ 1: \n\n");
    imprimir(m2);
    printf("IMPRIMO MATRIZ TRIANGULAR INFERIOR DE LA MATRIZ 1: \n\n");
    triangular_inferior(m1);
    imprimir(m1);
    multiplicarmat2(m2,m1);
    printf("IMPRIMO MATRIZ MULTIPLICAR DE MATRIZ 2 POR MATRIZ 1: \n\n");
    imprimir(m2);
    identidad(m2);
    printf("IMPRIMO MATRIZ iDENTIDAD DE MATRIZ 2: \n\n");
    imprimir(m2);
    multiplicarmat1(m1,m2);
    printf("IMPRIMO MATRIZ MULTIPLICAR DE MATRIZ 1 POR MATRIZ 2: \n\n");
    imprimir(m1);

}

int aleatorio (int inf, int sup){
    int aux;
    if (inf > sup){
        aux = inf;
        inf = sup;
        sup = aux;
       }
       return(inf+rand()%(sup+1-inf));
    }


void rellenar(int matriz[N][N]){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            matriz[i][j] = aleatorio(-20,20);
        }
    }
}

void imprimir(int matriz [N][N]){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("%10d",matriz[i][j]);
        }
        printf("\n");
    }
}

void multiplicarmat1(int matriz1[N][N],int matriz2 [N][N]){
    int matrizAux[N][N],suma,a,i,j;
    for ( a = 0; a < N; a++) {//es un valor fijo para las columnas de la segunda matriz, ya que si no lo utilizo al guardar el valor suma en la matriz aux ,se guardaría en otra posición que no es la primera.
        for ( i = 0; i < N; i++) {
                suma=0;//importante reiniciar la suma porque si no el valor de la suma se acumula.
            for ( j = 0; j < N; j++) {
                suma += matriz1[i][j] * matriz2[j][a];//así es como se multiplican matrices
                //mirarlo con el dibujo de las matrices originales en papel
                }
            matrizAux[i][a] = suma;
        }
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
                matriz1[i][j] = matrizAux[i][j];
                }
        }
}

void triangular_superior (int matriz[N][N]){
        for(int i=0;i<N;i++)
            for(int j=0;j<N;j++)
                    if(i > j)
                        matriz [i][j] = 0;
}

void multiplicarmat2(int matriz2[N][N],int matriz1 [N][N]){
    int suma;
    int matrizAux[N][N];
    for (int a = 0; a < N; a++) {//es un valor fijo para las columnas de la segunda matriz, ya que si no lo utilizo al guardar el valor suma en la matriz aux ,se guardaría en otra posición que no es la primera.
        for (int i = 0; i < N; i++) {
                suma=0;//importante reiniciar la suma porque si no el valor de la suma se acumula.
            for (int j = 0; j < N; j++) {
                suma += matriz2[i][j] * matriz1[j][a];//así es como se multiplican matrices
                //mirarlo con el dibujo de las matrices originales en papel
                }
            matrizAux[i][a] = suma;
        }
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
                matriz2[i][j] = matrizAux[i][j];
                }
        }
}

void triangular_inferior(int matriz[N][N]){
    for(int i=0;i<N;i++)
            for(int j=0;j<N;j++)
                    if(j > i)
                        matriz [i][j] = 0;

}
void identidad(int matriz[N][N]){
    for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                    if( i!=j){
                        matriz [i][j] = 0;
                            }else{
                                matriz[i][j]=1;
                            }
                        }
                    }
}



