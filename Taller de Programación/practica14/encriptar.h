#ifndef ENCRIPTAR_H_INCLUDED
    #define ENCRIPTAR_H_INCLUDED

    char* rotar    (unsigned char*);
    char* desrotar (unsigned char*);
    char* invertir (unsigned char*, unsigned char);
    void  codificar (FILE*, FILE*, unsigned char);
    void  decodificar(FILE*, FILE*, unsigned char);



#endif // ENCRIPTAR_H_INCLUDED
