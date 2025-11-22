package es.upm.Modelo;

import java.util.List;

public class Album_fotos {
    private List<Foto> fotos;

    public Album_fotos(List<Foto> foto) {
        this.fotos = foto;
    }

    public List<Foto> getFotos() {
        return fotos;
    }

    public void setFotos(List<Foto> fotos) {
        this.fotos = fotos;
    }

    public void addFoto(Foto foto) {
        this.fotos.add(foto);
    }

    public void removeFoto(Foto foto) {
        this.fotos.remove(foto);
    }
}
