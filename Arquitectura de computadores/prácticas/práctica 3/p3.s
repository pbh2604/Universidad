.data
i:		.word32  0
suma:		.word32  0
array:		.space 960	

.code
main:
; Inicializar los elementos del array con el valor 2
		lw r2,i(r0)
		daddi r3,r0,240
		daddi r6,r0,2
FOR_LOOP_1:
		slt r4,r2,r3
		beqz r4,END_FOR_LOOP1
		dsll r5,r2,2
		sw r6,array(r5)
		daddi r2,r2,1
		j FOR_LOOP_1
		nop		
END_FOR_LOOP1:
		
; Recorre el bucle suma += array[i]^2 
		daddi r2,r0,0				; i = 0
		daddi r3,r0,240
		lw r5,suma(r0)
FOR_LOOP_2:

		slt r4,r2,r3
		beqz r4,END_FOR_LOOP2
		
		dsll r6,r2,2
		lw r7,array(r6)
		dmul r8,r7,r7				; a[i]*a[i]
		dadd r5,r5,r8

		daddi r2,r2,1
		j FOR_LOOP_2
		nop
END_FOR_LOOP2:
		sw r5,suma(r0)
		halt