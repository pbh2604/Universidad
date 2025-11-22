package es.upm.Vista;

import es.upm.App;
import es.upm.Vista.IVistas.IVistaCuidados;
import java.time.LocalDateTime;
import java.time.ZoneOffset;
import java.time.format.DateTimeFormatter;

public class VCuidados implements IVistaCuidados {
    public VCuidados() {
    }

    @Override
    public String getNombreMascota() {
        System.out.println("Nombre de la mascota: ");
        return App.scanner.nextLine();
    }

    @Override
    public int getCP() {
        System.out.println("CP de la mascota: ");
        try {
            return Integer.parseInt(App.scanner.nextLine());
        } catch (NumberFormatException e) {
            System.out.println("Por favor, introduce un número entero.");
            return getCP();
        }
    }

    @Override
    public long getFecha() {
        System.out.println("Fecha del cuidado (dd-MM-yyyy HH:mm): ");
        String fecha = App.scanner.nextLine();
        LocalDateTime localDateTime = LocalDateTime.parse(fecha, DateTimeFormatter.ofPattern("dd-MM-yyyy HH:mm"));
        return localDateTime.toInstant(ZoneOffset.UTC).toEpochMilli();
    }

    @Override
    public int getDuracion() {
        System.out.println("Duración del cuidado (en minutos): ");
        try {
            return Integer.parseInt(App.scanner.nextLine());
        } catch (NumberFormatException e) {
            System.out.println("Por favor, introduce un número entero.");
            return getDuracion();
        }
    }
}
