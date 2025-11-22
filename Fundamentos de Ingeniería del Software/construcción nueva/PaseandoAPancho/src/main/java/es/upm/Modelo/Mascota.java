package es.upm.Modelo;

import es.upm.Modelo.Interfaces.IMascota;
import java.util.LinkedList;
import java.util.List;

public class Mascota implements IMascota {
    private String nombre;
    private String domicilio;
    private String descripcion;
    private String RIAC;
    private String numero_poliza;
    private Cuidador cuidador;
    private List<Cuidado> cuidados;

    public Mascota(String nombre, String domicilio, String descripcion, String RIAC, String numero_poliza) {
        this.nombre = nombre;
        this.domicilio = domicilio;
        this.descripcion = descripcion;
        this.RIAC = RIAC;
        this.numero_poliza = numero_poliza;
        this.cuidador = null;
        this.cuidados = new LinkedList<>();
    }

    public String getNombre() {
        return nombre;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    public String getDomicilio() {
        return domicilio;
    }

    public void setDomicilio(String domicilio) {
        this.domicilio = domicilio;
    }

    public String getDescripcion() {
        return descripcion;
    }

    public void setDescripcion(String descripcion) {
        this.descripcion = descripcion;
    }

    public String getRIAC() {
        return RIAC;
    }

    public void setRIAC(String RIAC) {
        this.RIAC = RIAC;
    }

    public String getNumero_poliza() {
        return numero_poliza;
    }

    public void setNumero_poliza(String numero_poliza) {
        this.numero_poliza = numero_poliza;
    }

    public Cuidador getCuidador() {
        return cuidador;
    }

    public void setCuidador(Cuidador cuidador) {
        this.cuidador = cuidador;
    }

    public List<Cuidado> getCuidados() {
        return cuidados;
    }

    public void setCuidados(List<Cuidado> cuidados) {
        this.cuidados = cuidados;
    }

    public void addCuidado(Cuidado cuidado) {
        this.cuidados.add(cuidado);
    }

    public void removeCuidado(Cuidado cuidado) {
        this.cuidados.remove(cuidado);
    }

    @Override
    public String toString() {
        return "Nombre:'" + nombre +
                " \n    Descripción ='" + descripcion + "\n";
    }
}
