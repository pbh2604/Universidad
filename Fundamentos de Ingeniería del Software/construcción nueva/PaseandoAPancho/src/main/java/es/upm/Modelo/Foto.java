package es.upm.Modelo;

public class Foto {
    private boolean es_favorita;
    private String path;

    public Foto(boolean es_favorita, String path) {
        this.es_favorita = es_favorita;
        this.path = path;
    }

    public boolean getEs_favorita() {
        return es_favorita;
    }

    public void setEs_favorita(boolean es_favorita) {
        this.es_favorita = es_favorita;
    }

    public String getPath() {
        return path;
    }

    public void setPath(String path) {
        this.path = path;
    }
}
