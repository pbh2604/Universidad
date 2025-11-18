#include <stdio.h>
#include <stdlib.h>
#define N 200
/* DATO IMPORTANTE: Si quieres meter valores en una estructura lo que tienes que hacer es hacerlo como un puntero utilizando &...->..., de caso contrario
y solo quieres acceder al contenido de los valores de la estructura lo que tienes que hacer es utilizar .*/
    struct Tfecha {
    int dia, mes, anio;
    };

    struct Tcliente {
    char apellidos[40+1];
    struct Tfecha antiguedad;//OJO CON ESTO, que se puede concatenar estructuras, para poder meter variables de tipo Tfecha en Tcliente.
    float ultimaCompra;
    };

    struct TlistaClientes{
    int numClientes;
    struct Tcliente arrayClientes[N];
    };

void scanFecha(struct Tfecha *);
void printFecha (struct Tfecha);
void scanCliente (struct Tcliente *);
void printCliente (struct Tcliente);
void printListaClientes (struct TlistaClientes);
void inicializarLista (struct TlistaClientes *);
void anadirCliente (struct TlistaClientes *);
int longitudLista (struct TlistaClientes);

int main()
{
    struct TlistaClientes lista;
    longitudLista(lista);
   // return 0;

}
void scanFecha(struct Tfecha *fecha){
    printf("dia? ");
    scanf("%d",&fecha->dia);
    printf("mes? ");
    scanf("%d",&fecha->mes);
    printf("anio? ");
    scanf("%d",&fecha->anio);
}

void printFecha (struct Tfecha fecha){
    printf("\nantiguedad: %d-%d-%d",fecha.dia,fecha.mes,fecha.anio);
    }

void scanCliente (struct Tcliente *cliente){
    printf("apellidos? ");
    scanf("%s",&cliente->apellidos);
    scanFecha(&cliente->antiguedad);
    printf("ultima compra: ");
    scanf("%f",&cliente->ultimaCompra);
}

void printCliente (struct Tcliente cliente){
    struct Tfecha antiguedad;
    printf("\napellidos: %s",cliente.apellidos);
    fflush(stdin);
    printFecha(cliente.antiguedad);
    printf("\nultima compra: %.2f",cliente.ultimaCompra);
}

void printListaClientes (struct TlistaClientes clientes){
    for(int i=0;i<clientes.numClientes;i++)
        printCliente(clientes.arrayClientes[i]);
}

void inicializarLista (struct TlistaClientes *clientes){
    clientes->numClientes=1;
}

void anadirCliente (struct TlistaClientes *clientes){
    int i;
    struct Tcliente arrayClientes[N];
    char letra;
    scanCliente(&clientes->arrayClientes[0]);
    inicializarLista(&clientes->numClientes);
    for(i=1;i=(clientes->numClientes);i++){
        printf("anadir cliente?");
        fflush(stdin);
        scanf("%c",&letra);
        if(letra == 's'){
                scanCliente(&clientes->arrayClientes[i]);
                (clientes->numClientes)++;
            }else if(letra == 'n'){
                printListaClientes(*clientes);
                return 0;
                }
        }
}
int longitudLista (struct TlistaClientes clientes){
    if(clientes.numClientes < N)
        anadirCliente(&clientes);
}







