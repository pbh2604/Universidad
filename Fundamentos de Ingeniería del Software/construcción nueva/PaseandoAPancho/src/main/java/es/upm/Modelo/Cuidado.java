package es.upm.Modelo;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

public class Cuidado {
    private double coste;
    private int id_fiscal;
    private long fecha;
    private int duracion;
    private int cp;
    private List<Responsable> responsables;
    private Cuidador cuidador;
    private Mensaje mensaje;
    private Mascota mascota;

    public Cuidado(double coste, int id_fiscal, long fecha, int duracion, int cp, List<Responsable> responsables, Cuidador cuidador, Mensaje mensaje, Mascota mascota) {
        this.coste = coste;
        this.id_fiscal = id_fiscal;
        this.fecha = fecha;
        this.duracion = duracion;
        this.cp = cp;
        this.responsables = responsables;
        this.cuidador = cuidador;
        this.mensaje = mensaje;
        this.mascota = mascota;
    }

    public double getCoste() {
        return coste;
    }

    public void setCoste(double coste) {
        this.coste = coste;
    }

    public int getId_fiscal() {
        return id_fiscal;
    }

    public void setId_fiscal(int id_fiscal) {
        this.id_fiscal = id_fiscal;
    }

    public long getFecha() {
        return fecha;
    }

    public void setFecha(long fecha) {
        this.fecha = fecha;
    }

    public int getDuracion() {
        return duracion;
    }

    public void setDuracion(int duracion) {
        this.duracion = duracion;
    }

    public int getCp() {
        return cp;
    }

    public void setCp(int cp) {
        this.cp = cp;
    }

    public List<Responsable> getResponsables() {
        return responsables;
    }

    public void setResponsables(List<Responsable> responsables) {
        this.responsables = responsables;
    }

    public Cuidador getCuidador() {
        return cuidador;
    }

    public void setCuidador(Cuidador cuidador) {
        this.cuidador = cuidador;
    }

    public Mensaje getMensaje() {
        return mensaje;
    }

    public void setMensaje(Mensaje mensaje) {
        this.mensaje = mensaje;
    }

    public Mascota getMascota() {
        return mascota;
    }

    public void setMascota(Mascota mascota) {
        this.mascota = mascota;
    }

    public void addResponsable(Responsable responsable) {
        this.responsables.add(responsable);
    }

    public void removeResponsable(Responsable responsable) {
        this.responsables.remove(responsable);
    }

    @Override
    public String toString() {
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd-MM-yyyy HH:mm");
        Date date = new Date(fecha);
        String fechaFormateada = dateFormat.format(date);
        return "Cuidado de " + mascota.getNombre() +
                "\n   fecha=" + fechaFormateada +
                "\n   duracion=" + duracion +
                "\n   coste=" + coste;
    }
}
