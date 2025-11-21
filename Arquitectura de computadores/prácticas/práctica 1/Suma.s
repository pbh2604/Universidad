; Programa que calcula la suma de A y B dejando el resultado en C.

.data

A:	.word		4
B:	.word		0xF
C:	.space	8

.text
.org	0xC
	ld R1, A(R0);El punto y coma es para poner un comentario
	ld R2, B(R0);esto es para cargar las variables en un espacio de memeoria
	dadd R3, R1, R2; R3 es como el espacio de memoria que todavía no lo has guardado, necesitas otras instrucción para guardarlo
	sd R3, C(R0);
	halt
;word ocupa en total 64 bits -> 8 bytes 
;y cada byte utilizado son dos espacios en la fila de data de las posiciones 
;por lo que el tamaño total de cada palabra son la fila entera los 16 numeros.
