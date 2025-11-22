package es.upm.Modelo;

import java.util.List;

public class Promocion extends Premio_fisico {
    private int posiciones;
    private int tiempo;

    public Promocion(String tipos, String descripcion, int panchopuntos, List<Cuidador> cuidador, int posiciones, int tiempo) {
        super(tipos, descripcion, panchopuntos, cuidador);
        this.posiciones = posiciones;
        this.tiempo = tiempo;
    }

    public int getPosiciones() {
        return posiciones;
    }

    public void setPosiciones(int posiciones) {
        this.posiciones = posiciones;
    }

    public int getTiempo() {
        return tiempo;
    }

    public void setTiempo(int tiempo) {
        this.tiempo = tiempo;
    }
}
