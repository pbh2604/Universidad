WITH 
pasajeros_con_entretenimiento AS (
    SELECT p.planeta_natal, p.sistema_natal, COUNT(*) AS total_pasajeros_con_entretenimiento
    FROM pasajeros p
    JOIN (
        SELECT pasajero
        FROM gastos
        GROUP BY pasajero
        HAVING COUNT(DISTINCT entretenimiento) >= 4
    ) g
    ON p.id = g.pasajero
    GROUP BY p.planeta_natal, p.sistema_natal
),
total_pasajeros_por_planeta AS (
    SELECT planeta_natal, sistema_natal, COUNT(*) AS total_pasajeros
    FROM pasajeros
    GROUP BY planeta_natal, sistema_natal
)
SELECT t.planeta_natal, 
       t.sistema_natal,
       t.total_pasajeros,
       e.total_pasajeros_con_entretenimiento
FROM total_pasajeros_por_planeta t
LEFT JOIN pasajeros_con_entretenimiento e
ON t.planeta_natal = e.planeta_natal AND t.sistema_natal = e.sistema_natal
WHERE (e.total_pasajeros_con_entretenimiento * 1.0 / t.total_pasajeros) > 0.25;
