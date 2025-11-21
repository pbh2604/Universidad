; Programa que calcula la suma de los vectores A y B
; dejando el resultado en otro vector C.

.data

.org	32     ;32 en decimal = 20 en hexadecimal

A:	.byte	0,9,11,3,12,5,14,7
B:	.byte	8,1,10,2,13,4,6,15
C:	.byte	0,0,0,0,0,0,0,0

.text
		daddi R10,R0,0
		daddi R5,R0,0
for:  	slti R5,R10,8; esto se pone 8 por que un byte tiene en total 8 bits
		beqz R5, fin
		lb R1, A(R10)
		lb R2, B(R10)
		dadd R3,R1,R2
		sb R3,C(R10)
		daddi R10,R10,1; es el numero de espacios que recorre una variable de tipo byte
		j for
fin:		halt

;cada uno de los vectores ocupa 1 posiciones(que son dos numeros) porque ocupa un byte