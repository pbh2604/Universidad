/*actualiza la cantidad de pasajeros vip, si cumplen la condiciónb de superar los 5000 en gastos */
UPDATE pasajeros 
SET pasajeros.vip = 1
WHERE (
    SELECT SUM(gastos.cantidad)
    FROM gastos 
    WHERE gastos.pasajero = pasajeros.id
) > 5000;

/*  actualiza la condición de VIP al insertar nuevos gastos*/
DELIMITER $$

CREATE TRIGGER actualizar_vip_en_insert
AFTER INSERT ON gastos
FOR EACH ROW
BEGIN
    DECLARE gastos_totales DECIMAL(10, 2);

    /*Calcular el gasto total del pasajero*/
    SELECT SUM(cantidad) INTO gastos_totales
    FROM gastos
    WHERE pasajero = NEW.pasajero;

    /* Verifica si supera los 5000 y actualiza si se debe*/
    IF gastos_totales > 5000 THEN
        UPDATE pasajeros
        SET vip = 1
        WHERE id = NEW.pasajero;
    END IF;
END;
$$

DELIMITER ;

/* Actualiza la condición de VIP al modificar gastos existentes*/
DELIMITER $$

CREATE TRIGGER actualizar_vip_en_update
AFTER UPDATE ON gastos
FOR EACH ROW
BEGIN
    DECLARE gastos_totales DECIMAL(10, 2);

    /* Calcular el gasto total del pasajero*/
    SELECT SUM(cantidad) INTO gastos_totales
    FROM gastos
    WHERE pasajero = NEW.pasajero;

	/*Verificar si supera los 5000 y actualizar si se debe*/
    IF gastos_totales > 5000 THEN
        UPDATE pasajeros
        SET vip = 1
        WHERE id = NEW.pasajero;
    END IF;
END;
$$

DELIMITER ;
