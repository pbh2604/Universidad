package es.upm.Modelo;

import java.util.LinkedList;
import java.util.List;

public class Cuidador extends Usuario {
    private int panchopuntos;
    private String capacitacion;
    private String documentacion;
    private Responsable responsable;
    private List<Mascota> mascotas;
    private List<Premio_fisico> premios_fisicos;
    private List<Cuidado> cuidados;

    public Cuidador(String id, String nombre, TPlataforma plataforma) {
        super(id, nombre, plataforma, new LinkedList<>(), new LinkedList<>());
        this.panchopuntos = 0;
        this.capacitacion = null;
        this.documentacion = null;
        this.responsable = null;
        this.mascotas = new LinkedList<>();
        this.premios_fisicos = new LinkedList<>();
        this.cuidados = new LinkedList<>();
    }

    public int getPanchopuntos() {
        return panchopuntos;
    }

    public void setPanchopuntos(int panchopuntos) {
        this.panchopuntos = panchopuntos;
    }

    public String getCapacitacion() {
        return capacitacion;
    }

    public void setCapacitacion(String capacitacion) {
        this.capacitacion = capacitacion;
    }

    public String getDocumentacion() {
        return documentacion;
    }

    public void setDocumentacion(String documentacion) {
        this.documentacion = documentacion;
    }

    public Responsable getResponsable() {
        return responsable;
    }

    public void setResponsable(Responsable responsable) {
        this.responsable = responsable;
    }

    public List<Mascota> getMascotas() {
        return mascotas;
    }

    public void setMascotas(List<Mascota> mascotas) {
        this.mascotas = mascotas;
    }

    public List<Premio_fisico> getPremios_fisicos() {
        return premios_fisicos;
    }

    public void setPremios_fisicos(List<Premio_fisico> premios_fisicos) {
        this.premios_fisicos = premios_fisicos;
    }

    public List<Cuidado> getCuidados() {
        return cuidados;
    }

    public void setCuidados(List<Cuidado> cuidados) {
        this.cuidados = cuidados;
    }

    public void addMascota(Mascota mascota) {
        this.mascotas.add(mascota);
    }

    public void removeMascota(Mascota mascota) {
        this.mascotas.remove(mascota);
    }

    public void addPremio_fisico(Premio_fisico premio_fisico) {
        this.premios_fisicos.add(premio_fisico);
    }

    public void removePremio_fisico(Premio_fisico premio_fisico) {
        this.premios_fisicos.remove(premio_fisico);
    }

    public void addCuidado(Cuidado cuidado) {
        this.cuidados.add(cuidado);
    }

    public void removeCuidado(Cuidado cuidado) {
        this.cuidados.remove(cuidado);
    }

    public int calcularPanchopuntos() {
        return 0;
    }
}
