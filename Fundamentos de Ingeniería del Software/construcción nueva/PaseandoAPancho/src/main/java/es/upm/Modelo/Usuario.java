package es.upm.Modelo;

import es.upm.Modelo.Interfaces.IUsuario;
import java.util.List;

public abstract class Usuario implements IUsuario {
    private String id;
    private String nombre;
    private TPlataforma plataforma;
    private List<Mensaje> mensajesEnviados;
    private List<Mensaje> mensajesRecibidos;

    public Usuario(String id, String nombre, TPlataforma plataforma, List<Mensaje> mensajesEnviados, List<Mensaje> mensajesRecibidos) {
        this.id = id;
        this.nombre = nombre;
        this.plataforma = plataforma;
        this.mensajesEnviados = mensajesEnviados;
        this.mensajesRecibidos = mensajesRecibidos;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getNombre() {
        return nombre;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    public TPlataforma getPlataforma() {
        return plataforma;
    }

    public void setPlataforma(TPlataforma plataforma) {
        this.plataforma = plataforma;
    }

    public List<Mensaje> getMensajesEnviados() {
        return mensajesEnviados;
    }

    public void setMensajesEnviados(List<Mensaje> mensajesEnviados) {
        this.mensajesEnviados = mensajesEnviados;
    }

    public List<Mensaje> getMensajesRecibidos() {
        return mensajesRecibidos;
    }

    public void setMensajesRecibidos(List<Mensaje> mensajesRecibidos) {
        this.mensajesRecibidos = mensajesRecibidos;
    }

    public void addMensajesEnviados(Mensaje mensaje) {
        this.mensajesEnviados.add(mensaje);
    }

    public void removeMensajesEnviados(Mensaje mensaje) {
        this.mensajesEnviados.remove(mensaje);
    }

    public void addMensajesRecibidos(Mensaje mensaje) {
        this.mensajesRecibidos.add(mensaje);
    }

    public void removeMensajesRecibidos(Mensaje mensaje) {
        this.mensajesRecibidos.remove(mensaje);
    }
}
