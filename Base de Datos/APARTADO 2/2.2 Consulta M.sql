delimiter $$
create function porcentajePasajerosParaDestinoPorCubierta(planeta varchar(50), sistema varchar(50), letra varchar(1))
returns decimal (10,2)
deterministic
begin
	declare porcentaje decimal(10,2);
	declare totalPasajeros int;
    declare numPasajeros int;
    select count(sub.total) into totalPasajeros from (
		select id as total
        from pasajeros) as sub;
        
    select count(sub.pasajeros) into numPasajeros from (
		select id as pasajeros
        from pasajeros
        where planeta_destino=planeta and sistema_destino=sistema and cubierta=letra
        ) as sub;
    set porcentaje= (numPasajeros/totalPasajeros)*100;
    return (porcentaje);
end $$
delimiter ;

select id, cubierta
from pasajeros
where planeta_destino='55 Cancri e'
and sistema_destino='Copernico'
order by cubierta asc;
;

select id 
from pasajeros
where planeta_destino='55 Cancri e' 
and sistema_destino='Copernico' 
and cubierta='A'
        
;
select porcentajePasajerosParaDestinoPorCubierta('55 Cancri e','Copernico','A') as porcentaje;