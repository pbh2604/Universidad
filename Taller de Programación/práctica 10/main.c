#include <stdio.h>
#include <stdlib.h>
//estructuras

struct Tnodo {
    int dato;
    struct Tnodo *siguiente;
} ;

struct TlistaNodos {
   struct Tnodo *inicio;
} ;

//declaración funciones
void iniciarLista(struct TlistaNodos *);

void insertarListaCircular (int, struct TlistaNodos *);
// crea un nodo, cuyo campo dato es un integer e inserta dicho nodo en una lista

void recorrerListaCircular (struct TlistaNodos);
// recorre una lista y printa el contenido del campo dato de cada nodo


//main

int main()
{
    struct TlistaNodos lista;
    iniciarLista(&lista);
    insertarListaCircular(5,&lista);
    insertarListaCircular(7,&lista);
    recorrerListaCircular(lista);
    return 0;
}

//funciones
void iniciarLista(struct TlistaNodos *lista){
 lista->inicio = NULL;
}

void insertarListaCircular(int valor, struct TlistaNodos *lista){
    struct Tnodo *nodo;
    nodo = malloc (sizeof(struct Tnodo));
    nodo->dato = valor;
    nodo->siguiente = lista->inicio;
    lista->inicio= nodo;
}

void recorrerListaCircular(struct TlistaNodos lista){
    struct Tnodo *nodo;
    nodo = lista.inicio;
    if(nodo != NULL){
        do{
           printf("%d-> ",nodo->dato);
           nodo = nodo->siguiente;
        }while(nodo != lista.inicio);
    }
}
