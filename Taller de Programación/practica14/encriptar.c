#include <stdio.h>
#include "encriptar.h"

char* rotar (unsigned char* c)
{
    /*
    * === Resultado que queremos: Poner los dos ultimos bits como los dos primeros
    * 'A' = 01000001 -> 01010000
    *             --    --
    *
    * === Funcionamiento:
    *
    * - mask = 3:
    *      3  = 00000011
    *
    * - char = 'A':
    *     'A' = 01000001
    *
    * (1) ults = bits que queremos rotar de char (los 2 ultimos):
    *     00000011 (mask)
    *   & 01000001 (char)
    *  -------------------
    *     00000001 (ults)
    *
    * (2) Desplazamos ults a la izquierda:
    *     00000001 << 6 = 01000000
    *
    * (3) Desplazamos char dos veces a la derecha (Damos 'espacio' para los ults):
    *     01000001 >> 2 = 00010000
    *
    * (4) Ponemos los ultimos dos bits (ults) en las primeras dos posiciones de char
    *     01000000 (ults)
    *   | 00010000 (char)
    *  -------------------------
    *     01010000 (char rotado)
    *
    *
    * === Podemos calcularlo en una linea:
    *
    *   char = ( ( char & 3 ) << 6 ) | ( char >> 2 )
    *          | |____(1)___|      |   |____(3)____|
    *          |_________(2)_______|
    *          |________________(4)________________|
    *
    */
    *c = ( ( *c & 3 ) << 6 ) | (*c >> 2);
    return c;
}

char* desrotar (unsigned char* c)
{
    /*
    * === Funcionamiento:
    *
    * - mask = 3 << 6 = 192:
    *      192  = 11000000
    *
    * - char rotado = 'A' rotado:
    *     'A' rotado = 01010000
    *
    * (1) prims = bits que queremos rotar (los 2 primeros):
    *     11000000 (mask)
    *   & 01010000 (char rotado)
    *  -------------------
    *     01000000 (prims)
    *
    * (2) Desplazamos prims a la derecha:
    *     01000000 >> 6 = 00000001
    *
    * (3) Desplazamos char rotado dos veces a la izquierda:
    *     01010000 << 2 = 01000000
    *
    * (4) Ponemos los primeros dos bits (prims) en las ultimas dos posiciones de char rotado
    *     00000001 (prims)
    *   | 01000000 (char rotado)
    *  -------------------------
    *     01000001 (char)
    *
    *
    * === Podemos calcularlo en una linea:
    *
    *   char = ( ( char & 192 ) >> 6 ) | ( char << 2 )
    *          | |____(1)_____|      |   |____(3)____|
    *          |_________(2)_________|
    *          |_________________(4)_________________|
    *
    */
    *c = ( ( *c & 192 ) >> 6 ) | (*c << 2);
    return c;
}

char* invertir ( unsigned char* c, unsigned char byte)
{
    *c ^= byte;
    return c;
}

void codificar(FILE* f_in, FILE* f_out, unsigned char byte)
{
    unsigned char c;
    while((c = fgetc(f_in)) && !feof(f_in))
        fputc(*invertir(rotar(&c), byte), f_out);
}

void decodificar (FILE* f_in, FILE* f_out, unsigned char byte)
{
    unsigned char c;
    while((c = fgetc(f_in)) && !feof(f_in))
        fputc(*desrotar(invertir(&c, byte)), f_out);
}
