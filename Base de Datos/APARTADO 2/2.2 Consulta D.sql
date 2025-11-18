SELECT 
    entretenimientos.nombre AS zona_entretenimiento,
    SUM(gastos.cantidad) AS gasto_total,
    CASE 
        WHEN pasajeros.vip = 1 THEN 'VIP'
        ELSE 'NO VIP'
    END AS tipo_pasajero
FROM 
    gastos 
JOIN 
    entretenimientos ON gastos.entretenimiento = entretenimientos.id
JOIN 
    pasajeros ON gastos.pasajero = pasajeros.id
GROUP BY 
    zona_entretenimiento, tipo_pasajero
ORDER BY 
    zona_entretenimiento, tipo_pasajero;
    