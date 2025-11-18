alter table titanic_spaceship.pasajeros
add tutor varchar(7),
add foreign key (tutor) references pasajeros(id);

delimiter $$
create procedure assign_tutors()
begin
	declare done integer default false;
	declare id_menor varchar(7);
    declare id_tutor varchar(7);
    declare cabina_menor integer;
    declare lado_menor varchar(1);
    declare cubierta_menor varchar(1);
	declare cur cursor for
		select id, numero_cabina, lado_cabina, cubierta
        from pasajeros
        where edad < 18
        and criosueño = 0
        and tutor is null;
	declare continue handler for not found set done = true;
		open cur;
        read_loop: loop
			fetch cur into id_menor, cabina_menor, lado_menor, cubierta_menor;
            if done then
				leave read_loop;
			end if;
            set id_tutor = null;
            select min(id) into id_tutor
				from pasajeros
				where numero_cabina = cabina_menor
				and lado_cabina = lado_menor
				and cubierta = cubierta_menor
				and criosueño = 0
				and edad >= 18;
            if id_tutor is null then
				update pasajeros
                set criosueño = 1
                where id = id_menor;
			else
				update pasajeros
                set tutor = id_tutor
                where id = id_menor;
			end if;
		end loop;
	close cur;
end$$
delimiter ;

SET SQL_SAFE_UPDATES= 0;

call assignTutors();

SET SQL_SAFE_UPDATES = 1;