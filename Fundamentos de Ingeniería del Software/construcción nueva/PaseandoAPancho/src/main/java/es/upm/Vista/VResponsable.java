package es.upm.Vista;

import es.upm.App;
import es.upm.Vista.IVistas.IVistaResponsable;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Scanner;
import java.time.ZoneOffset;

public class VResponsable implements IVistaResponsable {
    public VResponsable() {
    }
    @Override
    public String getNombre() {
        System.out.println("Ingrese su nombre de usuario:");
        return App.scanner.nextLine();
    }
}
