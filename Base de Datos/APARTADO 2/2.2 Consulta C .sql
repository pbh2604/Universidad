select nombre, concat(cubierta, '-', numero_cabina, '-', lado_cabina) as 'cabina', planeta_destino, sistema_destino
from pasajeros, cubiertas
where pasajeros.cubierta = cubiertas.letra
and cubiertas.clase = 3
and cubiertas.letra between 'A' and 'D'
and pasajeros.criosueño = 0