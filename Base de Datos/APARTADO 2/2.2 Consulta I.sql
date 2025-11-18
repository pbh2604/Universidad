select COUNT(*) - SUM(vip) as noVIP, lado_cabina, numero_cabina, count(id) as pasajerosDeCabina
from pasajeros 
inner join (
	SELECT pasajero, sum(cantidad) as gasto	
	FROM gastos 
	group by pasajero
	having sum(cantidad)>2*(
		select avg(gasto) 
		from(
			SELECT sum(cantidad) as gasto
			FROM gastos 
			group by pasajero) as subconsulta
	)
)as gastos
on pasajeros.id=gastos.pasajero
group by lado_cabina, numero_cabina
having COUNT(*) - SUM(vip)>3


