create view entretenimiento_pasajeros
as select pasajeros.id, pasajeros.nombre, edad, transportado, planeta_destino, sistema_destino, numero_cabina, lado_cabina, cubierta, cubiertas.clase, entretenimientos.nombre as entretenimiento_max_gasto, g1.cantidad as cantidad_max_gasto
from pasajeros, cubiertas, gastos g1, entretenimientos
where pasajeros.cubierta = cubiertas.letra
and pasajeros.id = g1.pasajero
and g1.entretenimiento = entretenimientos.id
and g1.cantidad = (
	select max(g2.cantidad)
    from gastos g2
    where g1.pasajero = g2.pasajero);
    
create user analista_datos identified by '1234';
grant select on entretenimiento_pasajeros to 'analista_datos';