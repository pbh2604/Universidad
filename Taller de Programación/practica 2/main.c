#include <stdio.h>
/*DATO IMPORTANTE: LA DIFERENCIA ENTRE & Y * EN LOS PUNTEROS, ES QUE & APUNTA A LA DIRECCIÓN DE MEMORIA Y * LO
QUE HACE ES APUNTAR AL CONTENIDO DE LA DIRECCIÓN DE MEMORIA.
EJM: BOLSA PELOTAS EN ESTE CASO & SERÍA LA BOLSA Y * SERÍA EL CONTENIDO DE LA BOLSA, EN ESTE CASO LAS PELOTAS*/
/*OTRO DATO IMPORTANTE: LAS DECLARACIONES DE LAS FUNCIONES SE REDUCE CUANDO SON VALORES INT, CHAR, PERO SI DEPENDEN LA PRIMERA APARICIÓN DE LA SEGUNDA DE
LA FUNCIÓN (VOID (1APARACIÓN,2APARICIÓN)), NO SE BORRA NADA, CUANDO SON PUNTEROS SE BORRA SOLO LA LETRA Y SE DEJA EL ASTERÍSCo; EN LAS MATRICES SE DEJA
EL TAMAÑO, PERO SE BORRA EL NOMBRE LA MATRIZ, CUANDO SON ESTRUCTURAS FUNCIONA IGUAL QUE CUADO ESTAS CON UN ENTERO, Y CUANDO ES UN PUNTERO PONES EL ASTERÍSCO
struct Tfecha *
struct Tfecha */
void intercambio(unsigned *, unsigned *);
void valores(unsigned *,unsigned *, unsigned *,unsigned *);

int main(){

    unsigned x,y,a,b;//x y a valor de las líneas e y e b valor de las columnas.
    unsigned z,c,o,p;
    valores(&x,&y,&a,&b);
    if(x<25 && y<80 || a<25 && b<80){
            if(x<a || y<b){
                intercambio(&a,&x);
                intercambio(&b,&y);
                }
    if((a-x)!=(b-y)){
    printf("El area del rectangulo tiene valor introducido de: %u\n",(a-x)*(b-y));
        }else{
                printf("Es un cuadrado,su area: %u\n",(a)*(b));
                }
    }
    valores(&z,&c,&o,&p);
    if(x<25 && y<80 || a<25 && b<80){
            if(o<z || c<p){
                    intercambio(&z,&o);
                    intercambio(&p,&c);
                    }
                    }
    if((z-o)<=(a-x)){
        if((p-c)<=(b-y)){
            printf("El rectangulo introducido esta   dentro.\n");
        }else{
        printf("El rectangulo no esta introducido.");}
    }else{
        printf("El rectangulo no esta introducido.");}
    }
void valores(unsigned *a,unsigned *b, unsigned *c,unsigned *d){
    printf("Introduce el valor de las lineas: ");
    scanf("%u",a);
    printf("Introduce el valor de las columnas: ");
    scanf("%u",b);
    printf("Introduce el valor de las lineas: ");
    scanf("%u",c);
    printf("Introduce el valor de las columnas: ");
    scanf("%u",d);
}
void intercambio(unsigned *a,unsigned *b){
    int aux=*a;
        *a=*b;
        *b=aux;
}

