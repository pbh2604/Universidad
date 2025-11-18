SELECT 
    pasajeros.nombre,
    entretenimientos.nombre AS zona_entretenimiento,
    SUM(gastos.cantidad) AS gasto_total
FROM pasajeros 
JOIN cabinas ON pasajeros.numero_cabina = cabinas.numero AND pasajeros.lado_cabina = cabinas.lado
JOIN cubiertas ON cabinas.cubierta = cubiertas.letra
JOIN gastos  ON pasajeros.id = gastos.pasajero
JOIN entretenimientos ON gastos.entretenimiento = entretenimientos.id
WHERE 
    cubiertas.letra = 'A' /* Solo pasajeros de la cubierta 'A'*/
    AND NOT EXISTS (-- que no existan entretenimientos
        SELECT *
        FROM entretenimientos
        WHERE NOT EXISTS (-- que no tengan gastos
            SELECT *
            FROM gastos
            WHERE gastos.pasajero = pasajeros.id 
              AND gastos.entretenimiento = entretenimientos.id
        )
    )/* Pasajeros que han gastado en todas las zonas*/
GROUP BY pasajeros.nombre, zona_entretenimiento
ORDER BY pasajeros.nombre ASC, gasto_total DESC;