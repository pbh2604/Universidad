package es.upm.Modelo;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class Responsable extends Usuario {
    private List<Cuidador> cuidadores;
    private List<Mascota> mascotas;
    private Cuidado cuidado;

    public Responsable(String id, String nombre, TPlataforma plataforma) {
        super(id, nombre, plataforma, new LinkedList<>(), new LinkedList<>());
        this.cuidadores = cuidadores;
        this.mascotas = new ArrayList<>();
        this.cuidado = cuidado;
    }

    public Responsable(String id, String nombre, TPlataforma plataforma, LinkedList<Mascota> m) {
        super(id, nombre, plataforma, new LinkedList<>(), new LinkedList<>());
        this.cuidadores = cuidadores;
        this.mascotas = m;
        this.cuidado = cuidado;
    }

    public List<Cuidador> getCuidadores() {
        return cuidadores;
    }

    public void setCuidadores(List<Cuidador> cuidadores) {
        this.cuidadores = cuidadores;
    }

    public List<Mascota> getMascotas() {
        return mascotas;
    }

    public void setMascotas(List<Mascota> mascotas) {
        this.mascotas = mascotas;
    }

    public Cuidado getCuidado() {
        return cuidado;
    }

    public void setCuidado(Cuidado cuidado) {
        this.cuidado = cuidado;
    }

    public void addCuidador(Cuidador cuidador) {
        this.cuidadores.add(cuidador);
    }

    public void removeCuidador(Cuidador cuidador) {
        this.cuidadores.remove(cuidador);
    }

    public void addMascota(Mascota mascota) {
        this.mascotas.add(mascota);
    }

    public void removeMascota(Mascota mascota) {
        this.mascotas.remove(mascota);
    }
}
