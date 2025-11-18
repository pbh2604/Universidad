#ifndef TIPOS_H_INCLUDED
    #define TIPOS_H_INCLUDED
    #include <stdio.h>
    #define M 15
    #define N 10
    typedef struct{
    char id[11];
    unsigned n[6];
    }Apuesta;

    int aleatorio(int, int);
    void crearid(char [10]);
    void crearnum(unsigned [7]);
    void crearapuesta(Apuesta*);
    void rellenarfapuestas(FILE* f_in, unsigned);
    unsigned acertados(Apuesta , unsigned[7], unsigned *);

#endif // TIPOS_H_INCLUDED
