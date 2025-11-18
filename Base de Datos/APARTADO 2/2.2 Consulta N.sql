delimiter $$
create trigger insert_gasto_negativo_trigger
before insert on gastos
for each row
begin
	if NEW.cantidad < 0 then
		signal sqlstate '02000'
        set message_text = 'ERROR: Bienvenido
ciber-delincuente, pero no puedes sacar dinero en un entretenimiento';
	end if;
end $$
delimiter ;

delimiter $$
create trigger update_gasto_negativo_trigger
before update on gastos
for each row
begin
	if NEW.cantidad < 0 then
		signal sqlstate '02000'
        set message_text = 'ERROR: Bienvenido
ciber-delincuente, pero no puedes sacar dinero en un entretenimiento';
	end if;
end $$
delimiter ;