create schema nave_espacial;
use nave_espacial;

create table sistema (
	nombre varchar(50),
    primary key (nombre)
);

create table planeta (
	nombre varchar(50),
    masa integer,
    radio integer,
    nombreSis varchar(50),
    primary key (nombre, nombreSis)
);

create table satelite (
	nombre varchar(50),
    nombrePla varchar(50),
    nombreSis varchar(50),
    primary key (nombre, nombrePla, nombreSis)
);

create table atmosfera (
	nombreElem varchar(50),
    nombrePla varchar(50),
    nombreSis varchar(50),
    primary key (nombreElem, nombrePla, nombreSis)
);

create table elementoQuimico (
	nombre varchar(50),
    simbolo varchar(3),
    peso decimal,
    primary key (nombre)
);

create table personal (
	id integer,
    nombreEnt varchar(50),
    idJefe integer,
    primary key (id)
);

create table entretenimiento (
	nombre varchar(50),
    primary key (nombre)
);

create table pasajero (
	id integer,
    nombre varchar(100),
    edad integer,
    vip varchar(2),
    criogenizacion varchar(2),
    desaparecido varchar(2),
    nombrePlaNat varchar(50),
    nombreSisNat varchar(50),
    nombrePlaDes varchar(50),
    nombreSisDes varchar(50),
    numeroCab integer,
    ladoCab varchar(1), 
    idTutelado integer,
    primary key (id)
);

create table gasto (
	idPas integer,
    nombreEnt varchar(50),
    gastoTotal decimal,
    primary key (idPas, nombreEnt)
);

create table cubierta (
	letra varchar(1),
	clase varchar(7),
    primary key (letra)
);

create table cabina (
	numero integer,
    lado varchar(1),
    letraCub varchar(1),
    primary key (numero, lado)
);

create table robot (
	id integer,
    diseño varchar(50),
    primary key (id)
);

create table limpia (
	numeroCab integer,
    ladoCab varchar(1),
    idRob integer,
    primary key (numeroCab, ladoCab, idRob)
);

create table mecanico (
	id integer,
    primary key (id)
);

create table repara (
	idRob integer,
    idMec integer,
    fecha date,
    primary key (idRob, idMec, fecha)
);

alter table repara
add foreign key (idRob) references robot(id),
add foreign key (idMec) references mecanico(id);

alter table limpia
add foreign key (numeroCab, ladoCab) references cabina(numero, lado),
add foreign key (idRob) references robot(id);

alter table cabina
add foreign key (letraCub) references cubierta(letra);

alter table gasto
add foreign key (nombreEnt) references entretenimiento(nombre),
add foreign key (idPas) references pasajero(id);

alter table pasajero
add foreign key (nombrePlaNat) references planeta(nombre),
add foreign key (nombreSisNat) references sistema(nombre),
add foreign key (nombrePlaDes) references planeta(nombre),
add foreign key (nombreSisDes) references sistema(nombre),
add foreign key (numeroCab, ladoCab) references cabina(numero, lado),
add foreign key (idTutelado) references pasajero(id);

alter table personal
add foreign key (nombreEnt) references entretenimiento(nombre),
add foreign key (idJefe) references personal(id);

alter table planeta
add foreign key (nombreSis) references sistema(nombre);

alter table atmosfera
add foreign key (nombrePla) references planeta(nombre),
add foreign key (nombreSis) references sistema(nombre),
add foreign key (nombreElem) references elementoQuimico(nombre);

alter table satelite
add foreign key (nombrePla) references planeta(nombre),
add foreign key (nombreSis) references sistema(nombre);