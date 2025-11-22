package es.upm.Vista;

import es.upm.App;
import es.upm.Vista.IVistas.IVistaCuidador;

public class VCuidador implements IVistaCuidador {

    public VCuidador() {
    }
    @Override
    public String getNombre() {
        System.out.println("Ingrese su nombre de usuario:");
        return App.scanner.nextLine();
    }
}
