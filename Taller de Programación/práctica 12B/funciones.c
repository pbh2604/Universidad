#include "tipos.h"
#include <stdio.h>
#include <stdlib.h>

void rellenarfapuestas(FILE* f_in, unsigned _apuesta){
    int i;
    Apuesta apuesta;
    for (i=0; i<_apuesta; i++){
        crearapuesta(&apuesta);
        fwrite(&apuesta, sizeof(Apuesta), 1, f_in);
    }
}

void crearid(char _id[11]){
    int i;
    _id[0] = '2';
    _id[1] = '8';
    for (i=2; i<10; i++)
        _id[i] = aleatorio('0', '9');
    _id[10] = aleatorio('A', 'Z');
    _id[11] = '\0';
}

void crearnum(unsigned _num[6]){
    int i, j;
    for (i=0; i<6;){
        _num[i] = aleatorio(1, 49);
    for (j=0; j<i && _num[j] != _num[i]; j++);
        if (j == i)
            i++;
    }
}

void crearapuesta(Apuesta* _apuesta){
    crearid(_apuesta->id);
    crearnum(_apuesta->n);
}

int aleatorio(int a, int b){
    return (rand()%(b-a+1)+a);
}

unsigned acertados(Apuesta _apuesta, unsigned _premiado[6], unsigned * _acertados){
    unsigned contaciertos = 0, i, j;
    for (i=0; i<6; i++){
        for(j=0; j<6 && _apuesta.n[i] != _premiado[j]; j++);
            if (j<6)
                _acertados[contaciertos++] = _apuesta.n[i];
    }
    return contaciertos;
}
