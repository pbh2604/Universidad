SELECT planetas.nombre,planetas.sistema AS sistema
FROM planetas
WHERE 
    NOT EXISTS (
        SELECT */*los pasajeros donde su planeta de destino sea igual al nombre del planeta*/
        FROM pasajeros
        WHERE pasajeros.planeta_destino = planetas.nombre AND pasajeros.vip = 1
    )
    AND planetas.nombre IN (
        SELECT pasajeros.planeta_natal/*cogemos el planeta natal de los pasajeros de mayor edad*/
        FROM pasajeros
        WHERE 
            pasajeros.edad = (SELECT MAX(edad) FROM pasajeros)
    );