; Programa que calcula la suma de los vectores A y B
; dejando el resultado en otro vector C.

.data

.org	32     ;32 en decimal = 20 en hexadecimal

A:	.word32	0,9,11,3,12,5,14,7    ;pongo .word32 porque me piden que sea cada elemento de 32 bits
B:	.word32	8,1,10,2,13,4,6,15
C:	.word32	0,0,0,0,0,0,0,0

.text
			daddi R10,R0,0
			daddi R5,R0,0
for:  		slti R5,R10,32 ; pongo 32 porque es el mumero de bits que tiene un tipo de elemento .word32
			beqz R5, fin
			lb R1, A(R10)
			lb R2, B(R10)
			dadd R3,R1,R2
			sb R3,C(R10)
			daddi R10,R10,4; .word32 va de cuaro en cuatro.
			j for
fin:			halt

;lo que he hecho para saber cuales son los espacios que ocupan en la dirección en hexadecimal
;.byte --> 1 byte---> 8 bits, lo que me piden es que en vez de 8 bits, ocupe 32 bits,son ocho por lo que tengo que hacer,
;32/8 = 4 bytes, y son 16 espacios
;por lo que 16/4 = 4 que son los esapcios que ocupan.
