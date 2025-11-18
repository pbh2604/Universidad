#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encriptar.h"

#define OPT_NONE -1
#define OPT_C 0
#define OPT_D 1

#define EXTENSION_DECODE "DECODED"
#define EXTENSION_CODE   "CODED"

#define CAP1 90
#define CAP2 100

int byte(char*);
void fext(char*, char*, char*);
unsigned char binaDecimal (char[8]);

int main(int n, char* cadena[])
{
    FILE         *f_in, *f_out;
    int           opt = OPT_NONE;
    unsigned char valorbyte;
    char          nombre[CAP2];

    if (n != 4)
    {
        printf("\nERROR: Faltan o sobran argumentos");
        printf("\n       [ Argumentos: -c/-d Byte('0'/'1')/(0-255) nombre del fichero ]\n");
        return 1;
    }

    if (!strcmp(cadena[1], "-c"))
        opt = OPT_C;
    else if (!strcmp(cadena[1], "-d"))
        opt = OPT_D;
    else
    {
        printf("\nERROR: Argumento 1: Opcion no reconocida");
        printf("\n       [ Argumentos: -c/-d Byte('0'/'1')/(0-255) nombre del fichero ]\n");
        return 2;
    }

    if (strlen(cadena[2]) == 8)
        valorbyte = binaDecimal(cadena[2]);
    else if (atoi(cadena[2]) >= 0 && atoi(cadena[2]) <= 255)
        valorbyte = atoi(cadena[2]);
    else
    {
        printf("\nERROR: Argumento 2: Tiene que tener 8 char ('0'/'1') o estar entre 0-255");
        printf("\n       [ Argumentos: -c/-d Byte('0'/'1')/(0-255) nombre del fichero ]\n");
        return 3;
    }

    if (!byte(cadena[2]))
    {
        printf("\nERROR: Argumento 2: Tiene que ser compuesto de '0' y '1'");
        printf("\n       [ Argumentos: -c/-d Byte('0'/'1')/(0-255) nombre del fichero ]\n");
        return 4;
    }

    if (strlen(cadena[3]) > CAP1)
    {
        printf("\nERROR: El nombre del fichero es muy grande\n");
        return 5;
    }

    if (!(f_in = fopen(cadena[3], "r")))
    {
        printf("\nERROR: No se puede abrir el archivo %s\n", cadena[3]);
        return 5;
    }

    switch (opt)
    {
        case OPT_C:
            fext(nombre, cadena[3], EXTENSION_CODE);
            if (!(f_out = fopen(nombre, "w")))
            {
                printf("\nERROR: No se puede abrir el archivo %s\n", nombre);
                return 5;
            }
            codificar(f_in, f_out, valorbyte);
            break;

        case OPT_D:
            fext(nombre, cadena[3], EXTENSION_DECODE);
            if (!(f_out = fopen(nombre, "w")))
            {
                printf("\nERROR: No se puede abrir el archivo %s\n", nombre);
                return 5;
            }
            decodificar(f_in, f_out, valorbyte);
            break;
    }

    fclose (f_in);
    fclose (f_out);

    return 0;
}

int byte(char* byte)
{
    for (; *byte && (*byte == '1' || *byte == '0'); byte++)
    return *byte == '1' || *byte == '0';
}

void fext(char* fnv_nombre, char* fnombre, char* fext)
{
    char* i = strchr(fnombre, '.');
    if (!i)
    {
        strcpy(fnv_nombre, fnombre);
        strcat(fnv_nombre, ".");
    }
    else
        strncpy(fnv_nombre, fnombre, i - fnombre + 1);
    strcat(fnombre, fext);
}

unsigned char binaDecimal(char bits[8])
{
    return
        (bits[0] == '1') << 7 +
        (bits[1] == '1') << 6 +
        (bits[2] == '1') << 5 +
        (bits[3] == '1') << 4 +
        (bits[4] == '1') << 3 +
        (bits[5] == '1') << 2 +
        (bits[6] == '1') << 1 +
        (bits[7] == '1');
}
