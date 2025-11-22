package es.upm.Modelo;

import java.util.List;

public class Premio_fisico {
    private String tipos;
    private String descripcion;
    private int panchopuntos;
    private List<Cuidador> cuidadores;

    public Premio_fisico(String tipos, String descripcion, int panchopuntos, List<Cuidador> cuidador) {
        this.tipos = tipos;
        this.descripcion = descripcion;
        this.panchopuntos = panchopuntos;
        this.cuidadores = cuidador;
    }

    public String getTipos() {
        return tipos;
    }

    public void setTipos(String tipos) {
        this.tipos = tipos;
    }

    public String getDescripcion() {
        return descripcion;
    }

    public void setDescripcion(String descripcion) {
        this.descripcion = descripcion;
    }

    public int getPanchopuntos() {
        return panchopuntos;
    }

    public void setPanchopuntos(int panchopuntos) {
        this.panchopuntos = panchopuntos;
    }

    public List<Cuidador> getCuidadores() {
        return cuidadores;
    }

    public void setCuidadores(List<Cuidador> cuidadores) {
        this.cuidadores = cuidadores;
    }

    public void addCuidadores(Cuidador cuidador) {
        this.cuidadores.add(cuidador);
    }

    public void removeCuidadores(Cuidador cuidador) {
        this.cuidadores.remove(cuidador);
    }
}
