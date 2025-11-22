package es.upm.Vista;

import es.upm.App;
import es.upm.Vista.IVistas.IVistaMascota;
import java.time.LocalDateTime;
import java.time.ZoneOffset;
import java.time.format.DateTimeFormatter;

public class VMascota implements IVistaMascota {
    public VMascota() {
    }
    @Override
    public String getNombreMascota() {
        System.out.println("Nombre de la mascota: ");
        return App.scanner.nextLine();
    }

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
    public String getDescripcion() {
        System.out.println("Descripción: ");
        return App.scanner.nextLine();
    }

    @Override
    public String getRIAC() {
        System.out.println("RIAC: ");
        return App.scanner.nextLine();
    }

    @Override
    public String getNumeroPoliza() {
        System.out.println("Poliza: ");
        return App.scanner.nextLine();
    }

    @Override
    public String getDomicilio() {
        System.out.println("Domicilio: ");
        return App.scanner.nextLine();
    }

    @Override
    public boolean getExotico() {
        System.out.println("¿Es exotica? (s/n): ");
        if (App.scanner.nextLine().equalsIgnoreCase("s"))
            return true;
        else
            return false;
    }

    @Override
    public String getCertificado() {
        System.out.println("Certificado: ");
        return App.scanner.nextLine();
    }
}
