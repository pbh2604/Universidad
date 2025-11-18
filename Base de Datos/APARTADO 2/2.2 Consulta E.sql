select nombre,sistema
from planetas
where (
	select COUNT(*) -- numero de nacidos por planeta
	from pasajeros
	where planeta_natal = planetas.nombre
    )<(
    select avg(nacimientos) -- promedio de nacidos 
	from ( 
		select count(nombre) as nacimientos
		from pasajeros
		group by planeta_natal, sistema_natal) as subconsulta
	);
    
    