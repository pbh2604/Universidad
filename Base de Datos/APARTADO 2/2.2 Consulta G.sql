SELECT DISTINCT cabinas.cubierta, cabinas.numero, cabinas.lado
FROM cabinas
JOIN pasajeros ON pasajeros.numero_cabina = cabinas.numero AND pasajeros.lado_cabina = cabinas.lado
WHERE 
    pasajeros.id IN (
        SELECT gastos.pasajero
        FROM gastos
        WHERE 
            gastos.entretenimiento = ( -- Pasajeros que tienen gasto en entretenimiento más popular
				SELECT gastos.entretenimiento -- entretenimiento más popular
                FROM gastos
                GROUP BY gastos.entretenimiento
                HAVING COUNT(DISTINCT gastos.pasajero) = ( 
					SELECT MAX(total_pasajeros) -- num de pasajeros en el entretenimiento más popular
					FROM (
						SELECT COUNT(DISTINCT gastos.pasajero) AS total_pasajeros -- Num de pasajeros por entretenimiento
						FROM gastos
						GROUP BY gastos.entretenimiento
                        ) AS max_pasajeros
                    )
            )
    )
ORDER BY 
   cabinas.cubierta, cabinas.numero, cabinas.lado;